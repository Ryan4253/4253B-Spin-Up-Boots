#include "main.h"
#include "GUI/gif-pros/gifclass.hpp"

void initialize() {
    // General Initialization
	pros::lcd::initialize();
    imu.calibrate();
    catapult->startTask();
    catapult->setSpeed(0.8);

    // Auton Selector
    const char* autons[3]  = {"a", "b", "c"};
    Selector::init(180, 1, autons);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    leftChassis.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightChassis.setBrakeMode(AbstractMotor::brakeMode::brake);

    switch(Selector::auton) {
        case 0:
            doNothing();
            break;

        case 1:
            redAutonA();
            break;
        
        case 2: 
            redAutonB();
            break;

        case 3: 
            redAutonC();
            break;
        
        case -1: 
            blueAutonA();
            break;
        
        case -2:
            blueAutonB();
            break;
        
        case -3: 
            blueAutonC();
            break;
    }
}

void createBlankBackground(){
    lv_obj_t *background;
    lv_style_t backgroundStyle;
    lv_style_copy(&backgroundStyle, &lv_style_plain);
    backgroundStyle.body.main_color = LV_COLOR_BLACK;
    backgroundStyle.body.grad_color = LV_COLOR_BLACK;
    backgroundStyle.body.radius = 0;
    backgroundStyle.text.color = LV_COLOR_WHITE;
    background = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(background, 0);
    lv_obj_set_style(background, &backgroundStyle);
    lv_obj_set_size(background, LVGL_SCREEN_WIDTH, LVGL_SCREEN_HEIGHT);
    lv_obj_align(background, NULL, LV_ALIGN_CENTER, 0, 0);
}

void opcontrol() {
    // Gif background
    // createBlankBackground();
    // Gif gif("/usd/gif/crab-rave.gif", lv_scr_act()); da thing is erroring out 

    // profiler->setTarget(8_ft, true);
    // while(true) pros::delay(1000);

	leftChassis.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightChassis.setBrakeMode(AbstractMotor::brakeMode::coast);

    auto model = std::static_pointer_cast<SkidSteerModel>(chassis->getModel());

    while(true) {
        model->curvature(
            master.getAnalog(ControllerAnalog::leftY), 
            master.getAnalog(ControllerAnalog::rightX), 
            DEADBAND
        );
        // model->tank(
        //     master.getAnalog(ControllerAnalog::leftY), 
        //     master.getAnalog(ControllerAnalog::rightY), 
        //     DEADBAND
        // );

        if(master.getDigital(ControllerDigital::L1)) {
            catapult->fire();
        }

        if(catapult->getState() == CatapultState::LOAD_POSITION) {
            intake.moveVoltage(12000 * (master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2)));
        } else {
            intake.moveVoltage(0);
        }

        pros::delay(10);
    }
}
