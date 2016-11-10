#include <map>
#include <string>
#include <iostream>
#include <curl/curl.h>
namespace Vk {
	class VkClient {
	public:
		using dict_t = std::map<std::string, std::string>;

		VkClient() {};
		VkClient(dict_t settings) : settings_(settings) {};
		auto check_connection() -> bool;
		auto groups_get()-> void;
		auto friends_getAppUsers()->void;
		static auto func(char* ptr, size_t size, size_t nmemb, std::string* link)->size_t;
	private:
		dict_t settings_;
	};
}

