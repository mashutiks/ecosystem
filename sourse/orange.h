#pragma once
#include <string>
#include "capybara.h"
//#include "deleting.h"
#include "defines.h"
#include <chrono>
#include <random>

struct orange {
    orange(int cur_x = -1, int cur_y = -1) {
        if (cur_x == -1 && cur_y == -1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            life_start = std::chrono::steady_clock::now();
            // Генерируем случайное значение для времени жизни апельсина
            std::uniform_int_distribution<> life(-20000, 20000);
            additional_life = life(gen);
            // Генерируем случайные x и y координаты
            std::uniform_int_distribution<> dis_x(100, 1720);
            x = dis_x(gen);

            std::uniform_int_distribution<> dis_y(100, 780);
            y = dis_y(gen);
        }
    }
    float x, y;
    float move_x, move_y;

    long long additional_life;
    int type = 1;

    int path_count;

    int age;

    bool is_alive = true;

    bool destination_right;
    float angle_destination;
    float angle;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> life_start;

    void move();

    void set_rotation();
};

void move_oranges(std::vector<orange>& oranges);
