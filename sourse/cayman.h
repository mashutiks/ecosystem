#pragma once
#include "defines.h"
#include "actionc.h"
#include "capybara.h"
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

struct capybara;

struct cayman {

    explicit cayman(int cur_x = -1, int cur_y = -1) {
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

    std::chrono::time_point<std::chrono::steady_clock> life_start;
    std::chrono::time_point<std::chrono::steady_clock> start;

    COORD eye_cord;
    COORD inner_eye;

    int path_count;
    bool hunt = false;

    bool found_close_prey = false;



    float hungry_level = 31;
    float x = 0, y = 0;
    float direction = 0;
    int speed = CAYMAN_SPEED;

    float move_x = 0;
    float move_y = 0;

    float fish_x = 0;
    float fish_y = 0;

    float angle = 0;
    float angle_destination = 0;

    bool is_alive = true;

    bool destination_right = true;

    capybara* prey = nullptr;

    void move(std::vector<capybara>& capybaras);

    bool find_capybara(std::vector<capybara>& capybaras);

    void set_rotation();
};


void move_caymans(std::vector<cayman>& caymans, std::vector<capybara>& capybaras);
