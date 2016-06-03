#pragma config(Sensor, dgtl1,  pnuematic,      sensorDigitalOut)
#pragma config(Sensor, dgtl3,  trigger,        sensorTouch)
#pragma config(Sensor, dgtl10, downswitch,     sensorTouch)
#pragma config(Sensor, dgtl11, upswitch,       sensorTouch)
#pragma config(Motor,  port7,           motor2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           motor1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(DatalogSeries, 0, "", Motors, MotorPower, port1, 50)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("Motors")
#pragma DebuggerWindows("VexLCD")
#pragma DebuggerWindows("taskStatus")
#pragma DebuggerWindows("debugStream")
#pragma DebuggerWindows("systemParameters")

#define shooter motor[port8]=motor[port1]  // Keep the two motors in sync


void shooter_down (int speed)
{
	shooter = speed;
	while(!SensorValue[downswitch])
	{
	}
	shooter = 0;
}

void shooter_down (int speed,int msec)
{
	shooter = speed;
	wait1Msec(msec);
	shooter = 0;
}

void shooter_up (int speed)
{
	shooter = speed  * -1;
	while(!SensorValue[upswitch])
	{
	}
	shooter = 0;
}

void shooter_up (int speed, int msec)
{
	shooter = speed*-1;
	wait1Msec(msec);
	shooter = 0;
}

void flip_pnu()
{
	SensorValue[pnuematic] = !SensorValue[pnuematic];
	writeDebugStreamLine("pnuematic state = %d",SensorValue[pnuematic]);
}


void set_pnu(int state)
{
	SensorValue[pnuematic] = state;
}
string s;



task main()
{
	set_pnu(1);
	shooter_up(64);
	wait1Msec(500);
	flip_pnu();
	shooter_down(64);
	wait1Msec(100);
	while(SensorValue[trigger] == 0)
	{
	}
	shooter = 2;
	flip_pnu();
}
