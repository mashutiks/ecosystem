#include "cayman.h"
#include "capybara.h"
#include "defines.h"
#define _USE_MATH_DEFINES
#include <math.h>

void cayman::set_rotation() {
    double angle_rad = atan2(move_y, move_x);
    int degrees = round(angle_rad * 180 / M_PI);
    int nearest_multiple = round(degrees / 45) * 45;
    angle = nearest_multiple * M_PI / 180;
}

void move_caymans(std::vector<cayman>& caymans, std::vector<capybara>& capybaras) {
    for (auto& pr : caymans) {
        if (pr.is_alive) {
            pr.move(capybaras);
        }
    }
}

void cayman::move(std::vector<capybara>& capybaras) {
    {
        COORD eye{};
        COORD inner = CAYMAN_EYE;

        inner_eye = inner;
        eye_cord = eye;
    }

    // условия смерти
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> life(-30000, 30000);

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - life_start).count() > CAYMAN_LIFE_TIME + life(gen) || hungry_level <= 0) {
        is_alive = false;
        x = -100;
        y = -100;
    }

    // условия охоты. Охота начинается при голоде < 30, максимальное значение 100 (насыщение). Начальный уровень = 31. 
    hungry_level -= 0.05;
    if (hunt && !found_close_prey) {
        hunt = true;
        found_close_prey = find_capybara(capybaras);
        speed = CAYMAN_HUNT_SPEED;
    }
    if (hungry_level < 30 && !hunt) {
        hunt = true;
        found_close_prey = find_capybara(capybaras);
        speed = CAYMAN_HUNT_SPEED;
    }
    if (hungry_level >= 90) {
        speed = CAYMAN_SPEED;
        hunt = false;
        prey = nullptr;
    }

    if ((hungry_level >= 30 && !hunt) || (hunt && !found_close_prey)) {
        auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(6000, 12000);

        if (current_time > dis(gen)) {

            start = std::chrono::steady_clock::now();
            std::uniform_int_distribution<> dis(-speed, speed);
            move_x = dis(gen);
            move_y = sqrt(speed * speed - move_x * move_x);

            std::uniform_int_distribution<> dis_zn(1, 2);
            int sign = dis_zn(gen);
            if (sign == 2) {
                move_y = -move_y;
            }

            //destination_right = abs(std::asin(move_y / speed) * 180 / M_PI) < 90 && move_x >= 0;
            //angle_destination = asin(move_y / speed) * 180 / M_PI;

        }
        else {

            x += move_x;
            y += move_y;
            if (x < 100 && move_x < 0) {
                move_x = -move_x;
            }
            if (x > WIDTH - 200 && move_x > 0) {
                move_x = -move_x;
            }
            if (y < 100 && move_y < 0) {
                move_y = -move_y;
            }
            if (y > HEIGHT - 200 && move_y > 0) {
                move_y = -move_y;
            }
        }
    }

    else {
        eye_cord = getCapybaraEyeCoord({ x, y }, inner_eye, angle, CAYMAN_WIDTH, CAYMAN_HEIGHT);
        COORD closest_point = { prey->x, prey->y };

        if (findDistanceTwoPoints(closest_point, eye_cord) < 25) {
            prey->is_alive = false;
            hungry_level += 30;
            if (hungry_level > 100) {
                hungry_level = 100;
            }
            found_close_prey = false;
            prey = nullptr;
        };

        float angle_from_prey = angle_between_two_coordinates(closest_point, eye_cord);
        move_x = cos(angle_from_prey * M_PI / 180) * speed;
        move_y = sin(angle_from_prey * M_PI / 180) * speed;
        x += move_x;
        y += move_y;
    }
    set_rotation();
}

// Поиск рыб при охоте
bool cayman::find_capybara(std::vector<capybara>& capybaras) {
    bool is_prey_found = false;
    eye_cord = getCapybaraEyeCoord({ x, y }, inner_eye, angle, CAYMAN_WIDTH, CAYMAN_HEIGHT);
    float closest_prey = 1e9;
    found_close_prey = false;
    // перебор всех рыб, поиск ближайшей
    for (int i = 0; i < capybaras.size(); i++) {
        COORD temp = getClosestFromPoint({ capybaras[i].x, capybaras[i].y }, capybaras[i].width, capybaras[i].height, capybaras[i].angle, eye_cord);
        // расстояние между временно найденной ближайшей точкой и глазом хищника
        float temp_distance = findDistanceTwoPoints(temp, eye_cord);
        // проверяется, если временное расстояние меньше текущего ближайшего расстояния, оно находится в пределах охотничьего расстояния, и рыба еще не была поймана.
        if (temp_distance < closest_prey && temp_distance <= CAYMAN_HUNT_DISTANCE && !capybaras[i].is_hunted) {
            is_prey_found = true;
            prey = &capybaras[i];
            capybaras[i].is_hunted = true;
        }
    }
    return is_prey_found;
}
