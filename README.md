# Low-cost-IoT-Plug-Play

This a IoT Plug&Pluy solution for ESP32

It was developed with the objective of creating a low-cost and low-effort IoT solutions.
With X simple steps  you'll have an independent IoT device that can read values from sensors connected to it and send it to desired API endpoint.

You'll need:

 - An ESP32 with sensors
 - A REST API web service
 
On the code:

 - On node_conn_handler.cpp change the IP address on the endpoint to the IP address where your API is listening

First usage:
  
  - Open lowcostplugandplay file and upload it to the device
  - The device will start as AP and emit hotspot network. 
  - Connect to the network (SSID: ESP32-Access-Point , Password: 123456789) and go to 192.168.4.1.
  - Insert the needed data on the web page
  - Click submit. The device will restart, connect to WiFi, and start sending POST requests with the value read from the sensor
  
