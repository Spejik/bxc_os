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
	std::stringstream sUpdateFiles(Get("update"));
	std::vector<std::string> vUpdateFiles;
	std::cout << "Available update files: " << sUpdateFiles.str() <<  std::endl;

	// Splits string at every ";", so that we get only the file names
	while (sUpdateFiles.good())
	{
		std::string sFile;
		getline(sUpdateFiles, sFile, ';');
		vUpdateFiles.push_back(sFile);
	}

	// If there is .old file, delete it, so we can rename the current file to that name
	boost::filesystem::remove(fs->sCurrentDirectory + "__bxc_os.old.exe");

	// Renames the executable file
	boost::filesystem::rename(fs->sCurrentDirectory + "bxc_os.exe", fs->sCurrentDirectory + "__bxc_os.old.exe");

	std::ofstream out;

	// Individually gets each file and puts it into a file
	for (auto & file : vUpdateFiles)
	{
		std::string sResources = Get("update/" + file);
		std::string sFile = fs->sCurrentDirectory + file;

		std::cout << "Downloaded >" << file <<  std::endl;

		out.open(sFile, std::ofstream::binary);
		out << sResources;
		out.close();
	}

	int nUpdateEnd = time->millisecond();
	return nUpdateEnd - nUpdateStart;
}