#pragma once

#include "view.h"

class ViewCreator {

    static View* objView;

    public:
        static View* get(char *mode = nullptr) {
            if (mode == nullptr || std::string(mode) == "text") {
                objView = new TextView();
            } else if (std::string(mode) == "gui") {
                objView = new GuiView();
            }

            return objView;
        }

};
