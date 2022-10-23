#pragma once
#include "okapi/api/units/QAngle.hpp"

using namespace okapi;

/**
 * @brief Turns the robot to the desired global angle (using closed-loop control)
 *
 * @param targetAngle - the target odometry global angle to turn to
 */
void turnToAngle(QAngle targetAngle);