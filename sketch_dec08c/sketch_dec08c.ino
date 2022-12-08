int pinNum = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinNum,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pinNum,100);
}
