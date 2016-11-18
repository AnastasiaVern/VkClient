#include <vk/client.hpp>
#include <iostream>
#include <string>
#include <exception> 
#include <curl/curl.h>
#include <vk/json.hpp>
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

    auto VkClient::get_groups()->nlohmann::json
    {
        CURL *curl = curl_easy_init();
        if (curl)
        {
            std::string data_to_send = "extended=1&offset=5&count=4&access_token="+ settings_["token"] + "&v=5.59";
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
                try
                {
                    nlohmann::json j_result = nlohmann::json::parse(link.c_str());
                    nlohmann::json j_resp = j_result["response"];
                if (!j_resp.empty())
                {
                    size_t count= j_resp["count"];
                    std::cout << "response {" << std::endl;
                    std::cout << "count: " << count << std::endl;
                    if (count)
                    {
                        nlohmann::json g_r= j_resp["items"];
                        for (nlohmann::json::iterator it = g_r.begin(); it != g_r.end(); ++it)
                        {
                            int g_id = it.value()["id"];
                            std::cout << "id: " << g_id <<std::endl;
                            std::string g_name = it.value()["name"];
                            std::cout << "name: " << "'"<< g_name<< "'" <<std::endl;
                            std::string g_screen_name = it.value()["screen_name"];
                            std::cout << "screen_name: " <<"'" <<g_screen_name<<"'" << std::endl;
                            int g_closed = it.value()["is_closed"];
                            std::cout << "is_closed: " << g_closed << std::endl;
                            std::string g_type= it.value()["type"];
                            std::cout << "type: " <<"'"<< g_type <<"'" << std::endl;
                        }
                        std::cout << "}" << std::endl;
                    }
                    else
                    {
                        nlohmann::json j_err = j_result["error"];
                        std::cerr << "error: " << j_err << std::endl;
                        return nullptr;
                    }
                }
                }
                catch (std::exception&)
                {
                    std::cerr << "Object is not JSON!!!" << std::endl;
                    return false;
                }
            };
            curl_easy_cleanup(curl);
        }   
    };
    
    auto VkClient::func(char* ptr, size_t size, size_t nmemb, std::string* link) -> size_t
    {
        *link += ptr;
        return size*nmemb;
    }
}
