#!/usr/bin/env python3
import rclpy
from rclpy.node import Node 

class MyNode(Node):
    def __init__(self):
        super().__init__("py_test")
        self.counter_ = 0 # licznik czasu
        self.get_logger().info("Hello world")
        self.create_timer(1.0, self.timer_callback) #zainicjowanie timera

    def timer_callback(self): #funkcja timera
        self.get_logger().info("Hello aaaa" + str(self.counter_))
        self.counter_ += 1


def main(args=None):
    rclpy.init(args=args)
    # node = Node("py_test")
    # node.get_logger().info("Hello world") #informujaca wiadomosc na poczatku programu
    node = MyNode()
    rclpy.spin(node) #utrzyma "node" aby dzialal do czasu wylaczenia przez ctrl+c
    rclpy.shutdown() #wylacza program


if __name__ == "__main__":
    main()