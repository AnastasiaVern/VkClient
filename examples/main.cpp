#include <vk/client.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>

int main() {

	setlocale(LC_ALL, "rus");
	std::string flag = "-v";
	std::string users_flag;
	std::string access_token;
	std::cout << "Hello! If you want to get the access_token please check the link below" << std::endl;
	std::cout << "https://oauth.vk.com/authorize?client_id=5685143&display=page&redirect_uri=http://vk.com/callback&scope=friends&response_type=token&v=5.59&state=1" << std::endl;
	std::cout << "Access_token: ";
	std::cin >> access_token;
	Vk::VkClient data({ { "token", access_token } });
	if (data.check_connection() == TRUE) 
	{
		int n;
		data.print_groups(data.get_groups());
		std::cout << "Please enter the number of threads: " << std::endl;
		std::cin >> n;
		std::cout << "Flag: ";
		std::cin >> users_flag;
		if (flag == users_flag)
		{
			data.start_streaming(n);
		}
	};
	system("pause");
	return 0;
}
