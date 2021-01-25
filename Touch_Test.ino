// ESP32 Touch Test
int touch_value = 100; 
void setup()
{
Serial.begin(115200);  //begin serial communication with BR 115200
pinMode (4, INPUT);    //gpio pin 4 input
pinMode(2, OUTPUT);   //2 output inbuilt led
digitalWrite (2, LOW);
}

void loop()
{
touch_value = touchRead(4);     //read from values from gpio4
Serial.print("Touch value is = ");
Serial.println( touch_value);   //print touch values

if (touch_value < 50)       //glow LED when touched
{digitalWrite (2, HIGH);}
else
{digitalWrite (2, LOW);}
delay(1000);
}
