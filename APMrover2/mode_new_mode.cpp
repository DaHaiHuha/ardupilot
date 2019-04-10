//
// Created by OrangeBC on 2019-03-24.
//

#include "mode.h"
#include "Rover.h"

// import from the guided mode
bool ModeNew_mode::_enter() {
    // initialise waypoint speed
    set_desired_speed_to_default();

    // set desired location to reasonable stopping point
    calc_stopping_location(_destination);
    set_desired_location(_destination);

    return true;
}

// import from the manual mode
void ModeManual::_exit() {
    // clear lateral when exiting manual mode
    g2.motors.set_lateral(0);
}

// import from the manual mode
void ModeManual::update() {

    /*

    // convert pilot stick input into desired steering and throttle
    float desired_steering, desired_throttle;
    get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle);

    // convert pilot throttle input to desired speed (up to twice the cruise speed)
    // the target_speed is the calculated speed that throttle should turn
    float target_speed = desired_throttle * 0.01f * calc_speed_max(g.speed_cruise, g.throttle_cruise * 0.01f);

    // convert pilot steering input to desired turn rate in radians/sec
    // but, this is a turn rate, which aims to change the current stage and revise
    float target_turn_rate = (desired_steering / 4500.0f) * radians(g2.acro_turn_rate);


    */

    float desired_steering, desired_throttle, desired_lateral;
    get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle);
    get_pilot_desired_lateral(desired_lateral);

    // if vehicle is balance bot, calculate actual throttle required for balancing
    if (rover.is_balancebot()) {
        rover.balancebot_pitch_control(desired_throttle);
    }

    // set sailboat mainsail from throttle position
    g2.motors.set_mainsail(desired_throttle);

    // copy RC scaled inputs to outputs
    g2.motors.set_throttle(desired_throttle);
    g2.motors.set_steering(desired_steering, false);
    g2.motors.set_lateral(desired_lateral);
}