#include <iostream>
#include <string>
#include "view.h"
#include "viewCreator.h"


void GuiView::run(Model &model) { 
    std::cout << "GuiView::run" << std::endl; 
}

void GuiView::drawFrame() { 
    std::cout << "GuiView::drawFrame" << std::endl; 
}

void GuiView::clean() { 
    std::cout << "GuiView::clean" << std::endl; 
}
