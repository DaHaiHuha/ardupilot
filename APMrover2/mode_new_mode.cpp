//
// Created by OrangeBC on 2019-03-24.
//

#include "mode.h"
#include "Rover.h"

bool ModeNew_mode::_enter()
    {
    // initialise waypoint speed
    set_desired_speed_to_default();

    // set desired location to reasonable stopping point
    calc_stopping_location(_destination);
    set_desired_location(_destination);

    return true;
}