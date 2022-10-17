#include "Globals.hpp"
#include "Subsystems/Globals.hpp"
using namespace okapi;

// CONTROLLERS
Controller master(ControllerId::master);

// MOTORS
Motor leftFront(10, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftMid(9, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBack(8, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightFront(7, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightMid(6, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(5, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

MotorGroup leftChassis({leftFront, leftMid, leftBack});
MotorGroup rightChassis({rightFront, rightMid, rightBack});

// Motor catapultMotor(11, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
Motor intake(19, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

// PNEUMATICS
Pneumatics intakeAngler('A');
Pneumatics expansion('G');

// SENSORS 
IMU imu(20);
// ADIButton catapultButton('G', false);
// ADIEncoder leftTracker('A', 'B', true);
// ADIEncoder rightTracker('E', 'F', false);
// ADIEncoder midTracker('C', 'D', false);

// MOTION PROFILE CONSTANTS
ProfileConstraint moveLimit({3_ftps, 5_ftps2, 5_ftps2, 25_ftps3}); //! todo!

// SUBSYSTEM CONTROLLERS
std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
    .withMotors(leftChassis, rightChassis)
    // !todo!
    .withDimensions({AbstractMotor::gearset::blue, 5.0/7.0}, {{3.25_in, 1.294_ft}, imev5BlueTPR})
    .build();

std::shared_ptr<AsyncMotionProfiler> profiler = AsyncMotionProfilerBuilder()
    .withOutput(chassis)
    .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
    .build();

std::shared_ptr<IterativePosPIDController> turnPID = 
    std::make_shared<IterativePosPIDController>(0.037, 0.0, 0.00065, 0, TimeUtilFactory::withSettledUtilParams(2, 2, 100_ms));

std::shared_ptr<Catapult> catapult = 
    std::make_shared<Catapult>(std::make_shared<Motor>(-20), 
                               std::make_shared<ADIButton>('H', false));