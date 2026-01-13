#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


using namespace std::placeholders;


class AddTwoIntsServerNode : public rclcpp::Node 
{
public:
    AddTwoIntsServerNode() : Node("add_two_ints_server") 
    {
        server_ = this->create_service<example_interfaces::srv::AddTwoInts>( //tworzymy serwer i dodajemy callback
            "add_two_ints", 
            std::bind(&AddTwoIntsServerNode::callbackAddTwoInts, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Add Two Ints Service has been started.");
    }




private:    //kiedy klient wysle zapytanie zostanie przetworzone to w tym kodzie i zwrocone do klienta
    void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request, 
                            const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "%d + %d = %d", 
                    (int)request->a, (int)request->b, (int)response->sum);
    }


    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); //inicjacja komunikacji ros2
    auto node = std::make_shared<AddTwoIntsServerNode>();   //stworzylismy odniesienie do Node
    rclcpp::spin(node); //pozwala na ciagle dzialanie Node
    rclcpp::shutdown();
    return 0;
}