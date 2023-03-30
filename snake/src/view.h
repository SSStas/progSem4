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


using point = std::pair<int, int>;

class View {
    protected:
        int height, width;

    public:
       View(): height(0), width(0) {};

        virtual void run(Controller *keyboard) = 0;
        virtual void draw() = 0;
        virtual void clean() = 0;
        //virtual size GetFrameSize() const = 0;

        virtual ~View() {};
};


class TextView: public View {
    struct termios terminalState;
    struct termios attrRaw;
    bool isFinished = true;

    public:
        TextView();
        
        void run(Controller *keyboard);
        void draw();
        void clean();
        point getsz();
        void onStart();
        void finishTextView(int a);
        void putString(point p, char *str);
        void putSymbol(point p, char sym);
        void horiontalLine(int x, int y, int len, char sym, char edges);
        void verticalLine(int x, int y, int len, char sym, char edges);
        void disableScrolling();
        void enableScrolling();

        ~TextView();
};


class GuiView: public View {
    public:
        GuiView() {};
        
        void run(Controller *keyboard);
        void draw();
        void clean();

        ~GuiView() {};
};
