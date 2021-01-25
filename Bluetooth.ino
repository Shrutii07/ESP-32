#include <BluetoothSerial.h>
BluetoothSerial BT;
char r;     //variable to read

void setup() 
{
BT.begin("Shruti's ESP");   //device name to be displayed
pinMode( 2, OUTPUT);    //led as output
}

void loop()
{
  r = BT.read();    //read command sent via bluetooth
  if (r == '1')         //r=1 LED ON
  {
    digitalWrite( 2, HIGH);
  }
  if ( r == '0')        //r-0 LED OFF
  {
    digitalWrite( 2, LOW);
  }
  if(r == 'B')          //r=B LED BLINK
  {
    while(r != 'E')     //r=E END BLINKING
    {digitalWrite( 2,HIGH);
    delay(100);
    digitalWrite( 2,LOW);
    delay(100);
    r = BT.read();
    }
  }
}
