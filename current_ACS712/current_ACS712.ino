int ENA = D2;
unsigned long start;

void setup() {
  pinMode(ENA, OUTPUT);
  analogWriteFreq(40000);
  //analogWriteResolution(10);
  Serial.begin(115200);  //Start Serial Monitor to display current read value on Serial monitor
}
uint8_t ind = 180;
void loop() {
  start = millis();
  while ((millis() - start) < (2000+(ind*4))) {
    unsigned int x = 0;
    float AcsValue = 0.0, Samples = 0.0, AvgAcs = 0.0, AcsValueF = 0.0, volt_5v = 0, volt_3v = 0;
    for (int x = 0; x < 150; x++) {  //Get 150 samples
      AcsValue = analogRead(A0);     //Read current sensor values
      Samples = Samples + AcsValue;  //Add samples together
      delay(3);                      // let ADC settle before next sample 3ms
    }
    //Serial.print("digital: ");
    AvgAcs = (Samples / 150.0);
    //Serial.print(AvgAcs);
    //Serial.println("");
    volt_3v = (AvgAcs * (3.3 / 1023.0) - 0.16);
    //Serial.print("Volt 3v: ");
    //Serial.print(volt_3v);
    //Serial.println("");
    volt_5v = ((volt_3v) + 1);
    //Serial.print("Volt 5v: ");
    //Serial.print(volt_5v);
    //Serial.println("");
    AcsValueF = ((2.50 - volt_5v) / 0.100)+0.1;
    if (AcsValueF < 0.4)
      AcsValueF = 0;
    Serial.print("Current: ");
    Serial.print(AcsValueF);  //Print the read current on Serial monitor
    Serial.println("A");
    delay(50);
  }
  Serial.print("pwm: ");
  if (ind < 180)
    ind = 180;
  ind += 5;
  Serial.println(ind);
  analogWrite(ENA, ind);
  //digitalWrite(ENA, HIGH);
}