#include "Toolbox.h"
#include "Button.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include "ResourcePath.hpp"


using std::cout;

Toolbox* Toolbox::instance = nullptr;

bool* test(std::string name){
    std::string newStr = "";
    bool* minesArray;
    minesArray = new bool[400];
    std::ifstream t(resourcePath() + name);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    for (int i = 0; i < str.length(); ++i) {
        if(i%26==25){
            continue;
        }
        std::string s(1, str[i]);
        newStr.append(s);
    }
    for (int i = 0; i < 400; ++i) {
        if(newStr[i]=='0'){
            minesArray[i] = 0;
        }
        else{
            minesArray[i] = 1;

        }
    }
    return minesArray;
}
Toolbox::Toolbox(){
    
   
    
    bool* minesArray;
    int mineNumber = 0;
    int mineCount  = 50;
    minesArray = new bool[400];
    
    for(int i = 0; i < 400; ++i){
        bool is_Mine = round((float) rand()/RAND_MAX - 0.34);
        if(is_Mine){
            mineNumber++;
        }
        if(mineNumber > mineCount){
            is_Mine = false;
        }
        minesArray[i] = is_Mine;
    }
    gameState = new GameState(sf::Vector2i(25, 16), 50, minesArray);
    sf::Vector2f debug(450, 512);
    sf::Vector2f newGame(380, 512);
    sf::Vector2f test1(522, 512);
    sf::Vector2f test2(594, 512);
    debugButton = new Button(debug, [&](){
        for(int i = 0; i < gameState->SIZE; ++i ){
            if(gameState->getArr()[i].getState()==HIDDEN && gameState->getArr()[i].getIsMine()){
                gameState->getArr()[i].setState(REVEALED);
            } else if(gameState->getArr()[i].getState()==REVEALED && gameState->getArr()[i].getIsMine()){
                gameState->getArr()[i].setState(HIDDEN);
            }
            gameState->getArr()[i].draw();
        }
    });
    newGameButton = new Button(newGame, [&](){
        delete gameState;
        bool* minesArray;
        int mineNumber = 0;
        int mineCount  = 50;
        minesArray = new bool[400];
        
        for(int i = 0; i < 400; ++i){
            bool is_Mine = round((float) rand()/RAND_MAX - 0.34);
            if(is_Mine){
                mineNumber++;
            }
            if(mineNumber > mineCount){
                is_Mine = false;
            }
            minesArray[i] = is_Mine;
        }
        gameState = new GameState(sf::Vector2i(25, 16), 50, minesArray);
    });
    testButton1 = new Button(test1,  [&](){
        delete gameState;
        gameState = new GameState(sf::Vector2i(25, 16), 50, test("testboard1.brd"));
        
    });
    testButton2 = new Button(test2,  [&](){
        delete gameState;
        gameState = new GameState(sf::Vector2i(25, 16), 50, test("testboard2.brd"));
    });
}
