/**
 * SDA -> 21
 * SCL -> 22
 * 
 * 
*/

#include <Arduino.h>
#include <Wire.h> //https://www.arduino.cc/en/reference/wire
#include <Adafruit_PWMServoDriver.h>
#include <PS4Controller.h>

#define SERVO_FREQ 50
#define SERVOMIN 205 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 410 // This is the 'maximum' pulse length count (out of 4096)
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Initialize System"));
	pca.begin();
	pca.setOscillatorFrequency(27000000);
	pca.setPWMFreq(SERVO_FREQ);
	PS4.begin((char*)"01:01:01:01:01:01");

}

void dualshock_loop()
{
	static int servonum = 0;
	if (PS4.isConnected()) {
		Serial.printf("L Sticky X : %d\n", PS4.LStickX());
		Serial.printf("L Sticky Y : %d\n", PS4.LStickY());
		pca.setPWM(servonum, 0, map(PS4.LStickX(), -128, 128, SERVOMIN, SERVOMAX));
		pca.setPWM(servonum + 1, 0, map(PS4.LStickY(), -128, 128, SERVOMIN, SERVOMAX));
		if (PS4.Right())
		{
			while(PS4.Right())
			{
				delay(5);
			}
			if (servonum >= 10)
			{
				servonum = 0;
			}
			servonum += 2;
		}
		else if (PS4.Left())
		{
			while(PS4.Left())
				{
				delay(5);

			}
			if (servonum == 0)
			{
				servonum = 12;
			}
			servonum -= 2;
		}
	}
}

void loop()
{
	// int servonum = 0;
	// for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++)
	// {
	// 	pca.setPWM(servonum, 0, pulselen);
	// 	delay(5);
	// }
	// delay(500);
	// for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--)
	// {
	// 	pca.setPWM(servonum, 0, pulselen);
	// 	delay(5);
	// }
	dualshock_loop();
	// put your main code here, to run repeatedly:
}