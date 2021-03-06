#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    pot,            sensorPotentiometer)
#pragma config(Sensor, in3,    select,         sensorPotentiometer)
#pragma config(Sensor, in4,    leftLeftLine,   sensorLineFollower)
#pragma config(Sensor, in5,    leftLine,       sensorLineFollower)
#pragma config(Sensor, in6,    midLine,        sensorLineFollower)
#pragma config(Sensor, in7,    rightRightLine, sensorLineFollower)
#pragma config(Sensor, in8,    rightLine,      sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, bum,            sensorTouch)
#pragma config(Sensor, dgtl12, po,             sensorDigitalOut)
#pragma config(Sensor, I2C_1,  armEnc,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftdrive,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftdrive1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lift,          tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port4,           lift1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           claw,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           claw1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           lift2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           lift3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightdrive1,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightdrive,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

const int CLAW_OPEN_DOWN = 2500;
const int CLAW_OPEN = 2800;
const int CLAW_CLOSED = 4000;
int timesSwept = 0;
const int ARM_DOWN = 0;

int sectionSweepTime = 1500;

int auton = 0;
task autonSelectDisplay{
	while(true){
		clearLCDLine(1);
		displayLCDPos(1,5);
		if(SensorValue[select] < 500){
			auton = 0;
		}
		else if(SensorValue[select] < 1500){
			auton = 1;
		}
		else if(SensorValue[select] < 2500){
			auton = 3;
		}
		else{
			auton = 4;
		}
		displayNextLCDNumber(auton);
	}
}

void pre_auton()
{
	startTask(autonSelectDisplay);
	bStopTasksBetweenModes = true;
}

int getArmValue(){
	return -(SensorValue[armEnc]);
}

bool goingLeft = false;

/* Required Includes */
#include "GetFunctions.c"
#include "MotorFunctions.c"
#include "PID.c"
#include "ArmClawControl.c"
#include "GenericDriveFunctions.c"
#include "LineTracking.c"
#include "GenericAutonMethods.c"
#include "ProgrammingSkills.c"
#include "Autonomous.c"



task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................
	// Remove this function call once you have "real" code.
	//	redLeftBabyRageStart();
	//programmingSkills();

		if(SensorValue[select] < 500){
			redLeftBabyRageStart();
		}
		else if(SensorValue[select] < 1500){
			redLeftStart();
		}
		else if(SensorValue[select] < 2500){
			redRightStart();
		}
		else{
			redRightBabyRageStart();
		}
}
int armDirection = 1;


task usercontrol()
{
	// User control code here, inside the loop
	clawPosition = SensorValue[pot];
	clearLCDLine(0);
	while(vexRT[Btn6D] != 1){
		clearLCDLine(1);
		displayLCDPos(1,5);
		displayNextLCDNumber(SensorValue[gyro]);
		wait1Msec(10);
		}

	while (true)
	{
		clearLCDLine(1);
		displayLCDPos(1,5);
		displayNextLCDNumber(SensorValue[gyro]);
		setDrive(vexRT[Ch3], vexRT[Ch2]);

		if(vexRT[Btn6D] == 1){
			setClaw(-127);
			}else if(vexRT[Btn6U] == 1){
			setClaw(127);
		}
		else{
			setClaw(-15);
		}

		if(vexRT[Btn5U] == 1){
			setLift(127);
			armDirection = 1;
			}else if(vexRT[Btn5D] == 1){
			setLift(-127);
			armDirection = -1;
		}
		else{
			setLift(15 * armDirection);
		}

		if(vexRT[Btn8L] == 1){
			for(int j = 0; j < 10; j++){
				motor[j] = 0;
			}
			//programmingSkills();
		}


		if(vexRT[Btn7U] == 1){
			for(int j = 0; j < 10; j++){
				motor[j] = 0;
			}
			//AutonomousInit();
			redLeftBabyRageStart();
			//programmingSkills();
			//redRightStart();
			//redLeft();
			//redLeft();
		}

		if(vexRT[Btn8D] == 1){
			SensorValue[po] = 1;
		}

		if(vexRT[Btn8U] == 1){
			SensorValue[po] = 0;
		}
	}
}
