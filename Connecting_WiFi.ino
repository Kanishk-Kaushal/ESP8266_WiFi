#include <ESP8266WiFi.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("WiFi_Name","WiFi_Pwd");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting... ");
    delay(200);
  }

  Serial.println();
  Serial.println();

  Serial.println("Node MCU is succesfully Connected to WiFi");

  Serial.println(WiFi.localIP());
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
