#include <map>
#include <string>
namespace Vk {
	class VkClient {
	public:
		using dict_t = std::map<std::string, std::string>;

		VkClient() {};
		VkClient(dict_t settings) : settings_(settings) {};
		auto check_connection() -> bool;

	private:
		dict_t settings_;
	};
}
