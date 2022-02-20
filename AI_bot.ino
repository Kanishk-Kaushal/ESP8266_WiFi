#include <ESP8266WiFi.h>

WiFiClient client; // defines Client
WiFiServer server(5005); // defines Server ; 5005 port number 

int pwmr;
int pwml;
int dr;
int dl;
int i = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin("mrm@M2", "mrm@2019");

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

}

void loop() 
{
  client = server.available();
   if(client == 1)
  {

  while(1)
  {
  // put your main code here, to run repeatedly:
  
  
 
    String request = client.readStringUntil('e');
   // Serial.println(request);
    request.trim();
    
    if (request[0] == 'm')
    {
      pwmr = (request[1]-'0')*100 + (request[2]-'0')*10 + (request[3]-'0');
      dr = request[4]-'0';
      pwml = (request[5]-'0')*100 + (request[6]-'0')*10 + (request[7]-'0');
      dl = request[8]-'0';
      Serial.println("PWMR");
      Serial.println(pwmr);
      Serial.println("PWML");
      Serial.println(pwml);
      Serial.println("DIRR");
      Serial.println(dr);
      Serial.println("DIRL");
      Serial.println(dl);

  

        
    }
   else if(request[9] == 'e')
    {break;}

   
   
  
 }

}
}


   
