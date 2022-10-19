#pragma once
#include "ryanlib/TaskWrapper.hpp"
#include "ryanlib/StateMachine.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/device/button/abstractButton.hpp"

enum class CatapultState{
    MOVING, LOAD_POSITION, IDLE
};

enum class ControlState {
    MANUAL, AUTOMATIC
};

template class ryan::StateMachine<CatapultState>;

class Catapult : public ryan::TaskWrapper, public ryan::StateMachine<CatapultState>{
    public:
    Catapult(const std::shared_ptr<okapi::AbstractMotor>& imotor, 
             const std::shared_ptr<okapi::AbstractButton>& ibutton);
    
    // Catapult();

    void disable(bool disabled);

    /**
     * @brief Set manual speed [-1, 1]
     * 
     * @param percentSpeed [-1, 1]
     */
    void jog(double percentSpeed);

    void fire();

    CatapultState getState();

    /**
     * @brief Set catapult speed [-1, 1]
     * 
     */
    void setSpeed(double speed);

    void loop() override;

    protected:
    std::shared_ptr<okapi::AbstractMotor> motor;
    std::shared_ptr<okapi::AbstractButton> button;

    private:
    bool isDisabled;
    double jogSpeed{0.0};
    bool fired{false};
    ControlState state;
    CatapultState cataState;
    double cataSpeed;
};