#define BLYNK_TEMPLATE_ID "" //get this from blynk.cloud (for your device)
#define BLYNK_DEVICE_NAME "" //get this from blynk.cloud (for your device)
#define BLYNK_AUTH_TOKEN "" //get this from blynk.cloud (for your device)

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8 //If you're only using a single 32x8 display then please set this to 4.

#define CLK_PIN   D5 //green
#define DATA_PIN  D7 //orange
#define CS_PIN    D8 //yellow

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES); 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
char auth[] = BLYNK_AUTH_TOKEN;

String pinValue1;
String pinValue2;
String pinValue3;
int delayValue;
int delayValue_ms;

BLYNK_WRITE(V4) {
  delayValue = param.asInt();
  delayValue_ms = (delayValue * 1000);
}
BLYNK_WRITE(V5) {
  pinValue1 = param.asString();
}
BLYNK_WRITE(V6) {
  pinValue2 = param.asString();
}
BLYNK_WRITE(V7) {
  pinValue3 = param.asString();
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  P.begin();

}

void loop()
{
  Blynk.run();
  
  P.displayText("", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT); //initialise all text output to be in the middle
  P.displayAnimate();

  P.print(pinValue1); //Output the string value found in the 1st Blynk IoT app terminal to the matrix display 
  Blynk.virtualWrite(V8, pinValue1); //Display the 1st string value from the matrix display to the V8 label (on IoT app)
  delay(delayValue_ms); //pause between switching from value 1 to value 2
  
  P.print(pinValue2); //Output the string value found in the 2nd Blynk IoT app terminal to the matrix display 
  Blynk.virtualWrite(V8, pinValue2); //Display the 2nd string value from the matrix display to the V8 label (on IoT app)
  delay(delayValue_ms); //pause between switching from value 2 to value 3
  
  P.print(pinValue3); //Output the string value found in the 3rd Blynk IoT app terminal to the matrix display
  Blynk.virtualWrite(V8, pinValue3); //Display the 3rd string value from the matrix display to the V8 label (on IoT app)
  delay(delayValue_ms); //pause between switching from value 3 and back to value 1
}