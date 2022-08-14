/* ==================================================================

         Project by Team Spiraa for Solve With Arduino
  ________  _______   __      _______        __            __
  /"       )|   __ "\ |" \    /"      \      /""\          /""\
  (:   \___/ (. |__) :)||  |  |:        |    /    \        /    \
  \___  \   |:  ____/ |:  |  |_____/   )   /' /\  \      /' /\  \
   __/  \\  (|  /     |.  |   //      /   //  __'  \    //  __'  \
  /" \   :)/|__/ \    /\  |\ |:  __   \  /   /  \\  \  /   /  \\  \
  (_______/(_______) (__\_|_ )|__|  \___)(___/    \___)(___/    \___)

  PS: I always felt the present traffic timing device is
  not fair in its control. Same time for all sides
  with different vehicle density. Not fair!!!

  I would like to design a device that controls
  lights depending up on the density of vehicle.
  Can you help me please?

  Answer : YES, we are more than happy to help you.

  ====================================================================
*/

#include <Servo.h>

Servo servoN, servoE, servoW, servoS;

int calibrationConst[4][90];

int news[4];

int trafficSignalTimer = 1000;

int newsBitMap[4];

int inches = 0;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)

{
  // Clear the trigger

  pinMode(triggerPin, OUTPUT);

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


void loop()
{


  /*
  // measure the ping time in cm

  cm = 0.01723 * readUltrasonicDistance(7, 7);

  // convert to inches by dividing by 2.54

  inches = (cm / 2.54);

  Serial.print(inches);

  Serial.print("in, ");

  Serial.print(cm);

  Serial.println("cm");

  // Wait for 100 millisecond(s)

  delay(100);

  */


}

int takeDes(int arr[])
{
   // Assuming maxTraffic in the index 0.

  int maxTraffic = 0;

  // Comparing each element in the array with the maxTraffic.

  for (int i = 0; i < 4; i++)

    if (arr[i] > arr[maxTraffic])

      // When an element is greater than the maxTraffic we are replacing the maxTraffic to index of that element.

      maxTraffic = i;

  // After the end of the loop the maxTraffic is returned.

  return maxTraffic;
}

void sweep()
{

  // When the system is turned on for the first time the roads will be calibrated.

  calibrate();

  while (1)
  {
    // The roads are scanned continuously for the traffic and decisions are taken accordingly.
    scan();
    takeDes(news);
    delay(trafficSignalTimer);
  }
  
}

void scan()
{

  for (int i = 0; i < 4; i++)
  {
    news[i] = 0; // Traffic density of all the roads are initialized with 0.
  }

  for (int i = 0; i < 90; i++)
  {

    turn(i); // All the servos are aligned to a particular angle.

    readRoads(); // The roads are scanned by the ultrasonic sensor for the particular angle and BitMap is created.

    for (int j = 0; i < 4; i++)
    {
      news[j] += newsBitMap[j]; // The values of the BitMap are added to the news array
    }
    
  }
}

void calibrate()
{

  /*
  Calibrate function
  Can be used for calibrating the traffic signal
  We read the values of empty reads first and store it in the tow dimensional array calibrationConst


  */

  for (int i = 0; i < 90; i++)
  {

    // Align all the servos to a particular angle

    turn(i);

    readRoads();

    for (int j = 0; j < 4; j++)
    {
      calibrationConst[j][i] = news[j]; // Assigning the calibrations constants with distance sensed by the four sensors when the road is empty.
    }
  }
}

void readRoads()
{
  
  for (int i = 4; i < 8; i++)
  {
    newsBitMap[i - 4] = readUltrasonicDistance(i, i); // The distance is calculated and stored in the BitMap.
  }
}

void turn(int angle)
{
  // turn() method is used to turn all servos at a particular angle simultaneously.
  servoN.write(angle);

  servoE.write(angle);

  servoW.write(angle);

  servoS.write(angle);

  delay(30);
}

void setup()
{

  Serial.begin(9600);

  servoN.attach(8);

  servoE.attach(9);

  servoW.attach(10);

  servoS.attach(11);

  sweep();

}

void signal(int d)
{
  switch (d)
  {
  case 0:
    digitalWrite(2, HIGH);
    break;
  case 1:
    digitalWrite(3, HIGH);
    break;
  case 2:
    digitalWrite(12, HIGH);
    break;
  case 3:
    digitalWrite(13, HIGH);
    break;
  default:
    break;
  }
}
