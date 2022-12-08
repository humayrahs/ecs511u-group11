int pinR = 11; //change rgb analog pin for rg diffsed common cathode
int pinG = 10;
int pinB = 9;
//as we will have 2 pins for eyes, turn this into an array/object at some point

void setup() {
  // put your setup code here, to run once:
  pinMode(pinR,OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT); //same here, neaten code for 2 eyes
}

void loop() {
  // put your main code here, to run repeatedly:
  //init mode = 0(neut)
  //reference rfid system here so that mode can switch
  //rfidSys();
  switchMode(0);
}

void switchMode(int mode){
  //switch anger/neut/friend mode -1/0/+1
  if(mode==0){
    neutMode();
  }
  else if(mode==1){
    frenMode();
  }
  else if(mode==-1){
    enemMode();
  }
  
}

void neutMode(){
  //behaviours go here, if overlapping behaviours convert them to objects/methods of their own
  ledEyes(200,0,200); //int r g b for neut, for test made purple
}

void frenMode(){
  ledEyes(0,255,0); //green eyes
}

void enemMode(){
  ledEyes(255,0,0); //red eyes
}

void ledEyes(int r, int g, int b){ //int r,int g, int b depending on what led 
  //init led in setup, blink colour/patterns here
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b); //same here, could pass array once again
}

void rfidSys(){
  //rfid code (referenced) goes here
}
