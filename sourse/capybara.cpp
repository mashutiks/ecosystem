#include "capybara.h"
#include "cayman.h"
#include "defines.h"
#include "geometry.h"
#include "actionc.h"
#include <random>
#include <chrono>
#include <type_traits>

#define _USE_MATH_DEFINES

#include <math.h>

bool capybara::find_cayman(std::vector<cayman>& caymans) {
    bool is_cayman_found = false;
    eye_cord = getCapybaraEyeCoord({ x, y }, inner_eye, angle, width, height);
    float closest_cayman = 1e9;
    found_close_cayman = false;

    for (int i = 0; i < caymans.size(); i++) {
        COORD temp = getClosestFromPoint({ caymans[i].x, caymans[i].y }, CAYMAN_WIDTH, CAYMAN_HEIGHT, caymans[i].angle, eye_cord);
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        if (temp_distance < closest_cayman && temp_distance <= CAPYBARA_RUN_DISTANCE) {
            is_cayman_found = true;
            cayman_x = temp.x;
            cayman_y = temp.y;
        }
        else if (temp_distance < closest_cayman && temp_distance <= 200) {
            distance_cayman = temp_distance;
            closest_cayman_x = temp.x;
            closest_cayman_y = temp.y;
            found_close_cayman = true;
        }

    }

    return is_cayman_found;
}

void capybara::set_rotation() {
    double angle_rad = atan2(move_y, move_x);
    int degrees = round(angle_rad * 180 / M_PI);
    int nearest_multiple = round(degrees / 45) * 45;
    angle = nearest_multiple * M_PI / 180;
}

void capybara::run_set_rotation() {
    double angle_rad = atan2(move_y, move_x);
    int degrees = round(angle_rad * 180 / M_PI);
    int nearest_multiple = round(degrees / 45) * 45;
    angle = nearest_multiple * M_PI / 180;
}

