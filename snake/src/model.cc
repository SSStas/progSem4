#include "model.h"


const point Snake::dirVaritions[5] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

Rabbit::Rabbit(int height, int width, std::list<Snake*> &snakes, std::list<Rabbit*> &rabbits, int sc) {
    bool isGetPos;

    do {
        position = {std::rand() % width, std::rand() % height};
        isGetPos = true;

        for (auto it = snakes.begin(); it != snakes.end(); ++it) {
            if ((*it)->isSnakePoint(position)) {
                isGetPos = false;
                break;
            }
        }

        for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
            if ((*it)->getPos() == position) {
                isGetPos = false;
                break;
            }
        }
    } while (!isGetPos);

    scores = sc;
}

Snake::Snake(int x, int y, int len, int direction, std::string keysMove, int color) {
    dir = (1 <= direction || direction <= 4) ? direction : 0;
    growthPoints = 0;
    this->keysMove = keysMove;
    this->color = color;

    for (int i = 0; i < len; ++i) {
        switch (dir) {
        case 1:
            posParts.push_back({x + i, y});
            lastDir = 1;
            break;
        case 2:
            posParts.push_back({x, y + i});
            lastDir = 2;
            break;
        case 3:
            posParts.push_back({x - i, y});
            lastDir = 3;
            break;
        default:
            posParts.push_back({x, y - i});
            lastDir = 4;
            break;
        }
    }
}

Snake::Snake(int height, int width, int len, std::list<Snake*> &snakes, std::string keysMove, int color) {
    dir = 1 + (std::rand() % 4);
    growthPoints = 0;
    this->keysMove = keysMove;
    this->color = color;

    bool isGetPos;

    // find free cells for snake
    do {
        int x = std::rand() % width, y = std::rand() % height;
        posParts.clear();
        isGetPos = true;

        for (int i = 0; i < len; ++i) {
            switch (dir) {
            case 1:
                posParts.push_back({x + i, y});
                lastDir = 1;
                break;
            case 2:
                posParts.push_back({x, y + i});
                lastDir = 2;
                break;
            case 3:
                posParts.push_back({x - i, y});
                lastDir = 3;
                break;
            default:
                posParts.push_back({x, y - i});
                lastDir = 4;
                break;
            }
        }

        for (auto it = snakes.begin(); it != snakes.end(); ++it) {
            for (auto snakePosIt = posParts.begin(); snakePosIt != posParts.end(); ++snakePosIt) {
                if ((*it)->isSnakePoint(*snakePosIt)) {
                    isGetPos = false;
                    break;
                }
            }
        }
    } while (!isGetPos);
}

void Snake::setGrowthPoints(int num) {
    growthPoints += num;
}

void Snake::move() {
    posParts.push_front({posParts.front().first + dirVaritions[dir].first, posParts.front().second + dirVaritions[dir].second});
    lastDir = dir;
    if (growthPoints > 0) {
        --growthPoints;
    } else {
        posParts.pop_back();
        growthPoints = 0;
    }
}

bool Snake::frameCollision(int height, int width) {
    int x = posParts.front().first, y = posParts.front().second;
    return (0 > x || x > width) || (0 > y || y > height);
}

bool Snake::selfCollision() {
    auto headIt = posParts.begin();
    for (auto tailIt = ++posParts.begin(); tailIt != posParts.end(); ++tailIt) {
        if (*headIt == *tailIt) 
            return true;
    }
    return false;
}

bool Snake::snakesCollision(const Snake *snake) {
    auto headIt = posParts.begin();

    if (snake == this) {
        return selfCollision();
    }

    for (auto snakeIt = snake->posParts.begin(); snakeIt != posParts.end(); ++snakeIt) {
        if (*headIt == *snakeIt) 
            return true;
    }
    return false;
}

bool Snake::isSnakePoint(point pos) {
    for (auto snakeIt = posParts.begin(); snakeIt != posParts.end(); ++snakeIt) {
        if (*snakeIt == pos) 
            return true;
    }
    return false;
}

int Snake::getColor() {
    return color;
}

std::string Snake::getKeys() {
    return keysMove;
}

void Snake::eatRabbits(std::list<Rabbit*> &rabbits) {
    auto snakeHeadIt = posParts.begin();
    auto rabbitIt = rabbits.begin();
    while (rabbitIt != rabbits.end()) {
        if ((*rabbitIt)->getPos() == *snakeHeadIt) {
            setGrowthPoints((*rabbitIt)->getScores());
            rabbitIt = rabbits.erase(rabbitIt);
        } else {
            ++rabbitIt;
        }
    }
}

// 1 - UP; 2 - LEFT; 3 - DOWN; 4 - RIGHT
void Snake::changeDirection(int c) {
    if (c == keysMove[0] && lastDir != 4) {
        dir = 2;
    } else if (c == keysMove[1] && lastDir != 3) {
        dir = 1;
    } else if (c == keysMove[2] && lastDir != 2) {
        dir = 4;
    } else if (c == keysMove[3] && lastDir != 1) {
        dir = 3;
    }
}


Model::Model(int height, int width, std::string keysMove, int rabbitsCount) {
    this->height = height;
    this->width = width;
    this->rabbitsCount = rabbitsCount;

    std::srand((unsigned int) time(nullptr));

    Snake *s = new Snake(height, width, 3, snakes, keysMove, 1);
    snakes.push_back(s);

    for (int i = 0; i < rabbitsCount; ++i) {
        Rabbit *r = new Rabbit(height, width, snakes, rabbits, 1);
        rabbits.push_back(r);
    }
}

void Model::makeNextStep() {
    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        (*it)->move();
    }

    // check snakes collisions
    auto snakeIt = snakes.begin();
    bool isSnakeDeleted = false;
    while (snakeIt != snakes.end()) {
        for (auto otherSnakeIt = snakes.begin(); otherSnakeIt != snakes.end(); ++otherSnakeIt) {
            if ((*snakeIt)->snakesCollision((*otherSnakeIt))) {
                snakeIt = snakes.erase(snakeIt);
                isSnakeDeleted = true;
                break;
            } 
        }
        if (!isSnakeDeleted) {
            ++snakeIt;
        }
        isSnakeDeleted = false;
    }

    // check frames collisions
    snakeIt = snakes.begin();
    while (snakeIt != snakes.end()) {
        if ((*snakeIt)->frameCollision(height, width)) {
            snakeIt = snakes.erase(snakeIt);
        } else {
            ++snakeIt;
        }
    }

    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        (*it)->eatRabbits(rabbits);
    }

    for (int i = rabbits.size(); i < rabbitsCount; ++i) {
        Rabbit *r = new Rabbit(height, width, snakes, rabbits, 1);
        rabbits.push_back(r);
    }
}

void Model::getRabbitsData(std::list<point> &data) {
    for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        data.push_back((*it)->getPos());
    }
}

void Model::getSnakesData(std::list<snakeData> &data) {
    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        data.push_back({(*it)->getColor(), (*it)->posParts});
    }
}

void Model::setSnakeKeys(Controller &keyboard) {
    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        auto quitFunc = std::bind(&Snake::changeDirection, *it, std::placeholders::_1);
        keyboard.setKeys(quitFunc, (*it)->getKeys());
    }
    
}

size_frame Model::getSize() {
    return {height, width};
}

Model::~Model() {
    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        delete (*it);
    }

    for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        delete (*it);
    }
}
