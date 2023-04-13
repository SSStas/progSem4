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
    printf("\e[8;%d;%dt", s.first + 2, s.second + 2);
    point temp = getsz();
    width = temp.first;
    height = temp.second;
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
    uploadData upData;
    deletedData delData;

    while(!isFinished) {
        spendTime = keyboard.pollKeyboard();
        model.makeNextStep(upData, delData);

        cleanObj(delData, 2, 2);
        delData.clear();

        drawObj(upData, 2, 2);
        upData.clear();

        drawFrame();

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

void TextView::cleanObj(deletedData &data, int moveX, int moveY) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        putSymbol({it->first + moveX, it->second + moveY}, ' ');
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

void TextView::drawObj(uploadData &data, int moveX, int moveY) {
    char c;
    for (auto it = data.begin(); it != data.end(); ++it) {
        switch (it->first) {
        case RABBIT:
            c ='@';
            break;
        case SNAKE1:
            c ='*';
            break;
        case SNAKE2:
            c ='#';
            break;
        case SNAKE3:
            c ='s';
            break;
        default:
            c = 'X';
            break;
        }
        putSymbol({(it->second).first + moveX, (it->second).second + moveY}, c);
    }
}

TextView::~TextView() {
    enableScrolling();
    printf("\e[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &terminalState);
}
