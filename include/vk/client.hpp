#include <map>
#include <string>
#include <iostream>
#include <curl/curl.h>
using dict_t = std::map<std::string, std::string>;
namespace Vk {
	class VkClient {
	private:
		dict_t settings_;
	public:
		VkClient() {};
		VkClient(dict_t settings) 
		{
			settings_ = settings;
		}

		auto check_connection() -> bool 
		{
			CURL *curl = curl_easy_init();
			if (curl) {
				CURLcode res;
				curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getInfo()");

				res = curl_easy_perform(curl);
				if (res == CURLE_OK) {
					std::cout << "Connected successfully"<< std::endl;
					return true;
				}
				curl_easy_cleanup(curl);
			}
		};
	};
}
