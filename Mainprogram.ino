int pinBuzzer = 6; // pin del buzzer
int Nota = 900; // nota che suono
int notalow= 800;
unsigned long timeSample; // qui memorizzo l'istante in cui uno alza il culo dalla sedia
unsigned long timeDiff; 
unsigned long beepDuration = 1000; // durata del beep [ms]
boolean sysStart = false; // finche' non mi siedo la prima volta, il sistema non parte
int led = 9;
int fsrPin = A2;// the FSR and 10K pulldown are connected to a2
int battpin = A3;
int fsrReading; 
int IRpin = A0;
int IRpin2 = A1;
int distanza;
int distanza2;

void setup() {
  
Serial.begin(9600);
pinMode(pinBuzzer, OUTPUT);
pinMode(led, OUTPUT);
pinMode(IRpin, INPUT);
analogWrite(led,150);
delay(100);
analogWrite(led,0);
delay(100);
analogWrite(led,150);
delay(100);
analogWrite(led,0);

}

void loop() {
  
fsrReading = analogRead(fsrPin); 
distanza = analogRead(IRpin);
distanza2 = analogRead(IRpin2);
int voltage = analogRead(battpin);
  
if (fsrReading < 150) {
  // culo alzato 
  // se e' ho appena acceso la baracca, sysStart e' false e non entro qui dentro
  // se mi sono gia' seduto, sysStart e' true e non conta piu'. quindi se ho il 
  // culo alzato AND questo istante - quello in cui l'ho alzato e' meno di beepDuration
  // allora suono la nota, altrimenti non entro dentro e saluti
  timeDiff = millis()-timeSample;
  Serial.print(timeDiff);Serial.println(" differenza timing"); // for debug only
  if (timeDiff<beepDuration && sysStart) {
     if (distanza>200 || distanza2>200) {
    tone(pinBuzzer,Nota);
    digitalWrite(led, HIGH);
  }}
  else {
    noTone(6);
     digitalWrite(led, LOW);
  }
 }
 else {
   // culo seduto
   sysStart = true; // la prima volta che mi siedo entro qui e lo metto true
   noTone(6);
   analogWrite(led, LOW);


   timeSample = millis(); //ad ogni loop in cui sono seduto memorizzo l'ora
 }
 
while ((voltage/44.73) < 5.9) {
   
analogWrite(pinBuzzer, 10);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
delay(500);          // wait for a delayms ms
analogWrite(pinBuzzer, 0);       // 0 turns it off
delay(2000); 
 }
   
  
  //Serial.print(fsrReading);Serial.println(" pressione");
  //Serial.println(distanza);
  Serial.print(voltage/44.73);Serial.println("Volt");
  Serial.println(distanza);
  Serial.println(distanza);



 delay(150);
}
