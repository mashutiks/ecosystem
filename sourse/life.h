#pragma once
#include "actionc.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <iostream>

class life {
public:
    float x, y;
    float move_x, move_y;
    float angle;
    float angle_destination;
    bool destination_right;
    bool is_alive;
    int path_count;

    bool hunt;
    bool found_close_prey;
    COORD eye_cord;
    COORD inner_eye;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> life_start;
    //float hungry_level;

public:
    life(float move_x = 0, float move_y = 0, float angle = 0, float angle_destination = 0, bool is_alive = true, int path_count = 0, bool destination_right = false)  {}
    ~life() {}
    
    //void set_rotation();
};
