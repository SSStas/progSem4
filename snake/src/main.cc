#include <iostream>
#include <string>
#include <unistd.h>
#include "viewCreator.h"
#include "view.h"
#include "controller.h"


View* ViewCreator::objView = nullptr;

int main(int argc, char **argv) {
    View *view = nullptr;

    if (argc == 1) {
        view = ViewCreator::get();
    } else if (argc > 1) {
        view = ViewCreator::get(argv[1]);
    } 
    
    if (view == nullptr) {
        return -1;
    }

    Controller keyboard = Controller();

    view->run(&keyboard);

    delete view;
    
    return 0;
}
