#pragma once

#include "capybara.h"
#include "orange.h"
#include "cayman.h"


std::vector<int> get_capybaras_to_delete(std::vector<capybara>& capybaras) {
    std::vector<int> capybaras_to_delete;
    for (int i = 0; i < capybaras.size(); i++) {
        if (!capybaras[i].is_alive) {
            capybaras_to_delete.push_back(i);
        }
    }
    return capybaras_to_delete;
}

void delete_capybaras(std::vector<capybara>& capybaras) {;
    for (auto& i : get_capybaras_to_delete(capybaras)) {
        capybaras.erase(capybaras.begin() + i);
    }
}



std::vector<int> get_caymans_to_delete(std::vector<cayman>& caymans) {
    std::vector<int> caymans_to_delete;
    for (int i = 0; i < caymans.size(); i++) {
        if (!caymans[i].is_alive) {
            caymans_to_delete.push_back(i);
        }
    }
    return caymans_to_delete;
}

void delete_caymans(std::vector<cayman>& caymans) {
    for (auto& i : get_caymans_to_delete(caymans)) {
        caymans.erase(caymans.begin() + i);
    }
}



std::vector<int> get_oranges_to_delete(std::vector<orange>& oranges) {
    std::vector<int> oranges_to_delete;
    for (int i = 0; i < oranges.size(); i++) {
        if (!oranges[i].is_alive) {
            oranges_to_delete.push_back(i);
        }
    }
    return oranges_to_delete;
}

void delete_oranges(std::vector<orange>& oranges) {
    for (auto& i : get_oranges_to_delete(oranges)) {
        oranges.erase(oranges.begin() + i);
    }
}

