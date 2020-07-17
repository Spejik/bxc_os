#include "http.h"



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
			std::cout << curl_easy_strerror(result) <<  std::endl;

		return sReadBuffer;
	}
}



std::string Http::GetVersion() {
	if (sRemoteVersion == "")
		sRemoteVersion = Get("version");

	return sRemoteVersion;
}


float Http::GetUpdate() {
	using hex_lower = cppcodec::hex_lower;

	int nUpdateStart = time->millisecond();
	std::string sUpdateFiles = Get("update");
	std::string sUpdateFilesChecksums = Get("update_checksums");
	json jFiles = json::parse(sUpdateFiles);
	json jFilesChecksums = json::parse(sUpdateFilesChecksums);
	json jFilesToDownload = json::array();
	std::ofstream out;

	std::cout << "Updateable files: " << jFiles << std::endl;

	// Delete and rename any old files
	//boost::filesystem::remove(fs->sCurrentDirectory + "__bxc_os.old.exe");
	//boost::filesystem::rename(fs->sCurrentDirectory + "bxc_os.exe", fs->sCurrentDirectory + "__bxc_os.old.exe");

	std::cout << fs->sCurrentDirectory << std::endl;
	// Iterate over every file
	for (int f = 0; f < jFiles.size(); f++) 
	{
		std::string sFile = (std::string)jFiles[f];
		std::string sFilePath = fs->sCurrentDirectory + sFile;

		std::cout << sFile << std::endl;

		// Read file
		std::string sFileContent;
		std::ifstream readStream;
		readStream.open(sFilePath, std::ios::binary);

		if (readStream.fail())
			std::cout << "bxc::http::GetUpdate() - failed opening " << sFile << std::endl;
		if (readStream.good()) 
			sFileContent.assign(
				(std::istreambuf_iterator<char>(readStream)),
				(std::istreambuf_iterator<char>()));

		// Close read stream
		readStream.close();

		// Digest the file using sha256
		CryptoPP::SHA256 hash;
		byte digest[CryptoPP::SHA256::DIGESTSIZE];

		hash.CalculateDigest(digest, (byte*)sFileContentHex.c_str(), sFileContentHex.length());

		CryptoPP::HexEncoder encoder;
		std::string output;
		encoder.Attach(new CryptoPP::StringSink(output));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();

		// Put the hex into lowercase, because that's just how it's generated on the backend
		boost::to_lower(output);

		// If file checksum doesn't match with the online one, add the file to download queue
		if (output != jFilesChecksums[sFile])
		{
			jFilesToDownload.push_back(sFile);
			std::cout << "File's " << sFile << " checksum doesn't match, added it to the download queue." << std::endl;
		}
		else
			std::cout << "File's " << sFile << " checksum matches." << std::endl;

		std::cout << output << std::endl << std::endl;
	}
	
	

	// Gets each file and puts it into a file
	/*for (auto & file : vUpdateFiles)
	{
		std::string sResources = Get("update/" + file);
		std::string sFile = fs->sCurrentDirectory + file;

		std::cout << "Downloaded >" << file <<  std::endl;

		out.open(sFile, std::ofstream::binary);
		out << sResources;
		out.close();
	}*/

	int nUpdateEnd = time->millisecond();
	return nUpdateEnd - nUpdateStart;
}