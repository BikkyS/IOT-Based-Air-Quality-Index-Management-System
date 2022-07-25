void setup() {
 // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
Serial.begin(9600);}
void loop() {
 // put your main code here, to run repeatedly:
delay(100);
digitalWrite(5,HIGH);
digitalWrite(6,LOW);
digitalWrite(8,HIGH);
Serial.println("sensor 1 read");
delay(1000);
digitalWrite(8,LOW);
delay(100);
digitalWrite(6,HIGH);
digitalWrite(5,LOW);
digitalWrite(9,HIGH);
Serial.println("sensor 2 read");
delay(1000);
digitalWrite(9,LOW);
}
