#include <arduino.h>
#include "ControlMotor.h"



/**********************************A NE PAS MODIFIER ! *********************************/
void Init_Motor()
{
 pinMode(IN1A,OUTPUT);     
 pinMode(IN2A,OUTPUT);     
                           
 digitalWrite(IN1A,LOW);   
 digitalWrite(IN2A,LOW);   
}

void Control_Motor()
{
 static int i = 0;
 static unsigned char Speed = 0;
 static unsigned char pin = IN1A;
 static bool stop = false;

 if (!stop)
 {
 if (!(i%5))
  {
   if (i<60)
   {
    Speed+=20;
    analogWrite(pin,Speed);
   }
   else
   { 
    if (Speed != 0)
    Speed-=20;
    analogWrite(pin,Speed);
    }
  }
  if (i == 120)
  {
   digitalWrite(pin,LOW);
   if (pin == IN2A)
     stop = true;
   
   pin = IN2A;    
   i = 0;
  }
  else
  i++;
 }
}
/****************************************************************************************/
