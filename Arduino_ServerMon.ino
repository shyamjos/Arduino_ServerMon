// Monitoring Linux server with arduino uno, LCD, ethernet module and PHP.
// Created 27 Aug 2016 by Shyam Jos <shyamjosepp@gmail.com> http://shyamjos.com

// include the library code:
#include <EtherCard.h>
#include <LiquidCrystal.h>

// Adjust HTTP_HEADER_OFFSET value to remove unwanted http headers
#define HTTP_HEADER_OFFSET 155 

// initialize the lcd library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 6, 7, 5, 9);
// pin 8 will control the backlight of lcd
int backLight = 8;    

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 }; 
// ethernet interface ip address // comment below line when using DHCP
//static byte myip[] = { 192,168,1,200 }; 
// gateway ip address for ethernet module // comment below line when using DHCP
//static byte gwip[] = { 192,168,1,1 }; 
// dns ip address for ethernet module // comment below line when using DHCP
//static byte dnsip[] = { 192,168,1,1 };
// set remote server ip address
static byte hisip[] = { 192, 198, 95, 71 };

// tcp/ip send and receive buffer
byte Ethernet::buffer[500];
static uint32_t timer;

// set remote server ip address (eg:192.168.1.2)
const char server[] PROGMEM = "192.198.2.2"; 

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
Ethernet::buffer[off+300] = 0;

// Final data after removing unwanted http headers by adjusting HTTP_HEADER_OFFSET  value
String data = (const char*) Ethernet::buffer + off + HTTP_HEADER_OFFSET;

// Seprate and assign values to variables based on ";" delimiter
int firstCommaIndex = data.indexOf(';');
int secondCommaIndex = data.indexOf(';', firstCommaIndex+1);
int thirdCommaIndex = data.indexOf(';', secondCommaIndex+1);
String uptime = data.substring(0, firstCommaIndex);
String load = data.substring(firstCommaIndex+1, secondCommaIndex);
String ram = data.substring(secondCommaIndex+1,thirdCommaIndex);
String disk = data.substring(thirdCommaIndex+1);

// Print final data after removing unwanted http headers to serial for debugging
Serial.print("# Adjust HTTP_HEADER_OFFSET value to remove unwanted http headers #");
Serial.print((const char*) Ethernet::buffer + off + HTTP_HEADER_OFFSET); 
Serial.print('\n');

// Print Final values to serial for debugging
Serial.print('\n');
Serial.print("Server Readings");
Serial.print('\n');
Serial.print("Uptime: ");
Serial.print(uptime);
Serial.print('\n');
Serial.print("Load:");
Serial.print(load);
Serial.print('\n');
Serial.print("Memory:");
Serial.print(ram);
Serial.print('\n');
Serial.print("Disk:");
Serial.print(disk);
Serial.print('\n');


// Print server Uptime value to lcd
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Uptime:");
lcd.setCursor(0,1); 
String uptime_value=uptime;
//remove whitespaces
uptime_value.trim();
//set 16 character limit for lcd
uptime_value.remove(16, 50);
lcd.print(uptime_value);     
delay (3000);

// Print server Load value to lcd
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Load:");
lcd.setCursor(0,1); 
String load_value=load;
//remove whitespaces
load_value.trim();
//set 16 character limit for lcd 
load_value.remove(16, 50);
lcd.print(load_value);     
delay (3000);

// Print server Free Memory value to lcd
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Free Memory: ");
lcd.setCursor(0,1); 
String ram_value=ram;
//remove whitespaces
ram_value.trim();
//set 16 character limit for lcd
ram_value.remove(16, 50);
lcd.print(ram_value);     
delay (3000);

// Print server Free Disk space value to lcd
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Free Disk Space:");
lcd.setCursor(0,1); 
String disk_value=disk;
//remove whitespaces
disk_value.trim();
//set 16 character limit for lcd
disk_value.remove(16, 50);
lcd.print(disk_value);     
delay (3000);

// Show this message until client request is completed
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Server Mon v1.0");
lcd.setCursor(0,1); //set cursor to top left corner
lcd.print("Loading >> >> >>");     

}

void setup () {
    //set serial set baud rate
    Serial.begin(57600);
   
   //set lcd backlight pin
    pinMode(backLight, OUTPUT);
    digitalWrite(backLight, HIGH);
    
   // check if ethernet module is connected 
   if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
   
   // set  remote server ip 
    ether.copyIp(ether.hisip, hisip);
   
   // uncomment below line to set static IP for ethernet module // comment below line when using DHCP
   // ether.staticSetup(myip, gwip, dnsip);
    
    // comment below lines when using static IP
     Serial.println(F("Setting up DHCP"));
     if (!ether.dhcpSetup())
     Serial.println(F("DHCP failed"));
   
    // Print network details to serial for debugging
    ether.printIp("My IP: ", ether.myip);
    ether.printIp("Netmask: ", ether.netmask);
    ether.printIp("GW IP: ", ether.gwip);
    ether.printIp("DNS IP: ", ether.dnsip); 
    ether.parseIp(ether.hisip, "192.198.2.2");
    ether.printIp("SRV: ", ether.hisip);
    
}

void loop () {

  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
     timer = millis() + 5000;
     Serial.println();
     
     //server port (eg:80)
     ether.hisport = 80;
     // path to php script 
     ether.browseUrl(PSTR("/"), "data.php", server, my_callback);

  }
}
