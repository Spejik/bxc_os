#include "http.h"

size_t Http::WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string Http::Get(string endpoint)
{
	curl_global_init(CURL_GLOBAL_ALL);

	CURL* curl = curl_easy_init();
	string readBuffer;

	curl_easy_setopt(curl, CURLOPT_URL, _url + endpoint);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_perform(curl);

	cout << readBuffer << endl;

	return readBuffer;
}



string Http::GetVersion() {
	if (_REMOTE_VERSION == "")
		_REMOTE_VERSION = Get("version");

	cout << "Remote version: " << _REMOTE_VERSION << endl;
	return _REMOTE_VERSION;
}