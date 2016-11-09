#include "stdafx.h"
#include "VkClient.h"
#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

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
   auto VkClient::groups_get()->void 
   {
	
	   CURL *curl = curl_easy_init();
	   if (curl) 
	   {
		   std::string data_to_send = "user_ids=asyavern&extended=0&filter=groups&fields&offset=5&count=4&access_token=" + settings_["token"] + "&v=5.59";
		   CURLcode res;
		   std::string link = "";
		   curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/groups.get?");
		   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
		   curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
		   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
		   curl_easy_setopt(curl, CURLOPT_WRITEDATA, link);
		   res = curl_easy_perform(curl);
		   if (res == CURLE_OK) 
		   {
			   //////////////MISTAKE///////////////////
			 nlohmann::json j_param = nlohmann::json::parse(link);
		   };
	   }
   }
   size_t VkClient::func(char* ptr, size_t size, size_t nmemb, std::string &link)
   {
	   link.append(ptr, size * nmemb);
	   size_t  res = size * nmemb;
	   return res;
   }
}
