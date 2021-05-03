
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <driver/adc.h>


#include "index.h"  //Web page header file

WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "Energized";
const char* password = "Batteries!";

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

int a = 0;
float batt1 = 0;
float batt2 = 0;
float batt3 = 0;
float batt4 = 0;
float ratioFactor = 6.1468;


void handleADC() {
 float sumVal = 0;
 String adcValue;

  // Battery Monitoring Section
  // Powers relays to connect batteries to voltage divider for analog input.
  // This sequence starts with the top battery and works to bottom (with respect to PCB).
  
  Serial.println("Battery 1 connected.");
  delay(3000);

  // BATTERY 1 SENSING
  for(unsigned int i=0;i<10;i++){
    sumVal = sumVal + analogRead(34);      //Read voltage divider
    delay(5);                              //Keep ADC stable
  }

  sumVal = (float)sumVal/10.0;            // Find average of 10 values
  sumVal = (float)(sumVal*3.3)/4095;      // Convert to voltage at ADC.
  batt1 = sumVal * ratioFactor;
  
  digitalWrite(25, HIGH);
  Serial.println("Battery 2 connected.");
  delay(3000);

  sumVal = 0; // Reset the sum value before next battery.
  
  // BATTERY 2 SENSING
  for(unsigned int i=0;i<10;i++){
    sumVal = sumVal + analogRead(34);      //Read voltage divider
    delay(5);                              //Keep ADC stable
  }

  sumVal = (float)sumVal/10.0;            // Find average of 10 values
  sumVal = (float)(sumVal*3.3)/4095;      // Convert to voltage at ADC.
  batt2 = sumVal * ratioFactor;
  
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  Serial.println("Battery 3 connected.");
  delay(3000);

  sumVal = 0; // Reset the sum value before next battery.

  //BATTERY 3 SENSING
  for(unsigned int i=0;i<10;i++){
    sumVal = sumVal + analogRead(34);      //Read voltage divider
    delay(5);                              //Keep ADC stable
  }

  sumVal = (float)sumVal/10.0;            // Find average of 10 values
  sumVal = (float)(sumVal*3.3)/4095;      // Convert to voltage at ADC.
  batt3 = sumVal * ratioFactor;
  printf("Batt 3 = %.2f ", batt3);
  
  digitalWrite(32, HIGH);
  Serial.println("Battery 4 connected.");
  delay(3000);

  sumVal = 0; // Reset the sum value before next battery.

  //BATTERY 4 SENSING
  for(unsigned int i=0;i<10;i++){
    sumVal = sumVal + analogRead(34);      //Read voltage divider
    delay(5);                              //Keep ADC stable
  }

  sumVal = (float)sumVal/10.0;            // Find average of 10 values
  sumVal = (float)(sumVal*3.3)/4095;      // Convert to voltage at ADC.
  batt4 = sumVal * ratioFactor;
  
  digitalWrite(32, LOW);
  digitalWrite(26, LOW);

 adcValue = "Batt 1=" + String(batt1) + "V Batt 2=" + String(batt2) + "V Batt 3=" + String(batt3) + "V Batt 4=" + String(batt4) + "V";
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

//===============================================================
// Setup
//===============================================================

void setup(void){
  Serial.begin(115200);

  // Relay pins
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(32, OUTPUT);

  // ADC pin is 34
  // ADC attenuation setup below:
  //adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);

  
  Serial.println();
  Serial.println("Booting Sketch...");


//ESP32 As access point
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);


//ESP32 connects to your wifi -----------------------------------
  //WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  //Serial.println("Connecting to ");
  Serial.print(ssid);
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //IP address of ESP32
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", handleADC);//To get update of ADC Value only
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
  delay(1);
}
