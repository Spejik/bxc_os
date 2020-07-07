#include "http.h"



static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string Http::Get(string endpoint)
{
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, (sUrl + endpoint).c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, false);

		string sReadBuffer;
		CURLcode result;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sReadBuffer);

		result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (result != CURLE_OK)
			cout << curl_easy_strerror(result) << endl;

		return sReadBuffer;
	}
}



string Http::GetVersion() {
	if (sRemoteVersion == "")
		sRemoteVersion = Get("version");

	return sRemoteVersion;
}


float Http::GetUpdate() {
	float nUpdateStart = nTimeMs();
	stringstream sUpdateFiles(Get("update"));
	vector<string> vUpdateFiles;
	cout << "Available update files: " << sUpdateFiles.str() << endl;

	// Splits string at every ";", so that we get only the file names
	while (sUpdateFiles.good())
	{
		string sFile;
		getline(sUpdateFiles, sFile, ';');
		vUpdateFiles.push_back(sFile);
	}

	// If there is bxc_os.old file, delete it, so we can rename the current file to that name
	filesystem::remove(sDirectory + "bxc_os.old.exe");

	// Renames the executable file
	filesystem::rename(sDirectory + "bxc_os.exe", sDirectory + "bxc_os.old.exe");

	ofstream out;

	// Individually gets each file and puts it into a file
	for (string file : vUpdateFiles)
	{
		string sResources = Get("update/" + file);
		string sFile = sDirectory + file;

		cout << "Downloaded " << file << endl;

		out.open(sFile, ofstream::binary);
		out << sResources;
		out.close();
	}

	float nUpdateEnd = nTimeMs();
	return nUpdateEnd - nUpdateStart;
}