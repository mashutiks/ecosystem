#include <SFML/Graphics.hpp>
#include <iostream>
//#include <vector>
#include <thread>
//#include <chrono>
#include "cayman.h"
#include "show_functions.h"
#include "adding.h"
#include "orange.h"
#include "deleting.h"

int main() 
{
    std::vector<capybara> capybaras(15);
    std::vector<cayman> сaymans(4);
    std::vector<orange> oranges(30);
    int count = 0;
    int open_time = 0;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Lake"); // создание окна отрисовки с указанными размерами и названием
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now(); // получение временной метки для начала отсчета времени

    Sprite sprite;
    sf::Image image;
    image.loadFromFile(BACKGROUND_PATH);
    Texture texture;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    //text
    sf::Font font;
    font.loadFromFile("C:/Program Files (x86)/for ecos/lake/ClassicRobotItalic.ttf"); 
    //endtext

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        // показ, взаидодействия классов с другими
        show_background(window, sprite);
        show_capybaras(capybaras, window);
        move_capybaras(capybaras, сaymans, oranges);
        show_caymans(сaymans, window);
        move_caymans(сaymans, capybaras);
        show_oranges(oranges, window);
        move_oranges(oranges);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        open_time++;
        // Отображение счетчика в правом верхнем углу окна
        sf::Text text;
        text.setFont(font);
        text.setString("Count: " + std::to_string(open_time));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(WIDTH - text.getGlobalBounds().width - 10, 10);
        window.draw(text);

        window.display();

        // реализация размножения (47-56). Новые объекты появляются через определенные интервалы.
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 5000 > count) 
        // Если количество миллисекунд, прошедших с момента `start`, поделенное на 5000, больше чем значение переменной `count`, то выполнить действие.
        {
            count++;
            add_capybara(capybaras);
            add_cayman(сaymans);
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000 > count) {
            add_orange(oranges);
        }
        
        delete_caymans(сaymans);
        delete_capybaras(capybaras);
        delete_oranges(oranges);

    }
    return 0;
}
