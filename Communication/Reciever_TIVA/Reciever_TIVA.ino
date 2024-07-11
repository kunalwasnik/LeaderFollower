#include <ESP8266WiFi.h>
#include <SPI.h>
char ssid[] = "Case";           // SSID of your home WiFi
char pass[] = "pass123@";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,150,153);       // the fix IP address of the server
WiFiClient client;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
 
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
     digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    
  }
   digitalWrite(LED_BUILTIN, LOW);
   
}

void loop() {
 
 client.connect(server, 80);   // Connection to the server

  //Serial.println(".");
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  //Serial.println("from server: " + answer);
  int value = answer.toInt();
  char c = value + '0';
  Serial.print(c);
  // Serial.print("Value : ");
  // Serial.println(value);
  // for (int i = 0; i < answer.length(); i++)
  // {
  //   Serial.write(answer[i]);   // Push each char 1 by 1 on each loop pass
  //   Serial.print("Sending");
  //   Serial.println(answer[i]);
  // }

  
   
  client.flush();

  delay(100);                  // client will trigger the communication after two seconds
}
