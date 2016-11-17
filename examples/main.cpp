#include <vk/client.hpp>
#include <iostream>
#include <map>
#include <string>
//client_id=5685143
int main() {

	setlocale(LC_ALL, "rus");
	std::string access_token;
	std::cout << "Hello! If you want to get the access_token please check the link below" << std::endl;
	std::cout << "https://oauth.vk.com/authorize?client_id=5685143&display=page&redirect_uri=http://vk.com/callback&scope=friends&response_type=token&v=5.59&state=1" << std::endl;
	std::cout << "Access_token: ";
	std::cin >> access_token;
	Vk::VkClient data({{"token", access_token }});
	data.check_connection();
	data.get_groups();
