#pragma once
#include "cayman.h"
#include "orange.h"
#include "defines.h"
#include "actionc.h"
#include <chrono>
#include <random>
#include <vector>
#include <string>

class cayman;

class orange;

class capybara {
public:
//private:
    orange* prey = nullptr;
    bool hunt;
    bool found_close_prey;
    COORD eye_cord;
    COORD inner_eye;
    int path_count;
    float hungry_level;
    int age;
    float x, y;
    long long capybara_additional_life;
    int type;
    float width;
    float height;
    float cayman_x;
    float cayman_y;
    float distance_cayman;
    float closest_cayman_x;
    float closest_cayman_y;
    float move_x;
    float move_y;
    float angle;
    float angle_destination;
    bool destination_right;
    bool is_alive;
    bool cayman_found;
    bool is_first;
    bool is_hunted;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> start_run;
    std::chrono::time_point<std::chrono::steady_clock> life_start;
    bool found_close_cayman;

public:
    capybara(int cur_x = -1, int cur_y = -1)
        : hunt(false), found_close_prey(false), path_count(0), hungry_level(40), age(0), type(1), cayman_x(0), cayman_y(0), distance_cayman(1e9), move_x(0), move_y(0), angle(0), angle_destination(0), is_alive(true), destination_right(true), cayman_found(false), is_first(true), is_hunted(false), found_close_cayman(false) {
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

    bool find_cayman(std::vector<cayman>& caymans);
    void move(std::vector<cayman>& caymans, std::vector<orange>& oranges);
    void set_rotation();
    void run_set_rotation();
    bool find_orange(std::vector<orange>& oranges);
    //void add_capybara(std::vector<capybara>& capybaras);
};

void move_capybaras(std::vector<capybara>& capybaras, std::vector<cayman>& caymans, std::vector<orange>& oranges);
