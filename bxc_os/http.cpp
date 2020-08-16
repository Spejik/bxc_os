#include "http.h"


std::string Http::ToHex(const std::string& s, bool upper_case)
{
	std::ostringstream ret;

	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		int z = s[i] & 0xff;
		ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z;
	}

	return ret.str();
}


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string Http::Get(std::string endpoint)
{
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, (sUrl + endpoint).c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, false);

		std::string sReadBuffer;
		CURLcode result;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sReadBuffer);

		result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (result != CURLE_OK)
			std::cout << curl_easy_strerror(result) << std::endl;

		return sReadBuffer;
	}
}



std::string Http::GetVersion() 
{
	if (sRemoteVersion == "")
		sRemoteVersion = Get("version");

	return sRemoteVersion;
}


void Http::GetUpdate() 
{
	double nUpdateStart = time->millisecond();
	std::string sUpdateFiles = Get("update");
	std::string sUpdateFilesChecksums = Get("update_checksums");
	json jFiles = json::parse(sUpdateFiles);
	json jFilesChecksums = json::parse(sUpdateFilesChecksums);
	json jFilesToDownload = json::array();
	std::ofstream out;
	std::string sDelimeter = "==========================================";

	std::cout << sDelimeter << std::endl;
	std::cout << "Files in the installation package: " << jFiles << std::endl << std::endl;


	// Delete and rename any old files
	std::string sOldExecutableName = fs->sCurrentDirectory + "__bxc_os.old.exe";
	std::string sNewExecutableName = fs->sCurrentDirectory + "bxc_os.exe";

	// If .old file exists, remove it
	if (boost::filesystem::exists(sOldExecutableName))
		boost::filesystem::remove(fs->sCurrentDirectory + "__bxc_os.old.exe");

	// Rename the current .exe file to .old
	if (boost::filesystem::exists(sNewExecutableName))
		boost::filesystem::rename(fs->sCurrentDirectory + "bxc_os.exe", fs->sCurrentDirectory + "__bxc_os.old.exe");

	std::cout << "Checking files:" << std::endl;

	// Iterate over every file
	for (int f = 0; f < jFiles.size(); f++) 
	{
		std::string sFile = (std::string)jFiles[f];
		std::string sFilePath = fs->sCurrentDirectory + sFile;

		// ===========
		// Reading
		// ===========
		std::string sFileContent;
		std::ifstream readStream;
		readStream.open(sFilePath, std::ios::binary);

		// If file wasn't found, we need to download it
		if (readStream.fail())
		{
			jFilesToDownload.push_back(sFile);
			std::cout << "- File '" << sFile << "' wasn't found, added it to the download queue." << std::endl;
			continue;
		}
		// If file was found, assign it's contents to a variable
		if (readStream.good()) 
			sFileContent.assign(
				(std::istreambuf_iterator<char>(readStream)),
				(std::istreambuf_iterator<char>()));

		// Make a hex out of the file, since that's how we hash it on the server
		sFileContent = ToHex(sFileContent, false);

		// Close read stream
		readStream.close();

		// ===========
		// Hashing
		// ===========
		// Digest the file using sha256
		CryptoPP::SHA256 hash;
		byte digest[CryptoPP::SHA256::DIGESTSIZE];

		hash.CalculateDigest(digest, (byte*)sFileContent.c_str(), sFileContent.length());

		CryptoPP::HexEncoder encoder;
		std::string sHashedFileContent;
		encoder.Attach(new CryptoPP::StringSink(sHashedFileContent));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();

		// Put the hex into lowercase, because that's just how it's generated on the backend
		boost::to_lower(sHashedFileContent);

		// ===========
		// Comparing
		// ===========

		// If file checksum doesn't match with the online one, add the file to download queue
		if (sHashedFileContent != jFilesChecksums[sFile])
		{
			jFilesToDownload.push_back(sFile);
			std::cout << "- File's '" << sFile << "' checksum doesn't match, added it to the download queue." << std::endl;
		}
		else
			std::cout << "- File's '" << sFile << "' checksum matches." << std::endl;
	}
	
	std::cout << std::endl << sDelimeter << std::endl;
	std::cout << "Checking files done!" << std::endl
		      << "Files that are going to be downloaded: " << jFilesToDownload << std::endl
		      << "Downloading files: " << std::endl;






	// Downloads files in the queue
	for (auto & file : jFilesToDownload)
	{
		// Casts json value to string
		std::string sFile = (std::string)file;
		std::string sFilePath = fs->sCurrentDirectory + sFile;

		// Downloads the file
		std::string sFileContent = Get("update/" + sFile);
		

		std::cout << "- File '" << file << "' downloaded successfully" << std::endl;

		out.open(sFile, std::ofstream::binary);
		out << sFileContent;
		out.close();
	}


	double nUpdateEnd = time->millisecond();

	std::cout << std::endl << sDelimeter << std::endl;
	std::cout << "BXC OS version " << GetVersion() << " installed in " << (nUpdateEnd - nUpdateStart) / 1000 << " seconds. " << std::endl 
		      << "This window will automatically restart in about 30 seconds." << std::endl;
	Sleep(30000);
}