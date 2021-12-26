#include <SFML/Graphics.hpp>

#ifndef Button_h
#define Button_h

class Button {
    sf::Sprite* sprite;
    sf::Vector2f position;
    std::function<void(void)> __onClick;
    public:
        Button(sf::Vector2f _position, std::function<void(void)> _onClick);
        sf::Vector2f getPosition();
        sf::Sprite* getSprite();
        void setSprite(sf::Sprite* _sprite);
        void onClick();
};

#endif /* Button_h */
