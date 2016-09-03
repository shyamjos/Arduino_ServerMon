# Arduino Linux Monitor
Monitoring linux server using arduino, ethernet module, LCD and PHP.

##Demo 
![demo](http://i.imgur.com/CNQ7JSf.gif "demo")

##Requirements
1. An Arduino Uno
2. A Linux server with php support
3. Ethernet module (ENC28J60)
4. [EtherCard Library](https://github.com/jcw/ethercard) 
5. 16 x 2 LCD screen

##Setup
1. install [EtherCard Library](https://github.com/jcw/ethercard)
2. Configure the lcd pin connections
3. Configure Ethernet module pin connections

VCC -   3.3V
GND - GND  
SCK - Pin 13  
SO  - Pin 12  
SI  - Pin 11  
CS  - Pin  10

##Debugging


Ps: I have only tested it my debian server 

