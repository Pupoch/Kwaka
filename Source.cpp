#include <SFML/Graphics.hpp>
#include<iostream>
#include "math.h"
using namespace std;


int main() {

    long double PI = 3.14159265358979323846;

    long double _width = 1280;
    long double _height = 720;

    sf::RenderWindow window(sf::VideoMode(_width, _height), "Pseudo3D");
    int vlines = 150;
    long double fov = 90.0;

    sf::RectangleShape* rect = new sf::RectangleShape[vlines];

    long double _w = _width / vlines;

    int n = 16;
    int map[16][16] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };



    long double plr_x = 2;
    long double plr_y = 2;
    long double dir_x = 0;
    long double dir_y = 0;
    long double plr_rot = 45;
    long double mov_spd = 0.06;
    long double view_len = 7.0;
    long double mouse_sens = 0.3;
    long double collision_step = 0.005;
    sf::Vertex bott[] =
    {
        sf::Vertex(sf::Vector2f(0, _height * 0.2), sf::Color::Black),
        sf::Vertex(sf::Vector2f(_width, _height * 0.2), sf::Color::Black),
        sf::Vertex(sf::Vector2f(_width, _height), sf::Color(128, 128, 128)),
        sf::Vertex(sf::Vector2f(0, _height), sf::Color(128, 128, 128))
    };
    

    sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);
    bool mouse_in_place = true;
    window.setMouseCursorVisible(false);
    sf::Clock mCl;
    mCl.restart();
    sf::Text text;
    sf::Font font;
    font.loadFromFile("PressStart2P.ttf");
    text.setFont(font);
    text.setPosition(sf::Vector2f(0, 0));
    
    window.setFramerateLimit(60);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(bott, 4, sf::Quads);

        dir_x = 0;
        dir_y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dir_x += cos((plr_rot - 90.0) * PI / 180);
            dir_y += sin((plr_rot - 90.0) * PI / 180);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dir_x += cos((plr_rot + 90.0) * PI / 180);
            dir_y += sin((plr_rot + 90.0) * PI / 180);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dir_x += cos(plr_rot * PI / 180);
            dir_y += sin(plr_rot * PI / 180);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dir_x -= cos(plr_rot * PI / 180);
            dir_y -= sin(plr_rot * PI / 180);
        }

        float delta = mCl.getElapsedTime().asSeconds();
        text.setString("fps = " + to_string(int(1.0 / delta)));
        mCl.restart();
        window.draw(text);

        sf::Vector2i mouse_relative = sf::Mouse::getPosition(window) - lastMousePosition;

        if (mouse_in_place) {
            plr_rot += mouse_relative.x * mouse_sens;
        }

        dir_x *= mov_spd;
        dir_y *= mov_spd;

        int curr_x = static_cast<int>(plr_x);
        int curr_y = static_cast<int>(plr_y);
        int new_x = static_cast<int>(plr_x + dir_x * (5.0));
        int new_y = static_cast<int>(plr_y + dir_y * (5.0));

        if (map[curr_x][new_y] != 1) {
            plr_y += dir_y;
        }
        if (map[new_x][curr_y] != 1) {
            plr_x += dir_x;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.setMouseCursorVisible(mouse_in_place);
            mouse_in_place = !mouse_in_place;
        }

        if (mouse_in_place) {
            sf::Mouse::setPosition(sf::Vector2i(_width / 2, _height / 2), window);
        }

        lastMousePosition = sf::Mouse::getPosition(window);

        for (int x = 0; x < vlines; x++) {
            long double delta_a = fov * (x - vlines / 2) / vlines;
            long double view_rot = plr_rot + delta_a;
            for (long double len = 0; len < view_len; len += collision_step) {
                int curr_x = static_cast<int>(plr_x + cos(view_rot * PI / 180) * len);
                int curr_y = static_cast<int>(plr_y + sin(view_rot * PI / 180) * len);
                curr_x = ((curr_x % n) + n) % n;
                curr_y = ((curr_y % n) + n) % n;

                if (map[curr_x][curr_y] == 1) {
                    rect[x].setFillColor(sf::Color(64, 64, 255, 255.0 * (1.0 - (len / view_len))));
                    long double block_h = _height / (len * cos(delta_a * PI / 240));
                    rect[x].setSize(sf::Vector2f(_w, block_h));
                    rect[x].setPosition(sf::Vector2f(_w * x, _height / 2 - block_h / 2));
                    window.draw(rect[x]);
                    break;
                }
            }
        }
        window.display();

    }
    return 0;
}
