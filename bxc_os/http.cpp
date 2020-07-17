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
	int nUpdateStart = time->millisecond();
	std::string sUpdateFiles = Get("update");
	std::string sUpdateFilesChecksums = Get("update_checksums");
	json vFiles = json::parse(sUpdateFiles);
	json vFilesChecksums = json::parse(sUpdateFilesChecksums);
	std::ofstream out;

	std::cout << "Updateable files: " << vFiles << std::endl;

	// Delete and rename any old files
	//boost::filesystem::remove(fs->sCurrentDirectory + "__bxc_os.old.exe");
	//boost::filesystem::rename(fs->sCurrentDirectory + "bxc_os.exe", fs->sCurrentDirectory + "__bxc_os.old.exe");

	std::cout << fs->sCurrentDirectory << std::endl;
	// Iterate over every file
	for (int f = 0; f < vFiles.size(); f++) {
		std::cout << vFiles[f] << std::endl;

		// Read file

		std::ifstream file(fs->sCurrentDirectory + (std::string)vFiles[f], std::ios::binary);
		std::string sFileContent;

		file.read(sFileContent.data(), RAND_MAX);
		file.close();

		std::cout << sFileContent << std::endl;

		// Digest the file using sha256
		std::string digest;
		CryptoPP::SHA256 hash;

		CryptoPP::StringSource foo(sFileContent, true,
			new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(digest))));

		std::cout << digest << std::endl;
	}
	
	

	// Individually gets each file and puts it into a file
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