#include <Lock.h>
#include <iostream>
#include "UnitsMonitor.h"
#include <vector>


UnitsMonitor::UnitsMonitor(std::vector<Unit> &units) : units(units) {
}

void UnitsMonitor::addUnit(Unit &unit) {
    Lock l(m);
    units.push_back(unit);
}

void UnitsMonitor::removeUnit(int id) {
    Lock l(m);
    for (auto unit = units.begin(); unit != units.end(); ++unit) {
        if (unit->get_ID() == id) {
            units.erase(unit);
        }
    }
}

void UnitsMonitor::update_position(int unit_id, int x, int y) {
    Lock l(m);
    for (auto unit = units.begin(); unit != units.end(); ++unit) {
        if (unit->get_ID() == unit_id) {
            unit->update_position(x, y);
        }
    }
//    std::cerr << "update_position: Invalid unit ID: " << unit_id << std::endl;
}

std::vector<Unit>
UnitsMonitor::getUnitsToDraw(unsigned int minX, unsigned int maxX,
                             unsigned int minY, unsigned int maxY) {
    Lock l(m);
    std::vector <Unit> returnVector;

    for (Unit &unit : units){
        if (unit.getXCoordinate() >= minX and
            unit.getXCoordinate() <= maxX and
            unit.getYCoordinate() >= minY and
            unit.getYCoordinate() <= maxY){
            returnVector.emplace_back(unit);
        }
    }
    return returnVector;
}

void
UnitsMonitor::markAsSelectedInRange(bool &unitsSelected,
                                    gdouble xStartCoordinate,
                                    gdouble yStartCoordinate,
                                    gdouble xFinishCoordinate,
                                    gdouble yFinishCoordinate) {
    Lock l(m);
    for (Unit &unit : units){
        unit.markAsSelectedInRange(unitsSelected, xStartCoordinate,
                                   yStartCoordinate, xFinishCoordinate,
                                   yFinishCoordinate);
    }
}

std::vector<Unit> UnitsMonitor::getSelectedUnits() {
    std::vector<Unit> units;
    for (Unit& unit : this->units) {
        if (unit.is_selected()) {
            units.push_back(unit);
        }
    }
    return units;
}