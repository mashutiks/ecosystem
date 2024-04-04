#include "capybara.h"
#include "cayman.h"
//#include "path_generate.h"
#include "show_functions.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void show_background(RenderWindow& window, Sprite& sprite) {
    window.draw(sprite);
}


void show_caymans(std::vector<cayman>& caymans, RenderWindow& window) {
    sf::Image cayman_image;
    Texture cayman_texture;
    Sprite cayman_sprite;

    for (auto& c : caymans) {
        if (!c.is_alive) {
            continue;
        }

        cayman_image.loadFromFile(TYPE_CAYMAN);
        cayman_texture.loadFromImage(cayman_image);
        cayman_sprite.setTexture(cayman_texture);
        cayman_sprite.setOrigin(100, 50);
        cayman_sprite.setPosition(c.x, c.y);
        cayman_sprite.setRotation(-c.angle);
 
        window.draw(cayman_sprite);
    }

}


void show_capybaras(std::vector<capybara>& capybaras, RenderWindow& window) {
    sf::Image capybara_image;
    Texture capybara_texture;
    Sprite capybara_sprite;
 

    for (auto& c : capybaras) {
        if (!c.is_alive) {
            continue;
        }

        capybara_image.loadFromFile(TYPE_CAPYBARA);
        capybara_texture.loadFromImage(capybara_image);
        capybara_sprite.setTexture(capybara_texture);
        capybara_sprite.setOrigin(100, 50);
        capybara_sprite.setPosition(c.x, c.y);
        capybara_sprite.setRotation(-c.angle);

        window.draw(capybara_sprite);
    }

}

void show_oranges(std::vector<orange>& oranges, RenderWindow& window) {
    sf::Image orange_image;
    Texture orange_texture;
    Sprite orange_sprite;
    for (auto& o : oranges) {
        if (!o.is_alive) {
            continue;
        }

        orange_image.loadFromFile(TYPE_ORANGE);
        orange_texture.loadFromImage(orange_image);
        orange_sprite.setTexture(orange_texture);
        orange_sprite.setOrigin(100, 50);
        orange_sprite.setPosition(o.x, o.y);

        window.draw(orange_sprite);
    }
}
