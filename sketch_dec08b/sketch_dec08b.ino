int analogPorts[] = {3,5,6,9,10,11};

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i< (sizeof(analogPorts)/sizeof(analogPorts[0])); i++){
    pinMode(analogPorts[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i< (sizeof(analogPorts)/sizeof(analogPorts[0])); i++){
    analogWrite(analogPorts[i],random(255));    //test value
    delay(1000);
  }
}
