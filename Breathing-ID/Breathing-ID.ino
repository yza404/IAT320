int LED_9 = 9;
int LED_10 = 10;
int LED_6 = 6;//define 3 "breathing LED"


void setup() {
pinMode(LED_9,OUTPUT);
pinMode(LED_10,OUTPUT);
pinMode(LED_6,OUTPUT);// defined as output modes

} 

void loop() {

LED(9);
LED(10);
LED(6);// call the fuction
}

void LED(int led){
for(int i=0; i<=255; i++){ analogWrite(led,i);
  delay(8);
  }
  for(int i=255; i>=0; i--){ analogWrite(led,i);
  delay(5);}
  delay(100);
}
