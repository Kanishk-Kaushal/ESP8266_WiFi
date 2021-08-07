#include <ESP8266WiFi.h>

WiFiClient client; // defines Client
WiFiServer server(80); // defines Server ; 80 

#define led1 D5
#define led2 D6

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

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
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
    if (request == "GET /led1_on HTTP/1.1")
    {
      digitalWrite(led1,HIGH);
    }
    if (request == "GET /led1_off HTTP/1.1")
    {
      digitalWrite(led1,LOW);
    }
    if (request == "GET /led2_on HTTP/1.1")
    {
      digitalWrite(led2,HIGH);
    }
    if (request == "GET /led2_off HTTP/1.1")
    {
      digitalWrite(led2,LOW);
    }
  }
  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<h1> Welcome to the other side </h1>");
  client.println("<h3> LED Controller </h3>");
  client.println("<br>");
  client.println("<a href = \"/led1_on\"\"><button>LED 1 ON</button></a>");
  client.println("<a href = \"/led1_off\"\"><button>LED 1 OFF</button></a><br />");
  client.println("<a href = \"/led2_on\"\"><button>LED 2 ON</button></a>");
  client.println("<a href = \"/led2_off\"\"><button>LED 2 OFF</button></a><br />");
  client.println("</html>");
  
}
   
