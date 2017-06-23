//
// Created by rodian on 22/05/17.
//

#include <memory>
#include "factory.h"
#define ID 3
Factory::Factory(int id, int life, std::string type, Size position,
                 std::vector<UnitMold> units, std::shared_ptr<Map> map,
                 std::map<std::string, Weapon> &weapons) :
Occupant(id, life,type, position), running(false),time_counter(0), units(units),
map(map), weapons(weapons){
    mold = units.begin();
}

void Factory::build(int& id_counter) {
    if (time_counter == mold->getCreationTime()) {
        Size u_size = mold->getUnitSize();
        Position factory_pos = this->obj_size.getPosition();
        u_size.moveTo(factory_pos.getX(),factory_pos.getY());
        Weapon u_weapon = weapons.at(mold->getTypeOfUnit());

        for (int i = 0; i < mold->getCreationQuantity(); ++i) {
            new_units.push_back(mold->createUnit(
                                             id_counter,u_size,*map,u_weapon));
            ++id_counter;
        }
        this->changed = true;
        time_counter = 0;
    } else if (running && time_counter < mold->getCreationTime()) {
        time_counter += 1 + tech_level;
        this->changed = false;
    }
}

//void Factory::stopBuilding(std::string &player_id) {
//    if (player_id == this->getTeam())
//        this->running = false;
//}

int Factory::getSelectedUnitTime() {
    return mold->getCreationTime();
}

std::string Factory::nextUnit() {
    int i = 0;
    this->running = false;
    while (i == 0 || mold->getTechnologyLevel() > this->tech_level) {
        ++mold;
        if (mold == units.end())
            mold = units.begin();
        ++i;
    }
    return mold->getTypeOfUnit();
}

Occupant *Factory::destroyFactory() {
    // capaz necesite un tipo distinto a Occupant para que no pueda ser
    // destruido ni atacado
//    Occupant* ruins = new Occupant(,1000,"Ruins",this->occ_size);
//    return ruins;
}

void Factory::changeTechLevel(int tech_level) {
    this->tech_level = tech_level;
}

void Factory::startBuilding(std::string &player_id) {
    if (player_id == this->getTeam())
        running = true;
}

int Factory::getCreationSpeed() {
    return ((*mold).getCreationTime() / (1 + tech_level));
}

bool Factory::haveNewUnits() {
    return (!this->new_units.empty());
}

std::vector<Unit*> Factory::getUnits() {
    std::vector<Unit*> tmp = new_units;
    new_units.clear();
    return tmp;
}
