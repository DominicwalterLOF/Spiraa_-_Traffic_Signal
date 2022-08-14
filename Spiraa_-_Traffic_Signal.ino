/* ==================================================================

         Project by Team Spiraa for Solve With Arduino
  ________  _______   __      _______        __            __
  /"       )|   __ "\ |" \    /"      \      /""\          /""\
  (:   \___/ (. |__) :)||  |  |:        |    /    \        /    \
  \___  \   |:  ____/ |:  |  |_____/   )   /' /\  \      /' /\  \
   __/  \\  (|  /     |.  |   //      /   //  __'  \    //  __'  \
  /" \   :)/|__/ \    /\  |\ |:  __   \  /   /  \\  \  /   /  \\  \
  (_______/(_______)  (__\_|_)|__|  \___)(___/    \___)(___/    \___)

  PS: I always felt the present traffic timing device is
  not fair in its control. Same time for all sides
  with different vehicle density. Not fair!!!

  I would like to design a device that controls
  lights depending up on the density of vehicle.
  Can you help me please?

  ====================================================================
*/



#include <Servo.h>


Servo servoN, servoE, servoW, servoS;

int calibrationConst[4][90];

int inches = 0;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  servoN.attach(8);
  servoE.attach(9);
  servoW.attach(10);
  servoS.attach(11);
}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
}


int takeDes(int arr[])
{
  int flag = -1;
  //logic goes here
  return flag;
}

int takeDest(int arr[]) {
  int maxTraffic = 0; // Assuming maxTraffic in the index 0.
  for (int i = 0; i < 4; i++)
    if (arr[i] > arr[maxTraffic]) // Comparing each element in the array with the maxTraffic.
      maxTraffic = i; // When an element is greater than the maxTraffic we are replacing the maxTraffic to index of that element.

  return maxTraffic; // After the end of the loop the maxTraffic is returned.
}


void calibrate() {

}


void turn(int angle) {

}
