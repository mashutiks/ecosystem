#include "orange.h"
#define _USE_MATH_DEFINES

#include <math.h>

void orange::set_rotation() {
    double angle_rad = atan2(move_y, move_x); // возвращает угол, образованный между положительным направлением оси X и точкой с координатами (y, x)
    int degrees = round(angle_rad * 180 / M_PI);
    int nearest_multiple = round(degrees / 45) * 45;
    angle = nearest_multiple * M_PI / 180;
}

/* старый set_rotation
void orange::set_rotation() {
    destination_right = abs(std::asin(move_y / PLANKTON_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
}
*/


void orange::move() {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > ORANGE_LIFE_TIME + additional_life) {
        is_alive = false;
        x = -100;
        y = -100;
    }
    else {
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(2000, 10000);

        if (current_time > dis(gen)) { // проверяется, прошло ли достаточно времени для изменения направления движения.
            start = std::chrono::steady_clock::now();

            std::uniform_int_distribution<> dis(-ORANGE_SPEED, ORANGE_SPEED);
            move_x = dis(gen);
            move_y = sqrt(ORANGE_SPEED * ORANGE_SPEED - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if (sign == 2) {
                move_y = -move_y;
            }

            destination_right = abs(std::asin(move_y / ORANGE_SPEED) * 180 / M_PI) < 90 && move_x >= 0;

        }
        else {
            x += move_x;
            y += move_y;
            if (x < 50 && move_x < 0) {
                move_x = -move_x;
            }
            if (x > WIDTH - 200 && move_x > 0) {
                move_x = -move_x;
            }
            if (y < 50 && move_y < 0) {
                move_y = -move_y;
            }
            if (y > HEIGHT - 200 && move_y > 0) {
                move_y = -move_y;
            }
        }
    }
    set_rotation();
}

void move_oranges(std::vector<orange>& oranges) {
    for (auto& o : oranges) {
        if (o.is_alive) {
            o.move();
        }
    }
}

