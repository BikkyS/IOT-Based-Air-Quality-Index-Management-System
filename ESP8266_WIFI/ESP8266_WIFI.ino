void setup() {
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(D5, DHT22);
char status;
WiFiClient client;

String apiKey = "PD23C8O7XWZ73YGZ";
const char *ssid =  "iot";
const char *pass =  "88888888";
const char* server = "api.thingspeak.com";
int x,y;
int oz,co2;
void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, pass);
    lcd.begin();                     
  lcd.backlight();
pinMode(D6,INPUT);
pinMode(D7,INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0,0);
    lcd.print("connecting to");
    lcd.setCursor(0,1);
    lcd.print(ssid);
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("WiFi connected");
  Serial.println("");
  Serial.println("WiFi connected");
  delay(3000);
  lcd.clear();
}

void loop() {


  //DHT11 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0,0);
    lcd.print("check DHT wire");
    return;
  }
x=digitalRead(D6);
y=digitalRead(D7);

if((x==1)&&(y==0))
{
  oz=analogRead(A0);
  delay(2000);
}
if((x==0)&&(y==1))
{
   co2=analogRead(A0);
   co2=co2+400;
   delay(2000);
}

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(oz);
    postStr += "&field4=";
    postStr += String(co2);
    postStr += "\r\n\r\n\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("co2: ");
    Serial.print(co2);
    Serial.println("ppm");
    Serial.print("ozone:");
    Serial.print(oz);
    Serial.println("ppm");
lcd.clear();
lcd.setCursor(0,0);
    lcd.print("temp:");
    lcd.print(t);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("hum:");
    lcd.print(h);
    lcd.print(" %");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
     lcd.print("co2:");
    lcd.print(co2);
    lcd.print(" ppm");
    lcd.setCursor(0,1);
    lcd.print("oz:");
    lcd.print(oz);
    lcd.print(" ppm");
    delay(1000);
  }
  //client.stop();

}
