#include "AccelStepper.h"
#include "math.h"

#define hiz 400
#define ivme 1000
#define aci 80

AccelStepper steppero(1, 7, 6);
AccelStepper stepperb(1, 9, 8);
AccelStepper stepperk(1, 11, 10);

int val1 = 0, val2 = 0;
int newval1;
int newval2;
int previous1 = 0, previous2 = 0, newprevious1 = 0, newprevious2 = 0;

int data[2];

void setup()
{
  
  Serial.begin(9600);

  stepperk.setMaxSpeed(hiz);
  stepperk.setAcceleration(ivme);

  steppero.setMaxSpeed(hiz);
  steppero.setAcceleration(ivme);

  stepperb.setMaxSpeed(hiz);
  stepperb.setAcceleration(ivme);

}
void loop()
{
  if (Serial.available() > 1)
  {
    for (int i = 0; i < 2; i++)
    {
      data[i] = Serial.read();
    }

    val1 = data[1];
    val2 = data[0];

    //Serial.print(newval1);
    //Serial.print(' ');
    //Serial.println(newval2);


    newval1 = map(val1, 0, 255, 0, aci);
    newval2 = map(val2, 0, 255, 0, aci);

    if ((val1 > previous1 + 13) || (val1 < previous1 - 13))
    {
      if (val1 > previous1)
      {
        for (int i = newprevious1; i < newval1 + 1; i++)
        {
          stepperk.runToNewPosition(i + newval2);
          steppero.runToNewPosition(i);
          stepperb.runToNewPosition(i);
        }
      }
      if (val1 < previous1)
      {
        for (int i = newprevious1; i > newval1 - 1; i--)
        {
          stepperk.runToNewPosition(i + newval2);
          steppero.runToNewPosition(i);
          stepperb.runToNewPosition(i);
        }
      }
      previous1 = val1;
      newprevious1 = map(previous1, 0, 255, 0, aci);
    }


    if ((val2 > previous2 + 13) || (val2 < previous2 - 13))
    {

      if (val2 > previous2)
      {
        for (int i = newprevious2; i < newval2 + 1; i++)
        {
          stepperk.runToNewPosition(i + newval1);
          steppero.runToNewPosition(newval1 - i / 3);
          stepperb.runToNewPosition(newval1 - i / 3);
        }
      }
      if (val2 < previous2)
      {
        for (int i = newprevious2; i > newval2 - 1; i--)
        {
          stepperk.runToNewPosition(i + newval1);
          steppero.runToNewPosition(newval1 - i / 3);
          stepperb.runToNewPosition(newval1 - i / 3);
        }
      }
      previous2 = val2;
      newprevious2 = map(previous2, 0, 255, 0, aci);
    }
  }
}
