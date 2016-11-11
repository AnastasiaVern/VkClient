
#include <vk/client.hpp"
#include "catch.hpp"
#include <iostream>;
SCENARIO("checking connection")
{
    GIVEN("token")
    {
        std::map<std::string,std::string> failed_token{{"token", "glkkfglkglvlkcx"}};

        WHEN("initialization")
        {
            Vk::VkClient user(failed_token);

            THEN("returning false")
            {
                REQUIRE(!user.check_connection());
            }
        }
    }

    GIVEN("correct token")
    {
    std::string token;
    std::cout<<"Your token: ";
    std::cin>>token;
        std::map<std::string, std::string> correct_token{{"token"},token};
        WHEN("initializing")
        {
            Vk::VkClient user(correct_token);
            THEN("returning true")
            {
                REQUIRE(user.check_connection());
            }
        }
    }
}
