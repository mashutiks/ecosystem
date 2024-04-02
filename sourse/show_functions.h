#pragma once
#include "defines.h"
#include "cayman.h"
#include "capybara.h"
#include "orange.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void show_background(RenderWindow& window, Sprite& sprite);

void show_caymans(std::vector<cayman>& caymans, RenderWindow& window);

void show_capybaras(std::vector<capybara>& capybaras, RenderWindow& window);

void show_oranges(std::vector<orange>& oranges, RenderWindow& window);
