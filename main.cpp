#include <iostream>
#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Toolbox.h"


void restart(){
    Toolbox* toolbox = Toolbox::getInstance();
    toolbox->newGameButton->onClick();
}

void toggleDebugMode(){
    Toolbox* toolbox = Toolbox::getInstance();
    toolbox->debugButton->onClick();
}

int lunch(){
    Toolbox* toolbox = Toolbox::getInstance();
    toolbox->window.create(sf::VideoMode(800, 600), "P4-Minesweeper, Harutyun Sargsyan", sf::Style::Close);
    sf::Image icon;
    
    
    sf::Texture backText;
    sf::Texture tileText;
    sf::Texture debugText;
    sf::Texture newGameText;
    sf::Texture loss;
    sf::Texture win;
    sf::Texture test1;
    sf::Texture test2;
    sf::Texture firstDig;
    sf::Texture secondDig;
    
    
    sf::Sprite tile;
    sf::Sprite back;
    sf::Sprite debug;
    sf::Sprite winSprite;
    sf::Sprite newGameSprite;
    sf::Sprite lossSprite;
    sf::Sprite test1Sprite;
    sf::Sprite firstDigSprite;
    sf::Sprite secondDigSprite;
    sf::Sprite test2Sprite;
    
    firstDigSprite.setPosition(0, 512);
    secondDigSprite.setPosition(21, 512);
    
    toolbox->testButton1->setSprite(&test1Sprite);
    toolbox->testButton2->setSprite(&test2Sprite);
    toolbox->debugButton->setSprite(&debug);
    toolbox->newGameButton->setSprite(&newGameSprite);
    debug.setPosition(toolbox->debugButton->getPosition());
    newGameSprite.setPosition(toolbox->newGameButton->getPosition());
    lossSprite.setPosition(toolbox->newGameButton->getPosition());
    winSprite.setPosition(toolbox->newGameButton->getPosition());
    test1Sprite.setPosition(toolbox->testButton1->getPosition());
    test2Sprite.setPosition(toolbox->testButton2->getPosition());
    
    firstDig.loadFromFile(resourcePath() + "digits.png", sf::IntRect(5 * 21, 0, 21, 32));
    secondDig.loadFromFile(resourcePath() + "digits.png",  sf::IntRect(0 * 21, 0, 21, 32));
    
    firstDigSprite.setTexture(firstDig);
    secondDigSprite.setTexture(secondDig);
    loss.loadFromFile(resourcePath() + "face_lose.png");
    lossSprite.setTexture(loss);
    win.loadFromFile(resourcePath() + "face_win.png");
    winSprite.setTexture(win);
    tileText.loadFromFile(resourcePath() + "tile_hidden.png");
    tile.setTexture(tileText);
    debugText.loadFromFile(resourcePath() + "debug.png");
    debug.setTexture(debugText);
    newGameText.loadFromFile(resourcePath()+"face_happy.png");
    newGameSprite.setTexture(newGameText);
    test1.loadFromFile(resourcePath()+"test_1.png");
    test1Sprite.setTexture(test1);
    test2.loadFromFile(resourcePath() + "test_2.png");
    test2Sprite.setTexture(test2);
    backText.loadFromFile(resourcePath() + "white-background.jpeg", sf::IntRect(0, 0, 800, 600));
    icon.loadFromFile(resourcePath() + "icon.png");
    
    toolbox->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    back.setTexture(backText);
        
    bool isDec = false;
    
    while (toolbox->window.isOpen())
    {
        toolbox->gameState->checkPlayStatus();
        // Process events
        sf::Event event;
        while (toolbox->window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed){
                
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(toolbox->gameState->getPlayStatus()==PLAYING){
                        if(event.mouseButton.y < 512){
                            toolbox->gameState->getTile(event.mouseButton.x, event.mouseButton.y)->onClickLeft();
                        }
                        if(event.mouseButton.x >= 450 && event.mouseButton.x < 522 && event.mouseButton.y >= 512 && event.mouseButton.y <=584){
                            toolbox->debugButton->onClick();
                        }
                    }
                    
                    if(event.mouseButton.x >= 380 && event.mouseButton.x < 452 && event.mouseButton.y >= 512 && event.mouseButton.y <=584){
                        restart();
                    }
                    if(event.mouseButton.x >= 522 && event.mouseButton.x < 594 && event.mouseButton.y >= 512 && event.mouseButton.y <=584){
                        toolbox->testButton1->onClick();
                    }
                    if(event.mouseButton.x > 594 && event.mouseButton.x < 666 && event.mouseButton.y >= 512 && event.mouseButton.y <=584){
                        toolbox->testButton2->onClick();
                    }
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    if(toolbox->gameState->getPlayStatus()==PLAYING){
                        if(event.mouseButton.y < 512){
                            toolbox->gameState->getTile(event.mouseButton.x, event.mouseButton.y)->onClickRight();
                           
                        }
                    }
                   
                }
            }
            
            if(event.type == sf::Event::Closed){
                toolbox->window.close();
            }
        }
        if(toolbox->gameState->getFlagCount() > 9) isDec = false;
        if(toolbox->gameState->getFlagCount() < 10) isDec = true;

        // Clear screen
        toolbox->window.clear();
        int dig1 = std::to_string(toolbox->gameState->getFlagCount())[0] - '0';
        int dig2 = std::to_string(toolbox->gameState->getFlagCount())[1] - '0';
        firstDig.loadFromFile(resourcePath() + "digits.png", sf::IntRect(dig1 * 21, 0, 21, 32));
        secondDig.loadFromFile(resourcePath() + "digits.png",  sf::IntRect(dig2 * 21, 0, 21, 32));
        if(toolbox->gameState->getPlayStatus()==PLAYING){
            toolbox->newGameButton->setSprite(&newGameSprite);
        }
        
        if(toolbox->gameState->getPlayStatus()==LOSS){
            toolbox->newGameButton->setSprite(&lossSprite);
            for(int i = 0; i < toolbox->gameState->SIZE; ++i ){
                if(toolbox->gameState->getArr()[i].getState()==HIDDEN && toolbox->gameState->getArr()[i].getIsMine()){
                    toolbox->gameState->getArr()[i].setState(EXPLODED);
                }
            }
        }
        
        if(toolbox->gameState->getPlayStatus()==WIN){
            toolbox->newGameButton->setSprite(&winSprite);
        }
        toolbox->window.draw(back);
        for (int i = 0; i < toolbox->gameState->SIZE; ++i) {
            toolbox->gameState->getArr()[i].draw();
        }
        
        toolbox->window.draw(*toolbox->debugButton->getSprite());
        toolbox->window.draw(*toolbox->newGameButton->getSprite());
        toolbox->window.draw(*toolbox->testButton1->getSprite());
        toolbox->window.draw(*toolbox->testButton2->getSprite());
        toolbox->window.draw(firstDigSprite);
        if(!isDec) toolbox->window.draw(secondDigSprite);
        
        // Update the window
        toolbox->window.display();
    }
    return 0;
}

int main() {return lunch();};

