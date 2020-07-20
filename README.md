# Low-cost-IoT-Plug-Play

This project was developed for the Computer Science Project of the Computer Engineering degree at the technology and Management School (ESTG) of the Polytechnic Institute of Leiria by the students Octávio Braga and Tiago Ferreira under the guidance of Professor António Manuel de Jesus Pereira and Professor Luís Alexandre Lopes Frazão. 


This project presents an IoT Plug&Play solution for the ESP32 device. 

It was developed with the objective of creating a low-cost and low-effort IoT solutions.
With 5 simple steps  you'll have an independent IoT device that can read values from sensors connected to it and send it to desired API endpoint.

You'll need:

 - An ESP32 and any sensor of your choice. 
 - A REST API web service. 
 
On the code:

 - On node_conn_handler.cpp change the IP address on the endpoint to the IP address where your API is listening

First usage:
  
  - Open lowcostplugandplay file and upload it to the device;
  - The device will start as an AP device, creating a hotspot wireless network;
  - With other device(Computer, smartphone, etc) connect to the network (SSID: ESP32-Access-Point , Password: 123456789) and access the URL: http://192.168.4.1;
  - Fill the form on the web page (existing Wi-Fi network information, and user information)
  - Click submit. 
  - The ESP32 device will restart, connect to your existing Wi-Fi network, and start sending HTTP POST requests with the value read by the sensor.
  
