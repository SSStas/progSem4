#include <iostream>
#include <string>
#include "view.h"
#include "viewCreator.h"


void TextView::disableScrolling() {
    printf("\033[?1049h");
}

void TextView::enableScrolling() {
    printf("\033[?1049l");
}

void TextView::onStart(size_frame s) {
    isFinished = false;
    printf("\e[8;%d;%dt", s.first + 1, s.second + 1);
    printf("\e[H\e[2J");
    disableScrolling();
}

void TextView::finishTextView(int a) {
    isFinished = true;
}

void TextView::run(Model &model) {
    auto quitFunc = std::bind(&TextView::finishTextView, this, std::placeholders::_1);
    keyboard.setKey(quitFunc, 'q');
    model.setSnakeKeys(keyboard);

    onStart(model.getSize());

    int spendTime = 0;
    std::list<point> rabbitsData;
    std::list<snakeData> snakesData;

    while(!isFinished) {
        spendTime = keyboard.pollKeyboard();
        model.makeNextStep();

        cleanObj(rabbitsData, snakesData, 1, 1);
        rabbitsData.clear();
        snakesData.clear();
        model.getRabbitsData(rabbitsData);
        model.getSnakesData(snakesData);

        drawFrame();
        drawRabbits(rabbitsData, 1, 1);
        drawSnakes(snakesData, 1, 1);

        usleep(100000 - spendTime);
    }

    enableScrolling();
}

void TextView::drawFrame() {
    clean();
    horiontalLine(1, 1, width + 1, '-', '+');
    horiontalLine(height, 1, width + 1, '-', '+');
    verticalLine(1, 1, height + 1, '|', '+');
    verticalLine(1, width, height + 1, '|', '+');

    fflush(stdout);
}

void TextView::clean() {
    puts("\e[H");
    printf("\033[1;1H");
}

void TextView::cleanObj(std::list<point> &rabbitsData, std::list<snakeData> &snakesData, int moveX, int moveY) {
    for (auto it = rabbitsData.begin(); it != rabbitsData.end(); ++it) {
        putSymbol({it->first + moveX, it->second + moveY}, ' ');
    }

    for (auto it = snakesData.begin(); it != snakesData.end(); ++it) {
        for (auto snakeIt = it->second.begin(); snakeIt != it->second.end(); ++snakeIt) {
            putSymbol({snakeIt->first + moveX, snakeIt->second + moveY}, ' ');
        }
    }

    clean();
}

void TextView::putString(point p, char *str) {
    printf("\e[%d;%dH", p.second, p.first);
    puts(str);
    puts("\e[H");
    printf("\033[1;1H");
}

void TextView::putSymbol(point p, char sym) {
    printf("\e[%d;%dH", p.second, p.first);
    putchar(sym);
    puts("\e[H");
    printf("\033[1;1H");
}

void TextView::verticalLine(int x, int y, int len, char sym, char edges) {
    putSymbol({y, x}, edges);
    for (int i = x + 1; i < len - 1; ++i) {
        putSymbol({y, i}, sym);
    }
    putSymbol({y, len - 1}, edges);
}

void TextView::horiontalLine(int x, int y, int len, char sym, char edges) {
    putSymbol({y, x}, edges);
    for (int i = y + 1; i < len - 1; ++i) {
        putSymbol({i, x}, sym);
    }
    putSymbol({y, len - 1}, edges);
}

point TextView::getsz() {
    struct winsize temp;
    ioctl(0, TIOCGWINSZ, &temp); 
    point sz = {temp.ws_col, temp.ws_row};

    return sz;
}

TextView::TextView() {
    keyboard = Controller();
    point temp = getsz();

    width = temp.first;
    height = temp.second;
    
    tcgetattr(STDIN_FILENO, &terminalState);

    struct termios attrRaw = terminalState;
    cfmakeraw(&attrRaw);
    attrRaw.c_lflag |= ISIG;

    tcsetattr(STDIN_FILENO, TCSANOW, &attrRaw);
}

void TextView::drawRabbits(std::list<point> &rabbitsData, int moveX, int moveY) {
    for (auto it = rabbitsData.begin(); it != rabbitsData.end(); ++it) {
        putSymbol({it->first + moveX, it->second + moveY}, '@');
    }
}

void TextView::drawSnakes(std::list<snakeData> &snakesData, int moveX, int moveY) {
    for (auto it = snakesData.begin(); it != snakesData.end(); ++it) {
        for (auto snakeIt = it->second.begin(); snakeIt != it->second.end(); ++snakeIt) {
            putSymbol({snakeIt->first + moveX, snakeIt->second + moveY}, '*');
        }
    }
}

TextView::~TextView() {
    enableScrolling();
    printf("\e[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &terminalState);
}
