#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64


class NumberPublisherNode(Node): 
    def __init__(self):
        super().__init__("number_publisher") 
        self.counter_ = 2
        self.publishers_ = self.create_publisher(Int64, "number", 10) #10 - wielkosc kolejki 
        self.timer_ = self.create_timer(1.0, self.publish_number) #pozwala wysyłać wiadomość co 1s.
        self.get_logger().info("Number publisher has been started")

    def publish_number(self):
        msg = Int64()
        msg.data = self.counter_ 
        self.publishers_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()