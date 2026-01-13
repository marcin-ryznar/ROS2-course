#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
#STRUKTURA KODU CLIENTA JEST INNA NIZ WCZESNIEJ /INNA NIZ SERWER
#ten kod jest idealny do sprawdzenia czy działa polaczenie z serwerem

def main(args=None):
    rclpy.init(args=args) #inicjacja komunikacji ros2
    node = Node("add_two_ints_client_no_oop")

    #tworzenie funkcji która informuje o tym że serwer nie działa
    client = node.create_client(AddTwoInts, "add_two_ints") #stworzenie klienta
    while not client.wait_for_service(1.0):
        node.get_logger().warn("Waiting for Add Two Ints server...")

    #stworzenie request
    request = AddTwoInts.Request()
    request.a = 3
    request.b = 8

    
    future = client.call_async(request) #wysłanie request
    rclpy.spin_until_future_complete(node, future) #działaj do momentu otrzymania odpowiedzi od serweru
    
    response = future.result() #otrzymanie odpowiedzi od serweru
    node.get_logger().info(str(request.a) + " + " +
                           str(request.b) + " + " + str(response.sum)) #wypisanie odpowiedzi


    rclpy.shutdown() #wyłączenie komunikacji ros2


if __name__ == "__main__":
    main()