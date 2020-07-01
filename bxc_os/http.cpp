#include "http.h"

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s)
{
	s->append(static_cast<char *>(ptr), size*nmemb);
	return size * nmemb;
}

string Http::Get(string endpoint)
{
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, (sUrl + endpoint).c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, false);

		string response_string;
		CURLcode result;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

		result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (result != CURLE_OK)
		cout << curl_easy_strerror(result) << endl;

		return response_string;
	}
}



string Http::GetVersion() {
	if (sRemoteVersion == "")
		sRemoteVersion = Get("version");

	cout << "Remote version: " << sRemoteVersion << endl;
	return sRemoteVersion;
}