void capybara::move(std::vector<cayman>& caymans, std::vector<orange>& oranges) {
    {
        COORD eye{};
        COORD inner = CAPYBARA_EYE;
        inner_eye = inner;
        eye_cord = eye;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > CAPYBARA_LIFE_TIME + capybara_additional_life || hungry_level <= 0) {
        is_alive = false;
        x = -100;
        y = -100;
    }
    hungry_level -= 0.05;

    if (find_cayman(caymans)) {
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_run).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 1000);
        if (current_time > dis(gen) && is_first) {
            cayman_found = true;
            float delta_x = eye_cord.x - cayman_x;
            float delta_y = eye_cord.y - cayman_y;

            COORD dest;
            float angle_from_cayman;

            angle_from_cayman = (float)(asin(delta_y / findDistanceTwoPoints(eye_cord, { cayman_x, cayman_y })) *
                180 / M_PI);

            if (delta_x < 0) {
                dest.x = -(float)cos(angle_from_cayman * M_PI / 180) * CAPYBARA_RUN_SPEED;
            }
            else {
                dest.x = (float)cos(angle_from_cayman * M_PI / 180) * CAPYBARA_RUN_SPEED;
            }

            dest.y = (float)sin(angle_from_cayman * M_PI / 180) * CAPYBARA_RUN_SPEED;
            move_x = dest.x;
            move_y = dest.y;
            destination_right = abs(std::asin(move_y / CAPYBARA_RUN_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / CAPYBARA_RUN_SPEED) * 180 / M_PI;

            is_first = false;

        }
        else {
            if (x < 50 && move_x < 0) {
                if (move_y >= 0) {
                    move_x = 0;
                    move_y = CAPYBARA_RUN_SPEED;
                }
                else {
                    move_x = 0;
                    move_y = -CAPYBARA_RUN_SPEED;
                }
            }
            if (x > WIDTH - 200 && move_x > 0) {
                if (move_y >= 0) {
                    move_x = 0;
                    move_y = CAPYBARA_RUN_SPEED;
                }
                else {
                    move_x = 0;
                    move_y = -CAPYBARA_RUN_SPEED;
                }
            }
            if (y < 50 && move_y < 0) {
                if (move_x >= 0) {
                    move_x = CAPYBARA_RUN_SPEED;
                    move_y = 0;
                }
                else {
                    move_x = -CAPYBARA_RUN_SPEED;
                    move_y = 0;
                }
            }
            if (y > HEIGHT - 200 && move_y > 0) {
                if (move_x >= 0) {
                    move_x = CAPYBARA_RUN_SPEED;
                    move_y = 0;
                }
                else {
                    move_x = -CAPYBARA_RUN_SPEED;
                    move_y = 0;
                }
            }
            x += move_x;
            y += move_y;
            run_set_rotation();
        }

    }
    else {
        hungry_level -= 0.05;

        found_close_prey = find_orange(oranges);
        if (hungry_level <= 70 && found_close_prey) {
            prey->is_alive = false;
            hungry_level += 25;
            found_close_prey = false;
            prey = nullptr;
        }

        is_first = true;
        bool gogo = false;
        if (cayman_found) {
            cayman_found = false;
            gogo = true;
        }
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::uniform_int_distribution<> dis(2000, 10000);
        std::random_device rd;
        std::mt19937 gen(rd());
        if (current_time > dis(gen) || gogo) {

            distance_cayman = 1e9;

            start = std::chrono::steady_clock::now();

            std::uniform_int_distribution<> dis(-CAPYBARA_SPEED, CAPYBARA_SPEED);
            move_x = dis(gen);
            move_y = sqrt(CAPYBARA_SPEED * CAPYBARA_SPEED - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if (sign == 2) {
                move_y = -move_y;
            }

            /*
            логику движения объекта в зависимости от наличия ближайшего хищника и генерирует новое 
            случайное направление движения.
            */
            while (true) {
                /*
                Если переменная `found_close_predator` (переменная, определяющая наличие ближайшего хищника) 
                равна true и расстояние между текущим положением объекта и ближайшим хищником меньше, чем 
                расстояние между текущим положением объекта и ближайшим хищником с учетом предполагаемого нового 
                положения (на которое объект собирается переместиться), то происходит следующее:
                */
                if (found_close_cayman && distance(eye_cord.x + move_x, eye_cord.y + move_y, closest_cayman_x, closest_cayman_x) <
                    distance(eye_cord.x, eye_cord.y, closest_cayman_x, closest_cayman_x)) {
                    std::uniform_int_distribution<> dis(-CAPYBARA_SPEED, CAPYBARA_SPEED);
                    move_x = dis(gen);
                    move_y = sqrt(CAPYBARA_SPEED * CAPYBARA_SPEED - move_x * move_x);

                    std::uniform_int_distribution<> dis_zn(1, 2);
                    int sign = dis_zn(gen);
                    if (sign == 2) {
                        move_y = -move_y;
                    }
                }
                else {
                    start = std::chrono::steady_clock::now();
                    break;
                }
            }

            destination_right = abs(std::asin(move_y / CAPYBARA_SPEED) * 180 / M_PI) < 90 && move_x >= 0;
            angle_destination = asin(move_y / CAPYBARA_SPEED) * 180 / M_PI;
            set_rotation();

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
        set_rotation();
    }
}

void move_capybaras(std::vector<capybara>& capybaras, std::vector<cayman>& caymans, std::vector<orange>& oranges) {
    for (auto& c : capybaras) {
        if (c.is_alive) {
            c.move(caymans, oranges);
        }
    }
}
// рыба видит планктон на расстоянии 30
bool capybara::find_orange(std::vector<orange>& oranges) {
    bool is_prey_found = false;
    eye_cord = getCapybaraEyeCoord({ x, y }, inner_eye, angle, width, height);
    float closest_prey = 1e9;
    found_close_prey = false;

    for (int i = 0; i < oranges.size(); i++) {
        COORD temp = { oranges[i].x, oranges[i].y };
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        if (temp_distance < closest_prey && temp_distance <= 30) {
            is_prey_found = true;
            prey = &oranges[i];
        }
    }

    return is_prey_found;
}

    return is_prey_found;
}
