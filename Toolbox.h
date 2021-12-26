#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"


#ifndef Toolbox_h
#define Toolbox_h

class Toolbox {
    
    public:
        sf::RenderWindow window;
        GameState* gameState;
        Button* debugButton;
        Button* newGameButton;
        Button* testButton1;
        Button* testButton2;
        inline static Toolbox* getInstance() { return instance ? instance : instance = new Toolbox(); }
    private:
        static Toolbox* instance;
        Toolbox();
};

#endif /* Toolbox_h */
