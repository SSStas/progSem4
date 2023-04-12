#include "controller.h"


void Controller::doEventsOnClick(char c) {
    auto funcIt = buttons.find(c);

    if(funcIt != buttons.end()) {
        for(auto it = funcIt->second->begin(); it != funcIt->second->end(); ++it) {
            event temp = *it;
            temp(c);
        }
        
    }
}

int Controller::getTime() {
    struct timeval tp;

    gettimeofday(&tp, NULL);

    return tp.tv_sec * 1000000 + tp.tv_usec;
}

void Controller::setKey(event func, char c) {
    auto it = buttons.find(c);

    if (it == buttons.end()) {
        keysList.push_back(c);
        std::vector<event> *tempList = new std::vector<event>;
        tempList->push_back(func);
        buttons[c] = tempList;
    } else {
        it->second->push_back(func);
    }
}

void Controller::setKeys(event func, std::string s) {
    for (const auto &c: s) {
        setKey(func, c);
    }
}

int Controller::pollKeyboard() {
    char c[4097];
    struct pollfd keyb = {0, POLLIN, 0};
    int bytesRead = 0;
    
    int time = getTime();

    while (poll(&keyb, 1, 0) == 1) {
        bytesRead = read(0, c, 4096);

        for(int i = 0; i < bytesRead; ++i) {
            doEventsOnClick(c[i]);
        }
    }

    return time - getTime();
}
