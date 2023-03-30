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

void TextView::onStart() {
    isFinished = false;
    printf("\e[H\e[2J");
    disableScrolling();
}

void TextView::finishTextView(int a) {
    isFinished = true;
}

void TextView::run(Controller *keyboard) {
    auto quitFunc = std::bind(&TextView::finishTextView, this, std::placeholders::_1);
    keyboard->setKey(quitFunc, 'q');

    onStart();

    while(!isFinished) {
        keyboard->pollKeyboard();
        draw();

        usleep(50000 * 4);
    }

    enableScrolling();
}

void TextView::draw() {
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
    point temp = getsz();

    width = temp.first;
    height = temp.second;

    tcgetattr(STDIN_FILENO, &terminalState);
    tcgetattr(STDIN_FILENO, &attrRaw);

    cfmakeraw(&attrRaw);
    attrRaw.c_lflag |= ISIG;

    tcsetattr(STDIN_FILENO, TCSANOW, &attrRaw);
}

TextView::~TextView() {
    enableScrolling();
    printf("\e[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &terminalState);
}
