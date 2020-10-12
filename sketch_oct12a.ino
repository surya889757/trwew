#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(3,4);//rx,tx 
SoftwareSerial sim800l(6,7); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
TinyGPS gps; // create gps object 
double pulse;
void setup()
{
Serial.begin(9600); // connect serial 
//Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor 
 sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the 
pinMode(11,INPUT);


Serial.print("metal detector");
}
void loop()
{

while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
  // display position 
   

  Serial.print("Position: "); 
  Serial.print("Latitude:"); 
  Serial.print(lat,6); 
  Serial.print(";"); 
  Serial.print("Longitude:"); 
  Serial.println(lon,6);  

  Serial.print(lat); 
  Serial.print(" "); 

 } 
} 
 
delay(1000); 
pulse = pulseIn(11,HIGH,5000);
if(pulse > 920)
{ Serial.print("metal detected be safe");
String latitude = String(lat,6); 
  String longitude = String(lon,6); 
Serial.println(latitude+";"+longitude);
    SendSMS();                          //And this function is called
}
}
void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+*********\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("SIM800l is working");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}
