#include "stdafx.h"
#include "VkClient.h"
#include <iostream>
#include <curl/curl.h>

namespace Vk {
		
   auto VkClient::check_connection()-> bool
		{

			CURL *curl = curl_easy_init();
			if (curl) {
				std::string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
				CURLcode res;
				curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/users.get?");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
				res = curl_easy_perform(curl);
				if (res == CURLE_OK) {
					std::cout << "Connected successfully" << std::endl;
					return true;
				}
				curl_easy_cleanup(curl);
			}
		};
}
