#include <iostream>
#include <string>
#include <unistd.h>
#include "viewCreator.h"
#include "view.h"


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

    while(1) {
        view->draw();
        usleep(1500000);
    }
    
    return 0;
}
