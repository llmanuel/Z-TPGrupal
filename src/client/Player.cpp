#include "Player.h"
#include <vector>

int Player::getID() {
    return id;
}

void Player::addUnit(Unit &unit) {
    units.push_back(unit);
}

bool Player::removeUnit(int id) {
    for (auto unit = units.begin(); unit != units.end(); ++unit) {
        if (unit->get_ID() == id) {
            units.erase(unit);
            return true;
        }
    }
    return false;
}

bool Player::update_position(int id, int x, int y) {
    for (auto unit = units.begin(); unit != units.end(); ++unit) {
        if (unit->get_ID() == id) {
            unit->update_position(x, y);
            return true;
        }
    }
    return false;
}

void Player::markAsSelectedInRange(bool &unitsSelected,
                                   gdouble xStartCoordinate,
                                   gdouble yStartCoordinate,
                                   gdouble xFinishCoordinate,
                                   gdouble yFinishCoordinate) {
    for (Unit& unit : units){
        unit.markAsSelectedInRange(unitsSelected, xStartCoordinate,
                                   yStartCoordinate, xFinishCoordinate,
                                   yFinishCoordinate);
    }
}

std::vector<Unit>
Player::getUnitsToDraw(unsigned int minX, unsigned int maxX, unsigned int minY,
                       unsigned int maxY) {
    std::vector <Unit> returnVector;
    for (Unit& unit : units){
        if (unit.getXCoordinate() >= minX and
                unit.getXCoordinate() <= maxX and
                unit.getYCoordinate() >= minY and
                unit.getYCoordinate() <= maxY){
            returnVector.emplace_back(unit);
        }
    }
    return returnVector;
}