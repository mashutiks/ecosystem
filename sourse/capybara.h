#pragma once
#include "cayman.h"
#include "orange.h"
#include "defines.h"
#include "actionc.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>

struct cayman;

struct orange;

struct capybara {

    explicit capybara(int cur_x = -1, int cur_y = -1) {
        if (cur_x == -1 && cur_y == -1) {
            life_start = std::chrono::steady_clock::now();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(100, 1720);
            std::uniform_int_distribution<> life(-20000, 20000);
            capybara_additional_life = life(gen);
            x = dis(gen);

            std::uniform_int_distribution<> dis_y(100, 780);
            y = dis_y(gen);

            width = CAPYBARA_WIDTH;
            height = CAPYBARA_HEIGHT;
        }

    }

    orange* prey = nullptr;

    bool hunt = false;
    bool found_close_prey = false;

    COORD eye_cord;
    COORD inner_eye;

    int path_count = 0;

    float hungry_level = 40;
    int age = 0;
    float x, y;

    long long capybara_additional_life;
    int type = 1;

    float width;
    float height;

    float cayman_x = 0;
    float cayman_y = 0;
    float distance_cayman = 1e9;

    float closest_cayman_x;
    float closest_cayman_y;
    float move_x = 0;
    float move_y = 0;

    float angle = 0;
    float angle_destination = 0;

    bool destination_right = true;

    bool is_alive = true;
    bool cayman_found = false;
    bool is_first = true;
    bool is_hunted = false;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> start_run;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

    bool found_close_cayman = false;
    bool find_cayman(std::vector<cayman>& caymans);

    void move(std::vector<cayman>& caymans, std::vector<orange>& oranges);

    void set_rotation();

    void run_set_rotation();

    bool find_orange(std::vector<orange>& oranges);

};

void move_capybaras(std::vector<capybara>& capybaras, std::vector<cayman>& caymans, std::vector<orange>& oranges);
