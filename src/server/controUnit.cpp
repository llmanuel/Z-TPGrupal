//
// Created by rodian on 22/05/17.
//

#include "controUnit.h"
#define WAIT 0.5


ControUnit::ControUnit() : winning(false) {}

void ControUnit::connect(Messenger *new_player) {
    Lock l(m);
    this->players.push_back(new_player);
}

void ControUnit::run() {
    while(!winning) {
        double t3(WAIT);

        auto t1 = std::chrono::high_resolution_clock::now();
        // execute commands
        executeCommands();

        // do stuff
        this->unitsMakeMicroAcction();
        this->checkAllLivingOccupants();
        auto t2 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_span =
             std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        sleepFor(t3 - time_span.count());
        //send update message
    }
    // send victory or defeated message
}

void ControUnit::sleepFor(double msec) {
    std::this_thread::sleep_for(std::chrono::seconds(msec));
}

void ControUnit::unitsMakeMicroAcction() {
    for (auto x: all_units){
        x->makeAction();
    }
}


void ControUnit::checkAllLivingOccupants() {
    for(auto x: all_occupants){
        if(!x->areYouAlive()) {
            //erase it from map
            // if building put ruins
        }

    }
}

void ControUnit::cmdMoveUnit(int id, int x, int y) {
    bool found = false;
    Unit* selected_unit = all_units.front();
    for (auto x: all_units) {
        if (x->getId() == id) {
            selected_unit = x;
            found = true;
            break;
        }
    }

    if (found)
        selected_unit->calculateRoadTo(x, y);
}

void ControUnit::executeCommands() {
    std::vector<Command> commands_copy;
    m.lock();
    for (auto x: *commands) {
        commands_copy.push_back(x);
    }
    commands->empty();
    m.unlock();

    // Execute command
    for (auto cmd: commands_copy) {
        cmd();
    }
}
