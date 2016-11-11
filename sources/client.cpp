#include "VkClient.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

namespace Vk {
	auto VkClient::check_connection()-> bool
	{

		CURL *curl = curl_easy_init();
		if (curl) {
			std::string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
			CURLcode res;
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getInfo?");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
			res = curl_easy_perform(curl);
			if (res == CURLE_OK) {
				long response_code;
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
				std::cout << std::endl;
				std::cout << response_code << std::endl;
				return true;
			}
			curl_easy_cleanup(curl);
		}
		return false;
	};

	//user_id extended filter fields (if extended 1) offset count
	//https://api.vk.com/method/groups.get?user_ids=asyavern&extended=0&filter=groups&fields&offset=5&count=4&access_token=2f36e6fea00c8115ed5c771dd3904b3f347cf0356e652606c625890fd40906d75bc9f7b82339133cefc10&v=5.59
	auto VkClient::groups_get()->void
	{

		CURL *curl = curl_easy_init();
		if (curl)
		{
			std::string data_to_send = "extended=0&filter=groups&fields&offset=5&count=4&access_token=" + settings_["token"] + "&v=5.59";
			CURLcode res;
			std::string link = "";
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/groups.get?");
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &link);
			res = curl_easy_perform(curl);
			if (res == CURLE_OK)
			{
			/*	nlohmann::json j_param = nlohmann::json::parse(link.c_str());
				nlohmann::json j_response = j_param["response"];

				if (!j_response.empty())
				{
					std::cout << "response: " << j_response << std::endl;
*/

					long response_code;
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
					//	std::cout << std::endl;
						//std::cout << response_code << std::endl;
				}
				curl_easy_cleanup(curl);
			};
		}
		
	};
	auto VkClient::func(char* ptr, size_t size, size_t nmemb, std::string* link) -> size_t
	{
		*link += ptr;
		return size*nmemb;
	}
}
