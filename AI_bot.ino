#include <ESP8266WiFi.h>

// Defines Client
WiFiClient client; 

// Defines Server ; 5005 Port Number 
WiFiServer server(5005); 

// Motor Driver Pins
int ppwmr = 5; // D1
int ppwml = 4; // D2
int pdr = 0;   // D3
int pdl = 2;   // D4


// Motor Driver Parameters
int pwmr;
int pwml;
int dr;
int dl;
int i = 0;

// Mapped PWM 
int mpwmr;
int mpwml;

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 134);

// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

// Set your Subnet
IPAddress subnet(255, 255, 255, 0);

// Set your Primary DNS
IPAddress primaryDNS(8, 8, 8, 8);   //optional

// Set your Secondary DNS
IPAddress secondaryDNS(8, 8, 4, 4); //optional


void setup()
{
  
  Serial.begin(115200);

  // Configuring Pins for Motor Driver
  pinMode(ppwmr, OUTPUT);
  pinMode(ppwml, OUTPUT);   
  pinMode(pdr, OUTPUT);
  pinMode(pdl, OUTPUT);
  
  // Configures static IP Address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) 
  {
    Serial.println("STA Failed to configure");
  }
  

  WiFi.begin("mrm@M2", "");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting... ");
    delay(200);
  }

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
      String request = client.readStringUntil('e');
      request.trim();
      
      if (request[0] == 'm')
      {
        pwmr = (request[1]-'0')*100 + (request[2]-'0')*10 + (request[3]-'0');
        mpwmr = map(pwmr, 0, 255, 0, 1024);
        analogWrite(ppwmr, mpwmr);

        dr = request[4]-'0';
        if(dr == 1)
        {
          digitalWrite(pdr, HIGH);
        }
        else
        {
          digitalWrite(pdr, LOW);
        }
        

        pwml = (request[5]-'0')*100 + (request[6]-'0')*10 + (request[7]-'0');
        mpwml = map(pwml, 0, 255, 0, 1024);
        analogWrite(ppwml, mpwml);

        dl = request[8]-'0';
        if(dl == 1)
        {
          digitalWrite(pdl, HIGH);
        }
        else
        {
          digitalWrite(pdl, LOW);
        }
        
 
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
      {
        break;
      }
  
    }
  
  }
}


   
