#pragma once


#include <list>
#include <string>
#include <cstdlib>
#include "controller.h"

typedef enum {
    EMPTY = 0,
    RABBIT = 1,
    SNAKE1, 
    SNAKE2,
    SNAKE3,
} CELL_ID;

using point = std::pair<int, int>;
using size_frame = std::pair<int, int>;
using uploadData = std::list<std::pair<CELL_ID, point>>;
using deletedData = std::list<point>;

class Model;
class Snake;
class Rabbit;

class Rabbit {
    point position;
    int scores;

    public:
        Rabbit(int height, int width, std::list<Snake*> &snakes, std::list<Rabbit*> &rabbits, int sc);
        point getPos() { return position; }
        int getScores() { return scores; }
};

class Snake {
    static const point dirVaritions[5];
    int dir;
    int lastDir;
    int growthPoints;
    CELL_ID id;
    std::string keysMove;

    void setGrowthPoints(int num=1);

    public:
        std::list<point> posParts;

        Snake(int x, int y, int len, int direction, std::string keysMove, CELL_ID id);
        Snake(int height, int width, int len, std::list<Snake*> &snakes, std::string keysMove, CELL_ID id);
        void move(deletedData &delData);
        bool frameCollision(int height, int width);
        bool selfCollision();
        bool snakesCollision(const Snake *snake); 
        bool isSnakePoint(point pos);
        CELL_ID getId();
        std::string getKeys();
        void eatRabbits(std::list<Rabbit*> &rabbits);
        void changeDirection(int c);
};

class Model {
    int height, width;
    std::list<Snake*> snakes;
    std::list<Rabbit*> rabbits;
    int rabbitsCount;

    void setDeletedSnakePos(Snake *snake, deletedData &data);
    void getCurrentData(uploadData &data);
    
    public:
        Model(int height, int width, std::string keysMove, int rabbitsCount);

        void makeNextStep(uploadData &upData, deletedData &delData);
        void setSnakeKeys(Controller &keyboard);
        size_frame getSize();

        ~Model();
};
