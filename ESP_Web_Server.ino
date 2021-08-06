#include <ESP8266WiFi.h>

WiFiClient client; // defines Client
WiFiServer server(80); // defines Server ; 80 

#define led D5

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Scorpio","gemini2810");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting... ");
    delay(200);
  }

  Serial.println();
  Serial.println();

  Serial.println("Node MCU is succesfully Connected to WiFi");

  Serial.println(WiFi.localIP());

  server.begin();

  pinMode(led,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();
  if(client == 1)
  {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request == "GET /led_on HTTP/1.1")
    {
      digitalWrite(led,HIGH);
    }
    if (request == "GET /led_off HTTP/1.1")
    {
      digitalWrite(led,LOW);
    }
  }

}
