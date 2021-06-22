#ifndef GE_HPP
#define GE_HPP

#include <SFML/Graphics.hpp>
#include "state/state.hpp"
#include "res/resource.hpp"
#include "res/texture.hpp"

namespace ge{
    struct Data{
        sf::RenderWindow window;
        sf::Clock clock;
        unsigned int width;
        unsigned int height;
        state::Handler state;
    };

    inline void CreateWindow(Data *data, unsigned int width, unsigned int height, const char *title){
        data->width = width;
        data->height = height;
        data->window.create(sf::VideoMode(width, height), title);
    }

    inline void Run(Data *data, float UPS = 1.0f / 60.0f){
        float delta = data->clock.getElapsedTime().asSeconds();
        float new_delta = 0.0f, elapsed = 0.0f;

        while(data->window.isOpen()){
            new_delta = data->clock.getElapsedTime().asSeconds();
            elapsed += new_delta - delta;
            delta = new_delta;

            if(elapsed > UPS){
                data->state.update();
                elapsed -= UPS;
            }

            data->window.clear();
            data->state.update();
            data->window.display();
        }
    }
}

#endif // !GE_HPP