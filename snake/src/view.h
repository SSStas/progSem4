#pragma once

#include <utility>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


using point = std::pair<int, int>;

class View {
    protected:
        int x, y;

    public:
        View(): x(0), y(0) {};
        ~View() {};

        virtual void draw() = 0;
        virtual void clean() = 0;
        //virtual size GetFrameSize() const = 0;
};

class TextView: public View {
    public:
        TextView();
        ~TextView() {};

        void draw();
        void clean();
        point getsz();
        void putString(point p, char *str);
        void putSymbol(point p, char sym);
        void horiontalLine(int n, char sym);
        void verticalLine(int n, char sym);
};


class GuiView: public View {
    public:
        GuiView() {};
        ~GuiView() {};

        void draw();
        void clean();
};
