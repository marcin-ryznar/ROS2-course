#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); //zainicjowano komunikacje ros2
    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client_no_oop"); //tworzymy node
    
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints"); //tworzymy klienta
    while (!client->wait_for_service(1s)) //jesli po sekundzie nie dostanie odp od serweru zaczyna wykonywac kod
    {
        RCLCPP_WARN(node->get_logger(), "Waiting for the server...");
    }
    //w momeencie gdy serwis działa
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>(); //tworzymy zapytanie
    request->a = 6;
    request->b = 2;

    auto future = client->async_send_request(request); //wysylamy zapytanie do serweru asynchroniccznie
    rclcpp::spin_until_future_complete(node, future); //program dziala caly czas do momentu wykonania future, czyli wykona sie w momencie gdy wyslemy zapytanie
    
    auto response = future.get(); // otrzymujemy wiadomosc z serweru
    RCLCPP_INFO(node->get_logger(), "%d + %d = %d",
                        (int)request->a, (int)request->b, (int)response->sum); // zapisujemy wiadomosc z serweru w takim formacie

    rclcpp::shutdown(); //zakonczono komunikacje ros2
    return 0;
}