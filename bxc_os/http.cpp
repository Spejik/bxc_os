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

bool Http::GetResources() {
	string sResources = Get("resources");
	string sFile = sAppdataDirectory + "resources.pak";
	
	ofstream out;
	out.open(sFile, ofstream::binary);
	out << sResources;
	out.close();

	return true;
}

bool Http::GetUpdate() {
	stringstream sUpdateFiles(Get("update"));
	vector<string> vUpdateFiles;

	// Splits string at every ";", so that we get only the file names
	while (sUpdateFiles.good())
	{
		string sFile;
		getline(sUpdateFiles, sFile, ';');
		vUpdateFiles.push_back(sFile);
	}

	ofstream out;

	// Individually gets each file and puts it into a file
	for (string file : vUpdateFiles)
	{
		string sResources = Get("update/" + file);
		string sPath = filesystem::current_path().string();
		string sFile = sPath + file;

		out.open(sFile, ofstream::binary);
		out << sResources;
		out.close();
	}

	return true;
}