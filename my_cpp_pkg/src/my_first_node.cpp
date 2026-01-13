#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello World");
        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                            std::bind(&MyNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
        counter_++;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;  
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); // INICJACJA KOMUNIKACJI DLA ROS2
    //auto node = std::make_shared<rclcpp::Node>("cpp_test");
    // RCLCPP_INFO(node->get_logger(), "Hello world"); //wyswietlanie informacji
    
    auto node = std::make_shared<MyNode>(); //projektujemy obiekt
    rclcpp::spin(node);  //#utrzyma "node" aby dzialal do czasu wylaczenia przez ctrl+c
    rclcpp::shutdown();
    return 0;
}