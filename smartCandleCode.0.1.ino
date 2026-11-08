
// Borrowed code from chat gpt to connect to wifi:
#include <WiFiS3.h>

char ssid[] = "GL-SFT1200-67d";
char pass[] = "goodlife";

IPAddress shellyIP(192, 168, 8, 160);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("Connecting to WiFi...");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Retrying...");
    delay(5000);
  }

  Serial.println("Connected!");

  delay(2000);

  Serial.print("WiFi Status: ");
  Serial.println(WiFi.status());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if(WiFi.localIP() == IPAddress(0,0,0,0)){
    Serial.println("Network Configuration FAIL!");
  }

  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());

  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
//connecting to shelly
  if (client.connect(shellyIP, 80)) {
    Serial.println("Connected to Shelly!");
}
else {
    Serial.println("Connection failed!");
}
//turning it on initially:
client.println("GET /rpc/Switch.Set?id=0&on=true HTTP/1.1");
client.println("Host: 1.92.168.8.163");
client.println("Connection: Close");
client.println();
//reading the response from shelly: 
while (client.connected()|| client.available()){
  if(client.available()){ //checking if there are unread messages from shelly
    char c = client.read();
    Serial.print(c);
  }
}
client.stop();
}

void loop() {
}