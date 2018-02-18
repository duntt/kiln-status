#include <Button.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "***";                           // WIFI network name
const char* password = "***";                       // WIFI network password
uint8_t connection_state = 0;                   // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again

#pragma endregion Globals

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
  static uint16_t attempt = 0;
  Serial.print("Connecting to ");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    Serial.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    Serial.println(ssid);
  }

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)
  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available or SSID and Password\r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("Got IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void Awaits()
{
  int32_t ts = millis();
  while (!connection_state)
  {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
  }
}

int bisqueButton = 4; // customise buttons. 
int earthenwareButton = 5;// customise buttons. 
int stonewareButton = 14;// customise buttons. 
int statusLed = 2; // customise leds. 
int powerLed = 10;// customise leds. 
int run;
int count;
int count1;
String recipient;
String displayTime;
int timezone = 10; // customise timezone. 
int dst = 0;

void setup()
{
  recipient = "***";
  pinMode(bisqueButton, INPUT_PULLUP);
  pinMode(earthenwareButton, INPUT_PULLUP);
  pinMode(stonewareButton, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);
  pinMode(powerLed, OUTPUT);
  digitalWrite(statusLed, LOW);
  digitalWrite(powerLed, LOW);
  run = 0; //starts stopped
  Ready();
  // not sure how this is getting the time before connecting to wifi
  getDateTime();

}

void FlashLed(int led, int speed) {
    for (int i = 0; i <= 10; i++) {
      digitalWrite(led, HIGH);
      delay(speed);
      digitalWrite(led, LOW);
      delay(speed);
    }  
}
void SendEmail(int button, String type) {
    Serial.begin(115200);
    FlashLed(statusLed, 50); // flash fast to show button has been pushed
    connection_state = WiFiConnect();
    getDateTime();
    if (!connection_state) // if not connected to WIFI
      Awaits();          // constantly trying to connect

    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "A " + type + " firing has finished at " + displayTime;
    if (gsender->Subject(subject)->Send(recipient, "A " + type + " firing has finished."))
    {
      Serial.println("Message about " + type + " sent to "  + recipient) ;
      FlashLed(statusLed, 200); // flash slower to show success
    }
    else
    {
      digitalWrite(statusLed, HIGH); // solid light to show error
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }
    run = 0;
}
void CheckButton(int button, String type) {
    if (digitalRead(button) == LOW)  {
      if (run == 0) {
        run = 255;
      } else {
        run = 0;
      }
    }
  
    if (run > 0) {
      SendEmail(button, type);      
    }
}
void Ready() {
   Serial.begin(115200);
   Serial.println("System is online");
}
void getDateTime() {  
    configTime(timezone * 3600, dst, "pool.ntp.org", "time.nist.gov");
    Serial.println("\nWaiting for time");
    while (!time(nullptr)) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println("");
    time_t now = time(nullptr);    
    Serial.println(ctime(&now));
    displayTime = ctime(&now);
}

void loop()
{

  CheckButton(bisqueButton, "bisque");
  CheckButton(earthenwareButton, "earthenware");
  CheckButton(stonewareButton, "stoneware");
 
}

