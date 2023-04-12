#pragma once

#include <utility>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include "controller.h"
#include "model.h"


using point = std::pair<int, int>;

class View {
    protected:
        int height, width;

    public:
       View(): height(0), width(0) {};

        virtual void run(Model &model) = 0;
        virtual void drawFrame() = 0;
        virtual void clean() = 0;

        virtual ~View() {};
};


class TextView: public View {
    struct termios terminalState;
    Controller keyboard;
    bool isFinished = true;

    public:
        TextView();
        
        void run(Model &model);
        void drawFrame();
        void clean();
        void cleanObj(std::list<point> &rabbitsData, std::list<snakeData> &snakesData, int moveX, int moveY);
        point getsz();
        void onStart(size_frame s);
        void finishTextView(int a);
        void putString(point p, char *str);
        void putSymbol(point p, char sym);
        void horiontalLine(int x, int y, int len, char sym, char edges);
        void verticalLine(int x, int y, int len, char sym, char edges);
        void disableScrolling();
        void enableScrolling();
        void drawRabbits(std::list<point> &rabbitsData, int moveX, int moveY);
        void drawSnakes(std::list<snakeData> &snakesData, int moveX, int moveY);

        ~TextView();
};


class GuiView: public View {
    public:
        GuiView() {};
        
        void run(Model &model);
        void drawFrame();
        void clean();

        ~GuiView() {};
};
