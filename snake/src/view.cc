#include <iostream>
#include <string>
#include "view.h"
#include "viewCreator.h"


View* ViewCreator::objView = nullptr;

//x вниз y вправо
void TextView::draw()
{
    std::cout << "Hello, it's text\n";

    printf("x = %d y = %d \n", x, y);

    clean();
    horiontalLine(1, '#');
    verticalLine(1, '#');
    verticalLine(x, '#');
    horiontalLine(y, '#');

    fflush(stdout);
}

void TextView::clean()
{
    puts("\e[H");
    puts("\e[2J");
}

void TextView::putString(point p, char *str)
{
    printf("\e[%d;%dH", p.second, p.first);
    puts(str);
    puts("\e[H");
}

void TextView::putSymbol(point p, char sym)
{
    printf("\e[%d;%dH", p.second, p.first);
    putchar(sym);
    puts("\e[H");
}

void TextView::verticalLine(int n, char sym)
{
    for (int i = 0; i < y; ++i) {
        putSymbol({n, i}, sym);
    }
}

void TextView::horiontalLine(int n, char sym)
{
    for (int i = 0; i < x; ++i) {
        putSymbol({i, n}, sym);
    }
}

point TextView::getsz()
{
    struct winsize temp;
    ioctl(0, TIOCGWINSZ, &temp); 
    point sz = {temp.ws_col, temp.ws_row};

    return sz;
}

TextView::TextView()
{
    point temp = getsz();

    x = temp.first;
    y = temp.second;
}



void GuiView::draw() { 
    std::cout << "GuiView::draw" << std::endl; 
}

void GuiView::clean() {
    std::cout << "GuiView::clean" << std::endl; 
}
