/*
 * 
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  pinMode(A0,OUTPUT); //solution works for one multi led, switch to shift registry for more than one
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
}
void loop() 
{
  lightsOn(0,0,0); //sets hardcoded pins to change colour, switch to shift registry
  // Look for new cards, this part is the neutral code
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "43 60 A2 19") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lightsOn(100,125,255); //add all the authorised code here
    delay(3000);
    //add an until, so that you can log out with the authorised card and go to netural mode
  }
 
 else   {
    Serial.println(" Access denied");
    lightsOn(255,100,100); //add all the unauthrised code here
    delay(3000);
  }
} 

void lightsOn(int r,int g,int b){ //we have an anode not cathode, so port to 5v over gnd
  analogWrite(A0,255-r);
  analogWrite(A1,255-g);
  analogWrite(A2,255-b);
} //change this function to work with the shift registry
