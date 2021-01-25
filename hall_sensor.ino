int val = 0;
void setup() {
  Serial.begin(9600);
  pinMode (2, OUTPUT);  // inBuilt LED output
}

void loop() {
  val = hallRead();     //get value from hallsensor
  if (val <=0 || val>=50) digitalWrite (2, HIGH); //Led to indicate presence of magnet poles
  else digitalWrite (2, LOW);
  Serial.print("Hall sensor measurement = ");  // print the results to the serial monitor
  Serial.println(val);//to graph 
   delay(500);
}
