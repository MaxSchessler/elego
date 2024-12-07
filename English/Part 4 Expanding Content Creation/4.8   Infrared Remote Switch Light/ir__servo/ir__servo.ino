//www.elegoo.com
//2023.05.08

#include "IRremote.h"
#include <Servo.h>
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating
   objects like the following "myservo" to refer to the members in ".".*/

Servo myservo;
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
//vairable uses to store the last decodedRawData
uint32_t last_decodedRawData = 0;

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
// describing Remote IR codes
{
  // Check if it is a repeat IR code
  if (irrecv.decodedIRData.flags)
  {
    //set the current decodedRawData to the last decodedRawData
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
  }
  switch (irrecv.decodedIRData.decodedRawData)
  {
    //the "VOL-" button
    case 0xEA15FF00:  myservo.write(30);// move servos to center position -> 30°
      delay(1000);
      break;

    //the "VOL+" button
    case 0xB946FF00:   myservo.write(150);// move servos to center position -> 150°
      delay(1000);
      break;
    default:
      Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat

} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver
  myservo.attach(11);//connect pin 11 with the control line(the middle line of Servo)

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}/* --(end main loop )-- */
