#include "http.h"


string Http::Get(string endpoint)
{
	string url = _url + endpoint;
	cout << url << endl;

	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

		std::string response_string;
		std::string header_string;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

		char* url;
		long response_code;
		double elapsed;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
		curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
		curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);


		cout << response_string << endl;
		return response_string;
	}
}



string Http::GetVersion() {
	if (_REMOTE_VERSION == "")
		_REMOTE_VERSION = Get("version");

	cout << "Remote version: " << _REMOTE_VERSION << endl;
	return _REMOTE_VERSION;
}