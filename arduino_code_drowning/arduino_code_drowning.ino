#include <ESP8266WiFi.h>

int ir=0;
const char* ssid     = "wifi001";
const char* password = "12345678";

const char* host = "iotprojects20232.000webhostapp.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup(void)
{
 
  //ESP.wdtDisable();
  // Your code here
  //ESP.wdtEnable(WDTO_8S); 

  Serial.begin(115200);
  pinMode(D8,OUTPUT);
  digitalWrite(D8,LOW);

    
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(void)
{ 
  delay(1000);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "GET http://iotprojects20232.000webhostapp.com/drowning/update2.php"; // Getting info from my online database through my online website
  url+=" HTTP/1.1\r\nHost: iotprojects20232.000webhostapp.com\r\n\r\n";
  url += "\r\n\r\n";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(url);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    char a=client.read();
    Serial.print(a);
    
    if(a=='*')
    {
      a=client.read();
    Serial.print(a);
    if(a=='a')
    {
      a=client.read();
      Serial.print(a);
    if(a=='1')
    {
      digitalWrite(D8,LOW);
      }
      if(a=='0')
    {
      digitalWrite(D8,HIGH);
      }  
      
    }  
      }
    //String line = client.readStringUntil('\r');
    //Serial.print(line);
   
    Serial.print(a);
  }
     
    } 
