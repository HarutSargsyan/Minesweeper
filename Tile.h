#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#ifndef Tile_h
#define Tile_h

enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

class Tile {
    State state = HIDDEN;
    sf::Vector2f position;
    std::array<Tile*, 8> neighbour_tiles;
    bool isMine = false;
    
    public:
        Tile();
        Tile(sf::Vector2f _position, bool _isMine);
        sf::Vector2f getLocation();
        State getState();
        bool getIsMine();
        std::array<Tile*, 8>& getNeighbors();
        void setState(State _state);
        void setNeighbors(std::array<Tile*,8> _neighbors);
        void open();
        void onClickLeft();
        void onClickRight();
        void draw();
    protected:
        void revealNeighbors();
};

#endif /* Tile_h */
