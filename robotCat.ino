// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>

//lichtsensoren
int leftLightSensor = A0;
int rightLightSensor = A1;

int leftLightSensorValue = 0;
int rightLightSensorValue = 0;

// DC motor on M2
AF_DCMotor rechtsMotor(3);
AF_DCMotor linksMotor(4);

// DC hobby servo
Servo servo1;

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    Serial.println("Motor party!");

    // turn on servo
    servo1.attach(9);

    // turn on motor #2
    rechtsMotor.setSpeed(200);
    linksMotor.setSpeed(200);
    rechtsMotor.run(RELEASE);
    linksMotor.run(RELEASE);

    //  pinMode(leftLightSensor, INPUT);
    //  pinMode(rightLightSensor, INPUT);

    Serial.println("start de motor !");
}

int i;

// Test the DC motor, stepper and servo ALL AT ONCE!
void loop()
{
    //  rechtsMotor.run(FORWARD);
    //  motor2.run(FORWARD);
    //  rechtsMotor.setSpeed(200);
    //  motor2.setSpeed(200);

    delay(350);

    rightLightSensorValue = analogRead(rightLightSensorValue);
    Serial.print("right: ");
    Serial.println(rightLightSensorValue);

    leftLightSensorValue = analogRead(leftLightSensorValue);
    Serial.print("left: ");
    Serial.println(leftLightSensorValue);

    //rij het licht na
    // 1030 drempelwaarde
    if (leftLightSensorValue < 300 || rightLightSensorValue < 300)
    {
        rechtsMotor.run(RELEASE);
        linksMotor.run(RELEASE);
    }
    else
    {
        // verschil in licht
        if (leftLightSensorValue > rightLightSensorValue)
        {
            //  naar links
            rechtsMotor.run(FORWARD);
            linksMotor.run(FORWARD);
            rechtsMotor.setSpeed(255);
            linksMotor.setSpeed(200);
            Serial.println("Links is groter dan rechts, rechter motor rijd harder");
        }
        else if (leftLightSensorValue < rightLightSensorValue)
        {
            rechtsMotor.run(FORWARD);
            linksMotor.run(FORWARD);
            rechtsMotor.setSpeed(200);
            linksMotor.setSpeed(255);
            Serial.println("rechts is groter dan links, links motor rijd harder");
        }
        else
        {
            rechtsMotor.run(RELEASE);
            linksMotor.run(RELEASE);
            rechtsMotor.setSpeed(0);
            linksMotor.setSpeed(0);
            Serial.println("beide motoren rijden even hard");
        }
        delay(350);
    }
}