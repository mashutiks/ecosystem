#pragma once
#include <string>
#include "capybara.h"
//#include "deleting.h"
#include "defines.h"
#include <chrono>
#include <random>

class orange {
public:
//private:
    float x, y;
    float move_x, move_y;
    long long additional_life;
    int type;
    int path_count;
    int age;
    bool is_alive;
    bool destination_right;
    float angle_destination;
    float angle;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

public:

    orange(int cur_x = -1, int cur_y = -1)
        : x(-1), y(-1), type(1), path_count(0), age(0), is_alive(true), destination_right(false), angle_destination(0), angle(0) {
        if (cur_x == -1 && cur_y == -1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            life_start = std::chrono::steady_clock::now();
            std::uniform_int_distribution<> life(-20000, 20000);
            additional_life = life(gen);
            std::uniform_int_distribution<> dis_x(100, 1720);
            x = dis_x(gen);
            std::uniform_int_distribution<> dis_y(100, 780);
            y = dis_y(gen);
        }
    }


    ~orange() {}

    void move();

    void set_rotation();
    //void add_orange(std::vector<orange>& oranges);
};

void move_oranges(std::vector<orange>& oranges);
