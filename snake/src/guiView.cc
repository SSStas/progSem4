#include <iostream>
#include <string>
#include "view.h"
#include "viewCreator.h"


void GuiView::run(Controller *keyboard) { 
    std::cout << "GuiView::run" << std::endl; 
}

void GuiView::draw() { 
    std::cout << "GuiView::draw" << std::endl; 
}

void GuiView::clean() {
    std::cout << "GuiView::clean" << std::endl; 
}
