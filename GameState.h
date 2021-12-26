#include <SFML/Graphics.hpp>
#include "Tile.h"

#ifndef GameState_h
#define GameState_h

enum PlayStatus { WIN, LOSS, PLAYING };

class GameState {
    private:
        static const int a = 32;
        int mineCount = 0;
        int flagCount = 50;
        sf::Vector2i dimensions;
        Tile* arr;
        PlayStatus status = PLAYING;
        bool* mines;
        
    public:
        void checkPlayStatus();
        void setMines(bool* _mines);
        static const int SIZE = 400;
        GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50, bool* mineArray = nullptr);
        GameState(const char* filepath);
        int getFlagCount();
        void setFlagCount(int count);
        void increaseFlagCountByOne(char n);
        int getMineCount();
        sf::Vector2i getDimensions();
        Tile* getArr();
        Tile* getTile(int x, int y);
        PlayStatus getPlayStatus();
        void setPlayStatus(PlayStatus _status);
};

#endif /* GameState_h */
