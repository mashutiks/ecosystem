#pragma once
#include "life.h"
#include "defines.h"
#include "actionc.h"
#include "capybara.h"
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

class capybara;

class cayman : public life {
public:
//private:
    std::chrono::time_point<std::chrono::steady_clock> life_start;
    std::chrono::time_point<std::chrono::steady_clock> start;
    COORD eye_cord;
    COORD inner_eye;
    int path_count;
    bool hunt;
    bool found_close_prey;
    float hungry_level;
    float x, y;
    float direction;
    int speed;
    float move_x;
    float move_y;
    float capybara_x;
    float capybara_y;
    float angle;
    float angle_destination;
    bool is_alive;
    bool destination_right;
    capybara* prey = nullptr;

public:
    cayman(int cur_x = -1, int cur_y = -1) 
        : found_close_prey(false), hungry_level(31), x(0), y(0), direction(0), speed(CAYMAN_SPEED), capybara_x(0), capybara_y(0),
        life(move_x, move_y, angle, angle_destination, is_alive, path_count, destination_right) {

        if (cur_x == -1 && cur_y == -1) {
            life_start = std::chrono::steady_clock::now();
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<> dis(100, WIDTH - 200);
            x = dis(gen);

            std::uniform_int_distribution<> dis_y(100, HEIGHT - 200);
            y = dis_y(gen);
        }
    }
    ~cayman() {}
    void move(std::vector<capybara>& capybaras);
    bool find_capybara(std::vector<capybara>& capybaras);
    void set_rotation();
    //void add_cayman(std::vector<cayman>& caymans);
};

void move_caymans(std::vector<cayman>& caymans, std::vector<capybara>& capybaras);
