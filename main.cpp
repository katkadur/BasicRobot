#include "WPILib.h"


class Robot : public IterativeRobot{
private:

    CANTalon* lift;
    CANTalon* frontLeft;
    CANTalon* rearLeft;
    CANTalon* frontRight;
    CANTalon* rearRight;
    RobotDrive* drive;
    Joystick* joy;
    DigitalInput* limitSwitch;
    Ultrasonic* ultra;
    AnalogGyro* gyro;

    void robotInit(){
        lift = new CANTalon(1);
        drive = new RobotDrive(frontLeft,rearLeft,frontRight,rearRight);
        joy = new Joystick(0);
        limitSwitch = new DigitalInput(0);
        ultra = new Ultrasonic(1,2);
        gyro = new AnalogGyro(3);
    }

    void teleopInit(){


    }

    void teleopPeriodic(){
        double leftSide = joy->GetRawAxis(1);//left joystick, y axis
        double rightSide = joy->GetRawAxis(5);//right joystick, y axis
        drive->TankDrive(leftSide, rightSide);

        if (limitSwitch->Get() == true){
            lift->Set(1);
        }

        ultra->SetAutomaticMode(true);
        int range = ultra->GetRangeInches();
        if (range == 20){
            lift->Set(-1);
        }

        float angle = gyro->GetAngle();
        if (angle == 10){
            drive->TankDrive(-0.5, -0.5); //will this work???
            //do I need to reset the gyro???
        }


    }
};

START_ROBOT_CLASS(Robot);

