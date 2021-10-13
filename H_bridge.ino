int m1a = 8;
int m1r = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(m1a,OUTPUT);
  pinMode(m1r,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(m1a,HIGH);
  digitalWrite(m1r,LOW);
  delay(1000);
  digitalWrite(m1a,LOW);
  digitalWrite(m1r,HIGH);
  delay(1000);
  digitalWrite(m1a,LOW);
  digitalWrite(m1r,LOW);
  delay(1000);
}
