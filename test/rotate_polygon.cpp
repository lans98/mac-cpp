#include <cmath>
#include <iostream>
#include <linear_transformation.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace mac;

int main() {
    sf::RenderWindow render_window(sf::VideoMode(400, 400), "My Window");

    bool running = true;
    while (running) {
        sf::Event window_event;
        while (render_window.pollEvent(window_event)) {
            switch (window_event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }

    Matrix polygon({
        { 2, 2 },
        { 4, 2 },
        { 4, 4 },
        { 2, 4 }
    });

    cout << "Initial polygon (each row is a vertice)\n";
    cout << polygon;

    LinearTransformation rotate(2, 2, Matrix({
        { cos(M_PI/2), -sin(M_PI/2) },
        { sin(M_PI/2),  cos(M_PI/2) }
    }));

    for (auto i = 0; i < polygon.n_rows; ++i)
        polygon.row(i) = rotate(RVector(polygon.row(i)));

    cout << "Rotated polygon (each row is a vertice)\n";
    cout << polygon;
}

