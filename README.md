
# Arduino Linux Monitor [![Build Status](https://travis-ci.org/shyamjos/Arduino-Linux-Monitor.svg?branch=master)](https://travis-ci.org/shyamjos/Arduino-Linux-Monitor)
Monitoring linux server using arduino, ethernet module, LCD and PHP.

##Demo 
![demo](http://i.imgur.com/CNQ7JSf.gif "demo")

##Requirements
1. An Arduino Uno
2. A Linux server with php support (debian/nginx)
3. Ethernet module (ENC28J60)
4. [EtherCard Library](https://github.com/jcw/ethercard) 
5. 16 x 2 LCD screen

##Setup
1. Download arduino sketch
2. install [EtherCard Library](https://github.com/jcw/ethercard)
3. Configure the lcd pin connections
4. Configure Ethernet module pin connections
 * VCC - 3.3V  
 * GND - GND  
 * SCK - Pin 13  
 * SO  - Pin 12  
 * SI  - Pin 11  
 * CS  - Pin  10
5. Upload data.php to your web server 
6. update remote server IP address and path to php script in arduino sketch
7. DHCP is enabled by default , You can set static IP for arduino if needed
8. Connect the ethernet cable and upload the sketch to arduino
9. Adjust the  ```HTTP_HEADER_OFFSET``` value if the readings looks incorrect
10. Use serial monitor for debugging

##Issues
I have only tested it in my debian/nginx VPS , you may need to adjust the ```HTTP_HEADER_OFFSET``` value to remove any unwanted http headers.
