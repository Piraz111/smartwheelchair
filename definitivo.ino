int pinBuzzer = A0; // pin del buzzer
int Nota = 900; // nota che suono
unsigned long timeSample; // qui memorizzo l'istante in cui uno alza il culo dalla sedia
unsigned long timeDiff; 
unsigned long beepDuration = 1000; // durata del beep [ms]
boolean sysStart = false; // finche' non mi siedo la prima volta, il sistema non parte
int led = A1;
int interr = 7;
int statoint = 0;
int triggerPort = 8;
int echoPort = 9;

void setup() {
  
Serial.begin(9600);
pinMode(pinBuzzer, OUTPUT);
pinMode(led, OUTPUT);
pinMode(interr, INPUT);
pinMode( triggerPort, OUTPUT );
pinMode( echoPort, INPUT );
}

void loop() {
  
int sensorValue = analogRead(A5);
statoint=digitalRead(interr);
digitalWrite( triggerPort, LOW );
digitalWrite( triggerPort, HIGH );
delayMicroseconds( 10 );
digitalWrite( triggerPort, LOW );
long duration = pulseIn( echoPort, HIGH );
long r = 0.034 * duration / 2;

if (sensorValue < 300) {
  // culo alzato 
  // se e' ho appena acceso la baracca, sysStart e' false e non entro qui dentro
  // se mi sono gia' seduto, sysStart e' true e non conta piu'. quindi se ho il 
  // culo alzato AND questo istante - quello in cui l'ho alzato e' meno di beepDuration
  // allora suono la nota, altrimenti non entro dentro e saluti
  timeDiff = millis()-timeSample;
  Serial.print(timeDiff);Serial.println(" differenza timing"); // for debug only
  if (timeDiff<beepDuration && sysStart) {
     if (statoint == HIGH || r>5 ) {
    tone(pinBuzzer,Nota);
    digitalWrite(led, HIGH);
  }}
  else {
    noTone(A0);
     digitalWrite(led, LOW);
     digitalWrite(statoint, LOW) ;
  }
 }
 else {
   // culo seduto
   sysStart = true; // la prima volta che mi siedo entro qui e lo metto true
   noTone(A0);
   digitalWrite(led, LOW);
   digitalWrite(statoint, LOW) ;

   timeSample = millis(); //ad ogni loop in cui sono seduto memorizzo l'ora
 }
  
  Serial.print(sensorValue);Serial.println(" pressione");
  Serial.print(r);Serial.println(" cm");


 delay(150);
}
