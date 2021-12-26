#include "Button.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick){
    this->position = _position;
    __onClick = _onClick;
    
}

void Button::onClick(){
    __onClick();
}

sf::Sprite* Button::getSprite(){
    return sprite;
}

sf::Vector2f Button::getPosition(){
    return position;
};

void Button::setSprite(sf::Sprite* _sprite){
    sprite = _sprite;
};
