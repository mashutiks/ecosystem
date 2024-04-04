#include "life.h"
#include "capybara.h"
#include "cayman.h"
#include "defines.h"
//#include "geometry.h"
#include "actionc.h"
#include <random>
#include <chrono>
#include <type_traits>

#define _USE_MATH_DEFINES

#include <math.h>
/*
void animal::set_rotation() {
    double angle_rad = atan2(move_y, move_x);
    int degrees = round(angle_rad * 180 / M_PI);
    int nearest_multiple = round(degrees / 45) * 45;
    angle = nearest_multiple * M_PI / 180;
}
*/
