#include "Subsystems/Catapult.hpp"
#include "Subsystems/Globals.hpp"

Catapult::Catapult(const std::shared_ptr<okapi::AbstractMotor>& imotor, 
                   const std::shared_ptr<okapi::AbstractButton>& ibutton)
{
    motor = std::move(imotor);
    button = std::move(ibutton);
    isDisabled = false;
    state = ControlState::MANUAL;
    cataState = CatapultState::IDLE;
}

void Catapult::disable(bool disabled) {
    isDisabled = disabled;
}

void Catapult::jog(double percentSpeed) {
    state = ControlState::MANUAL;
    jogSpeed = percentSpeed;
}

void Catapult::fire() {
    state = ControlState::AUTOMATIC;
    fired = true;
}

CatapultState Catapult::getState() {
    return cataState;
}

void Catapult::loop() {
    while(true) {
        if(!isDisabled) {
            switch(state) {
                case ControlState::MANUAL:
                    cataState = CatapultState::MOVING;
                    motor->moveVoltage(jogSpeed * 12000);
                    break;

                case ControlState::AUTOMATIC:
                    if(!button->isPressed()) {
                        fired = false;
                    }
                    if((button->isPressed() && fired) || (!button->isPressed())) {
                        motor->moveVoltage(8000);
                        cataState = CatapultState::MOVING;
                    } else {
                        motor->moveVoltage(0);
                        cataState = CatapultState::LOAD_POSITION;
                    }
                    break;
            }
        }
        pros::delay(10);
    }
}