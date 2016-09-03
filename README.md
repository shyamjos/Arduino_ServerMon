# Arduino Linux Monitor
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
8. Upload the sketch and use serial monitor for debugging

##Issues
I have only tested it in my debian/nginx VPS , you may need to adjust the ```HTTP_HEADER_OFFSET``` value to remove any unwanted http headers when you are running different web server.

You can use seial monitor for debugging.
