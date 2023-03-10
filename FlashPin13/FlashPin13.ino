void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  
  Serial.begin(9600); // debugging
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("ON ");
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  Serial.print("OFF ");
  delay(500);
  Serial.println();
}
