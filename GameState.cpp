#include <stdio.h>
#include <array>
#include "GameState.h"
#include <math.h>
#include <random>


GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines, bool* mineArray){
    mineCount = _numberOfMines;
    dimensions = _dimensions;
    arr = new Tile[SIZE];
    this->mines = mineArray;
    
    for(int row = 0; row < dimensions.y; ++row){
        for(int col = 0; col < dimensions.x; ++col){
            sf::Vector2f newVec(a*col, a*row);
            arr[dimensions.x*row+col] =  *new Tile(newVec, mines[dimensions.x*row+col]);
        }
    }
    
    for(int i = 0; i < SIZE; ++i){
        std::array<Tile*, 8> array;
        
        if(i == 0){
            array[0] = &arr[i+1];
            array[1] = &arr[i+25];
            array[2] = &arr[i+26];
            array[3] = nullptr;
            array[4] = nullptr;
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        
        else if (i==24){
            array[0] = &arr[i-1];
            array[1] = &arr[i+24];
            array[2] = &arr[i+25];
            array[3] = nullptr;
            array[4] = nullptr;
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        else if(i==375){
            array[0] = &arr[i-25];
            array[1] = &arr[i-24];
            array[2] = &arr[i+1];
            array[3] = nullptr;
            array[4] = nullptr;
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        else if(i==399){
            array[0] = &arr[i-25];
            array[1] = &arr[i-26];
            array[2] = &arr[i-1];
            array[3] = nullptr;
            array[4] = nullptr;
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        else if(i < 24){
            array[0] = &arr[i-1];
            array[1] = &arr[i+24];
            array[2] = &arr[i+25];
            array[3] = &arr[i+26];
            array[4] = &arr[i+1];
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        else if (i % 25 == 0){
            array[0] = &arr[i-25];
            array[1] = &arr[i-24];
            array[2] = &arr[i+1];
            array[3] = &arr[i+26];
            array[4] = &arr[i+25];
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        
        else if (i % 25 == 24){
            array[0] = &arr[i-25];
            array[1] = &arr[i-26];
            array[2] = &arr[i-1];
            array[3] = &arr[i+24];
            array[4] = &arr[i+25];
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        
        else if (i > 375){
            array[0] = &arr[i-1];
            array[1] = &arr[i-26];
            array[2] = &arr[i-25];
            array[3] = &arr[i-24];
            array[4] = &arr[i+1];
            array[5] = nullptr;
            array[6] = nullptr;
            array[7] = nullptr;
        }
        
        else{
            array[0] = &arr[i-26];
            array[1] = &arr[i-25];
            array[2] = &arr[i-24];
            array[3] = &arr[i-1];
            array[4] = &arr[i+1];
            array[5] = &arr[i+24];
            array[6] = &arr[i+25];
            array[7] = &arr[i+26];
        };
        arr[i].setNeighbors(array);
    }
}

int GameState::getMineCount(){
    return mineCount;
}

void GameState::setFlagCount(int count){
    this->flagCount = count;
}


sf::Vector2i GameState::getDimensions(){
    return dimensions;
}

Tile* GameState::getArr(){
    return arr;
}

int GameState::getFlagCount(){
    return this->flagCount;
}

PlayStatus GameState::getPlayStatus(){
    return this->status;
}

void GameState::checkPlayStatus(){
    int revealedTiles = 0;
    for (int i = 0; i < SIZE; ++i) {
        if(arr[i].getState() == EXPLODED){
            setPlayStatus(LOSS);
            return;
        }
        if(arr[i].getState() == REVEALED){
            revealedTiles++;
        }
    }
    if(flagCount==0 && revealedTiles == SIZE-getMineCount()){
        setPlayStatus(WIN);
    }
}

void GameState::increaseFlagCountByOne(char n){
    flagCount = flagCount+n;
}

void GameState::setPlayStatus(PlayStatus _status){
    this->status = _status;
}

Tile* GameState::getTile(int x, int y){
    int c_x = ceil(x/a);
    int c_y = ceil(y/a);
    return &arr[c_x+c_y*getDimensions().x];
}
