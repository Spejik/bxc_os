#include "http.h"

size_t Http::WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string Http::Get(string endpoint)
{
	curl_global_init(CURL_GLOBAL_ALL);

	CURL* easyhandle = curl_easy_init();
	std::string readBuffer;

	curl_easy_setopt(easyhandle, CURLOPT_URL, _url + endpoint);
	curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_perform(easyhandle);

	cout << readBuffer << endl;

	return readBuffer;

	/*auto curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, _url + endpoint);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_USERPWD, _auth);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

		string response_string;
		string header_string;

		char* url;
		long response_code;
		double elapsed;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
		curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
		curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl = NULL;

		cout << "Curl " << endpoint << ": " << response_string << endl;
		return "";
	}
	else
	{
		cout << "curl_easy_init() failed" << endl;
		throw new exception();
		return "";
	}*/
}



string Http::GetVersion() {
	if (_REMOTE_VERSION == "")
		_REMOTE_VERSION = Get("version");

	cout << "Remote version: " << _REMOTE_VERSION << endl;
	return _REMOTE_VERSION;
}