#include "Http.hpp"


std::string Http::ToHex(const std::string& s, bool upper_case)
{
	// We could use a lib like cppcodec, but this seems fine
	std::ostringstream ret;

	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		int z = s[i] & 0xff;
		ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z;
	}

	return ret.str();
}

std::string Http::Get(std::string endpoint)
{
	cpr::Response r = cpr::Get(cpr::Url{ fmt::format("{}{}.php", url, endpoint)});
	return r.text;
}

std::string Http::GetVersion()
{
	return Get("version");
}

void Http::GetUpdate() 
{
	spdlog::info("Updating...");
	double updateStart = Time::millisecond();

	std::string updateFiles = Get("update");
	std::string updateFilesChecksums = Get("update_checksums");

	json files = json::parse(updateFiles);
	json filesChecksums = json::parse(updateFilesChecksums);
	std::queue<std::string> filesQueue;

	spdlog::debug("Files in the installation package: {}", files.dump());

	// Delete and rename any old files
	std::string oldExecutableName = Filesystem::currentDirectory + "__bxc_os.old.exe";
	std::string newExecutableName = Filesystem::currentDirectory + "bxc_os.exe";

	// If .old file exists, remove it
	if (std::filesystem::exists(oldExecutableName))
		std::filesystem::remove(Filesystem::currentDirectory + "__bxc_os.old.exe");
	
	// Rename the current .exe file to .old
	if (std::filesystem::exists(newExecutableName))
		std::filesystem::rename(Filesystem::currentDirectory + "bxc_os.exe", Filesystem::currentDirectory + "__bxc_os.old.exe");

	spdlog::info("Checking files...");

	// Iterate over every file
	for (int f = 0; f < files.size(); f++) 
	{
		std::string file = (std::string)files[f];
		std::string filePath = Filesystem::currentDirectory + file;

		// ===========
		// Reading
		// ===========
		std::string fileContent;
		std::ifstream readStream;
		readStream.open(filePath, std::ios::binary);

		// If file wasn't found, we need to download it
		if (readStream.fail())
		{
			filesQueue.push(file);
			spdlog::debug("- File '{}' wasn't found, added it to the download queue.", file);
			continue;
		}
		// If file was found, assign its contents to a variable
		if (readStream.good()) 
			fileContent.assign(
				(std::istreambuf_iterator<char>(readStream)),
				(std::istreambuf_iterator<char>()));

		// Make a hex out of the file, since that's how we hash it on the server
		fileContent = ToHex(fileContent, false);

		// Close read stream
		readStream.close();

		// ===========
		// Hashing
		// ===========
		// Digest the file using sha256
		CryptoPP::SHA256 hash;
		CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

		hash.CalculateDigest(digest, (CryptoPP::byte*)fileContent.c_str(), fileContent.length());

		CryptoPP::HexEncoder encoder;
		std::string hashedFileContent;
		encoder.Attach(new CryptoPP::StringSink(hashedFileContent));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();

		// Put the hex into lowercase, because that's just how it's generated on the backend
		boost::to_lower(hashedFileContent);

		// ===========
		// Comparing
		// ===========

		// If file checksum doesn't match with the online one, add the file to download queue
		if (hashedFileContent != filesChecksums[file])
		{
			filesQueue.push(file);
			spdlog::debug("- Checksum of '{}' doesn't match, added to queue.", file);
		}
		else
			spdlog::debug("- Checksum of '{}' matches.", file);
	}
	
	spdlog::info("All files checked!");
	spdlog::info("Downloading files...");

	std::ofstream out;

	// Downloads files in the queue
	while (!filesQueue.empty())
	{
		std::string file = filesQueue.front();
		std::string filePath = Filesystem::currentDirectory + file;

		// Downloads the file
		std::string fileContent = Get("update/" + file);

		spdlog::debug("File '{}' downloaded successfully.", file);

		out.open(file, std::ofstream::binary);
		out << fileContent;
		out.close();

		filesQueue.pop();
	}

	double updateEnd = Time::millisecond();

	spdlog::info("BXC OS {0} downloaded in {1} seconds.", GetVersion(), (updateEnd - updateStart) / 1000);
	spdlog::info("This window will be restarted in 15 seconds.");
	Sleep(15000);
}