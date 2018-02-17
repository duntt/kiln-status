#include <Button.h>
#include <ESP8266WiFi.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "*ssid*";                           // WIFI network name
const char* password = "*password*";                       // WIFI network password
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

int buttonPin;
int buttonPin1;
int ledPin1;
int ledPin2;
int run;
int count;
int count1;

void setup()
{
  buttonPin = 4;
  buttonPin1 = 5;
  ledPin1 = 2;
  ledPin2 = 10;
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  run = 0; //starts stopped

}

void loop()
{
  //code you always run here; you can leave this section blank if you want the entire program to stop and start, or add code here if you want it to always run
  //check button press here and if it is pressed then toggle run variable between 0 and 255; REQUIRED!
  if (digitalRead(buttonPin) == LOW) //funcitons based off of button pulling input pin LOW
  {
    if (run == 0)
    {
      run = 255;
    }
    else
    {
      run = 0;
    }
  }

  if (run > 0)

    // New 1 End

    // Original Start - Run when pressed hopefully
  {
    Serial.begin(115200);
    connection_state = WiFiConnect();
    if (!connection_state) // if not connected to WIFI
      Awaits();          // constantly trying to connect

    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Button 1 Pressed (D2 or GPIO4)";
    if (gsender->Subject(subject)->Send("* enter recipient email *", "Setup test"))
    {
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      Serial.println("Message send.");
    }
    else
    {
      digitalWrite(ledPin1, HIGH);
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }
    run = 0;
  }

  // *********

  if (digitalRead(buttonPin1) == LOW) //funcitons based off of button pulling input pin LOW
  {
    if (run == 0)
    {
      run = 255;
    }
    else
    {
      run = 0;
    }
  }
  if (run > 0)

  {
    Serial.begin(115200);
    connection_state = WiFiConnect();
    if (!connection_state) // if not connected to WIFI
      Awaits();          // constantly trying to connect

    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Button 1 Pressed (D1 or GPIO5)";
    if (gsender->Subject(subject)->Send("* enter recipient email *", "Setup test"))
    {
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(200);
      digitalWrite(ledPin1, LOW);
      delay(200);
      Serial.println("Message send.");
    }
    else
    {
      digitalWrite(ledPin1, HIGH);
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }
    run = 0; //starts stopped
  }
  // *********

}

// Original End

