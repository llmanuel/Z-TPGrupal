#include <iostream>
#include "Update.h"

Update::Update() {
}

void Update::execute(const std::vector<std::string> &args) {
    for (const std::string &arg : args) {
        std::cout << arg << std::endl;
    }
}
