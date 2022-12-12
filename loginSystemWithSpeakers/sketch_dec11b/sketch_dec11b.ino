//Libraries

  //movement
#include <Servo.h>

  //for RFID 
#include <SPI.h>      
#include <MFRC522.h>

  //for Speaker
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Global Variables

  //movement
Servo leftFoot;
Servo rightFoot;

  //login system
String currentUserID= "";
String GOOD_USER = "43 60 A2 19"; //change based on who the desired user is
String BAD_USER = "53 BD E5 12";

int loggedIn = 0; //neutral 0 friend +1 enem -1, kept this and the current user id in case we want to expand to arrays

  //for RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

  //for Speaker
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

DFRobotDFPlayerMini player;  

  //pause between actions to prevent mixed signals
int pause = 500;

void setup() {
  setupRFID();
  setupLED();
  setupServo();
  //setupSpeaker();
}

void loop() {
  String cardScanned = lookForCards();

  if (cardScanned != "") {
    Serial.println("Card scanned.");

    if(currentUserID==""){
      Serial.println("User not logged in yet.");
      currentUserID=cardScanned; //attempt login
      if(loggedIn == 0){
        Serial.println("Logging in...");
        login();
      }
    }else if(currentUserID==cardScanned){
      logout(); //clears
    }else{
      Serial.println("You cannot switch users until you have logged out.");
    }
  }

  delay(pause);

  if(loggedIn==-1){
    unfriendlyMode();
  }
  else if(loggedIn==1){
    friendlyMode();
  }
  else{
    neutralMode();
  }
} 

void setupRFID(){
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void setupLED(){  //could put into array fill
  //left eye r,g,b
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  //right eye r,g,b
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
}

void setupServo(){
  //left foot
  leftFoot.attach(6);
  //right foot
  rightFoot.attach(5);
}

void setupSpeaker(){
  const int LDR = A0; //cannot be a0-a5, or 5 upwards for pin, if 2 and 3 is already used theres no more ports T_T
  int input_val = 0;
  int x = 0;
  int y = 0;

  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

String lookForCards(){
  //Checks if a card is physically present and is a valid RFID tag
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return "";
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return "";
  }

  String temp="";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     temp.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     temp.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  temp.toUpperCase();
  return temp;
}

void login(){
  if (currentUserID.substring(1) == GOOD_USER){ //change here the UID of the card/cards that you want to give access
    loggedIn = 1;
    printLogin(currentUserID.substring(1));
  }
  else if(currentUserID.substring(1) == BAD_USER){
    loggedIn = -1;
    printLogin(currentUserID.substring(1));
  }
}

void friendlyMode(){
  colourEyes(0,255,0);
  moveFeet(90,1);
  //speakerActive(); //should play the goodnight and goodmorning audio
}

void unfriendlyMode(){
  colourEyes(255,0,0);
  moveFeet(45,1);
}

void neutralMode(){
  colourEyes(200,0,200);
  moveFeet(0,0);
}

void logout(){
  Serial.println("You have logged out.");
  loggedIn = 0;
  currentUserID = "";
}

void printLogin(String id){
  Serial.println("You are logged in as "+id+" .");
}
void colourEyes(int r, int g, int b){
  //cathode ver.
  r = 255-r;
  g = 255-g;
  b = 255-b;

  //left eye
  analogWrite(A0,r);
  analogWrite(A1,g);
  analogWrite(A2,b);

  //right eye
  analogWrite(A3,r);
  analogWrite(A4,g);
  analogWrite(A5,b);
}

void moveFeet(int angle, int speed){
  if(angle==0 && speed==0){
    delay(delayTime);
    return;
  }

  int pos = 0;
  int delayTime = 25;

  for(pos=0; pos<=angle; pos+=speed){
    leftFoot.write(pos);
    rightFoot.write(pos);
    delay(delayTime);
  }

  for(pos=angle;pos>=0;pos-=speed){
    leftFoot.write(pos);
    rightFoot.write(pos);
    delay(delayTime);
  }
}

//int arrayLength(int arr[]){
//  int arrayLength = sizeof(arr)/sizeof(arr[0]);
//  return arrayLength;
//}
