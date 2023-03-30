#pragma once

#include <unordered_map>
#include <vector>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <functional>


class Controller {
    using event = std::function<void (int)>;

    std::vector<char> keysList;
    std::unordered_map<char, std::vector<event>*> buttons;

    void doEventsOnClick(char c);
    int getTime();

public:
    Controller() {};

    void setKey(event func, char c);
    int pollKeyboard();

    ~Controller() {
        for (auto it = keysList.begin(); it != keysList.end(); ++it)
            delete buttons.find(*it)->second;
    };
};
