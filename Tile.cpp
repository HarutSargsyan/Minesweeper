#include "Tile.h"
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"


Toolbox* toolbox = Toolbox::getInstance();

Tile::Tile(sf::Vector2f _position, bool _isMine){
    this->position = _position;
    this->isMine = _isMine;
}

State Tile::getState(){
    return this->state;
}

void Tile::setState(State _state){
    state = _state;
}

sf::Vector2f Tile::getLocation(){
    return this->position;
};

bool Tile::getIsMine(){
    return this->isMine;
}

void Tile::setNeighbors(std::array<Tile*,8> _neighbors){
    neighbour_tiles = _neighbors;
}

std::array<Tile*, 8>& Tile::getNeighbors(){
    return this->neighbour_tiles;
}

void Tile::revealNeighbors(){
    for (int i = 0; i < 8; ++i){
        if(!(this->getNeighbors()[i] == nullptr)){
            this->getNeighbors()[i]->open();
        }
    }
}

void Tile::open(){
    if(this->state==REVEALED || this->state==FLAGGED ){
        return;
    }
    setState(REVEALED);
    for (int i = 0; i < 8; ++i) {
        if(!(this->getNeighbors()[i]==nullptr)){
            if(this->getNeighbors()[i]->getIsMine()){
                return;
            }
        }
    }
    
    this->revealNeighbors();

}

void Tile::onClickLeft(){
    if(this->getIsMine()){
        this->setState(EXPLODED);
        toolbox->gameState->setPlayStatus(LOSS);
        return;
    }
    this->open();
}

void Tile::onClickRight(){
    if(this->state == FLAGGED){
        this->setState(HIDDEN);
        toolbox->gameState->increaseFlagCountByOne(1);
    }
    else if(this->state==HIDDEN){
        if(toolbox->gameState->getFlagCount() > 0){
            this->setState(FLAGGED);
            toolbox->gameState->increaseFlagCountByOne(-1);
        }
    }
}



Tile::Tile(){}

void Tile::draw(){
    int neighbourMinesCount = 0;
    sf::Texture texture_hidden;
    sf::Texture texture_revealed;
    sf::Texture flag;
    sf::Texture bomb;
    sf::Texture mineCount;
    
    
    for (int i = 0; i < 8; ++i) {
        if(!(this->getNeighbors()[i]==nullptr)){
            if(this->getNeighbors()[i]->isMine){
                neighbourMinesCount++;
            }
        }
    }
    
    bomb.loadFromFile(resourcePath() + "mine.png");
    texture_hidden.loadFromFile(resourcePath() + "tile_hidden.png");
    texture_revealed.loadFromFile(resourcePath()+"tile_revealed.png");
    flag.loadFromFile(resourcePath() + "flag.png");
    
    sf::Sprite sprite;
    if(state==HIDDEN){
        sprite.setTexture(texture_hidden);
    }
    if(state==EXPLODED){
        sprite.setTexture(bomb);
    }
    if(state==FLAGGED){
        sprite.setTexture(flag);
    }
    if(state==REVEALED){
        if(this->getIsMine()){
            sprite.setTexture(bomb);
        }
        else if(!(neighbourMinesCount==0)){
            mineCount.loadFromFile(resourcePath() + "number_" + std::to_string(neighbourMinesCount) + ".png");
            sprite.setTexture(mineCount);

        }else{
            sprite.setTexture(texture_revealed);
        }
    }
    sprite.setPosition(this->position);
    toolbox->window.draw(sprite);
}
