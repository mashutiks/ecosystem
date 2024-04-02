#include "adding.h"
#define _USE_MATH_DEFINES
#include <math.h>

void add_capybara(std::vector<capybara>& capybaras) {
    if (capybaras.size() >= MIN_CAPYBARA_COUNT) {
        return;
    }
    float x{}, y{};
    for (auto& cap : capybaras) {
        if (cap.hungry_level > 50) {
            x = cap.x;
            y = cap.y;
        }
    }
    capybaras.push_back(capybara());
    capybaras[capybaras.size() - 1].x = x;
    capybaras[capybaras.size() - 1].y = y;
}

void add_cayman(std::vector<cayman>& caymans) {
    if (caymans.size() >= MIN_CAYMAN_COUNT) {
        return;
    }
    float x{}, y{};
    for (auto& cay : caymans) {
        if (cay.hungry_level > 50) {
            x = cay.x;
            y = cay.y;
        }
    }
    caymans.push_back(cayman());
    caymans[caymans.size() - 1].x = x;
    caymans[caymans.size() - 1].y = y;
}

void add_orange(std::vector<orange>& oranges) {
    if (oranges.size() >= MIN_ORANGE_COUNT) {
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> x_dis(0, WIDTH/4);
    std::uniform_int_distribution<> y_dis(0, HEIGHT/4);
    int x = x_dis(gen);
    int y = y_dis(gen);
    oranges.push_back(orange());
    oranges[oranges.size() - 1].x = x;
    oranges[oranges.size() - 1].y = y;
}
