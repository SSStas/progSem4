#pragma once


#include <list>
#include <string>
#include <cstdlib>
#include "controller.h"

using point = std::pair<int, int>;
using size_frame = std::pair<int, int>;
using snakeData = std::pair<int, std::list<point>>;

class Model;
class Snake;
class Rabbit;

class Rabbit {
    point position;
    int scores;

    public:
        Rabbit(int height, int width, std::list<Snake*> &snakes, std::list<Rabbit*> &rabbits, int sc );
        point getPos() { return position; }
        int getScores() { return scores; }
};

class Snake {
    static const point dirVaritions[5];
    int dir;
    int lastDir;
    int growthPoints;
    int color;
    std::string keysMove;

    void setGrowthPoints(int num=1);

    public:
        std::list<point> posParts;

        Snake(int x, int y, int len, int direction, std::string keysMove, int color);
        Snake(int height, int width, int len, std::list<Snake*> &snakes, std::string keysMove, int color);
        void move();
        bool frameCollision(int height, int width);
        bool selfCollision();
        bool snakesCollision(const Snake *snake); 
        bool isSnakePoint(point pos);
        int getColor();
        std::string getKeys();
        void eatRabbits(std::list<Rabbit*> &rabbits);
        void changeDirection(int c);
};

class Model {
    int height, width;
    std::list<Snake*> snakes;
    std::list<Rabbit*> rabbits;
    int rabbitsCount;
    
    public:
        Model(int height, int width, std::string keysMove, int rabbitsCount);

        void makeNextStep();
        void getRabbitsData(std::list<point> &data);
        void getSnakesData(std::list<snakeData> &data);
        void setSnakeKeys(Controller &keyboard);
        size_frame getSize();

        ~Model();
};
