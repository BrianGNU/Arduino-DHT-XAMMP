#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0xA9, 0xC0 }; //Setting MAC Address
#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

float temperature;
char server[] = "192.168.2.51";
EthernetClient client;

/* Setup for Ethernet */

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac);
  }
  delay(1000);
}
//------------------------------------------------------------------------------

/* Infinite Loop */
void loop(){
  temperature = dht.readTemperature(); 
  Sending_To_db_arduino(); 
  delay(2000); // interval
}


  void Sending_To_db_arduino()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
      // Make a HTTP request:
    // Serial.print(GET + /insert_temp.php +" "+ (temperature));
    client.print("GET /insert_temp.php?");     //YOUR URL
    client.print("temperature=");
    client.print(temperature);
    Serial.println("Temperature is");
    Serial.println(temperature);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.2.51");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }