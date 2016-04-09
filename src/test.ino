#include <SPI.h>
#include <EthernetV2_0.h>

#define W5200_CS 10
#define SDCARD_CS 4

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
String host = "api.ipify.org";

EthernetClient client;

void setup(){
    Serial.begin(9600);
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);

    if (Ethernet.begin(mac) == 0){
        Serial.println("Failed to configure Ethernet using DHCP");
        while (1);
    }
    delay(1000);

    char h[host.length() + 1];
    host.toCharArray(h, host.length() + 1);

    Serial.println("Connecting to " + host);

    if (client.connect(h, 80)){
        Serial.println("Connected");
        client.println("GET / HTTP/1.1");
        client.println("Host: " + host);
        client.println();
    }
    else {
        Serial.println("Connection failed");
    }
}

void loop(){
    if (client.available()){
        char c = client.read();
        Serial.print(c);
    }

    if (!client.connected()) {
        Serial.println();
        Serial.println("Disconnecting");
        client.stop();
        while (1);
    }
}
