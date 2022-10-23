#pragma once
#include "Subsystems/Catapult.hpp"
#include "okapi/api.hpp"
#include "ryanlib/Pneumatics.hpp"
#include "ryanlib/api.hpp"


using namespace okapi;

#define LVGL_SCREEN_WIDTH 480
#define LVGL_SCREEN_HEIGHT 240

// CONSTANTS
const double DEADBAND = 0.0500;

// CONTROLLER(s)
extern Controller master;

// MOTORS
extern MotorGroup leftChassis;
extern MotorGroup rightChassis;
// extern Motor catapultMotor;
extern Motor intake;

// PNEUMAICS
extern Pneumatics intakeAngler;
extern Pneumatics expansion;

// SENSORS
extern IMU imu;
// extern ADIButton catapultButton;

// SUBSYSTEM CONTROLLERS
extern std::shared_ptr<ChassisController> chassis;
extern std::shared_ptr<AsyncMotionProfiler> profiler;
extern std::shared_ptr<IterativePosPIDController> turnPID;
extern std::shared_ptr<Catapult> catapult;
