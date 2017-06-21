//
// Created by rodian on 18/05/17.
//

#include "map.h"

Map::Map(int x, int y, int width, int height,
   std::vector<std::vector<Cell>>& terrain_map,
         std::vector<Occupant*>* occupants,
         std::string& xml) : map_size(x,y,width,height),
    terrain_map(terrain_map), all_occupants(occupants), xml(xml) {
    this->buildTypeMap();
}

//void Map::addOccupant(Occupant *new_occupant) {
//    all_occupants.push_back(new_occupant);
//}

double Map::getTerrainFactorOn(int x, int y) {
    int w_cell = terrain_map[0][0].getWidthOfCell();
    int x_pos = x / w_cell;
    int y_pos = y / w_cell;

    return terrain_map[x_pos][y_pos].getMovementFactor();
}

std::string Map::getTerrainType(int x, int y) {
    int w_cell = terrain_map[0][0].getWidthOfCell();
    int x_pos = x / w_cell;
    int y_pos = y / w_cell;

    return terrain_map[x_pos][y_pos].getTerrainType();
}

bool Map::areThisPointsEmpty(Size &size, int id) {
    bool no_collision = true;
    std::vector<Occupant*>::iterator it = all_occupants->begin();
    for(;it != all_occupants->end();){
        // if Occupant is dead remove it from vector
        if(!(*it)->areYouAlive()) {
            //erase it from map
            it = all_occupants->erase(it);
        } else {
            //make checks
            if((*it)->getId() != id
               && (*it)->isThereACollision(size) &&
                    (*it)->getType() != "Bridge") {
                no_collision = false;
                break;
            }
            ++it;
        }
    }
    return no_collision;
}

bool Map::areThisPointsEmpty(Size &size, Occupant &shooter, Occupant &occupant) {
    bool no_collision = true;
    std::vector<Occupant*>::iterator it = all_occupants->begin();
    for(;it != all_occupants->end();){
        // if Occupant is dead remove it from vector
        if(!(*it)->areYouAlive()) {
            //erase it from map
            it = all_occupants->erase(it);
        } else {
            //make checks
            if((*it)->getId() != occupant.getId() &&
                    (*it)->isThereACollision(size)
                    && (*it)->getType() != "Bridge"  &&
                    (*it)->getId() != shooter.getId()) {
                no_collision = false;
                break;
            }
            ++it;
        }
    }
    return no_collision;
}

int Map::getWidth() {
    return map_size.getWidth();
}

int Map::getHeigth() {
    return map_size.getHeight();
}

bool Map::canIWalkToThisPosition(Size &other_size, int id) {
    bool you_can = true;

    // if the object is stepping out of the map
    if (map_size.areYouHalfOutSide(other_size))
        you_can = false;
    // if the object is stepping into lava
    if (isThereLava(other_size)) {
        you_can = false;
        if (thereIsABridge(other_size))
            you_can = true;
    }
    if (!areThisPointsEmpty(other_size, id)) {
        you_can = false;
    }

    return (you_can);
}

bool Map::canBulletWalkToThisPosition(Size &other_size, Occupant &shooter,
                                                        Occupant &target) {
    bool you_can = true;

    // if the object is stepping out of the map
    if (map_size.areYouHalfOutSide(other_size))
        you_can = false;

    if (!areThisPointsEmpty(other_size,shooter,target)) {
        you_can = false;
    }

    return (you_can);
}

bool Map::doesThisPositionExist(int x, int y) {
    return map_size.areYouOnThisPoint(x,y);
}

bool Map::isThereLava(Size& other_size) {
    int x_max, x_min, y_max, y_min;
    other_size.calculateMaxAndMinForX(x_max, x_min);
    other_size.calculateMaxAndMinForY(y_max, y_min);

    int w_cell = terrain_map[0][0].getWidthOfCell();
    // Check if any of the corners are stepping into lava
    for (int y = y_min; y <= y_max; ++y) {
        for (int x = x_min; x <= x_max; ++x) {
            if (doesThisPositionExist(x,y)) {
                // Calculate the cell that holds this position
                int x_pos = x / w_cell;
                int y_pos = y / w_cell;

                if (terrain_map[x_pos][y_pos].getTerrainType() == "Lava") {
                    return terrain_map[x_pos][y_pos].isThereACollision(
                            other_size);
                }
            }
        }
    }

    return false;
}

bool Map::thereIsABridge(Size& other_size) {
    bool bridge = false;
    std::vector<Occupant*>::iterator it = all_occupants->begin();
    for(;it != all_occupants->end();){
        // if Occupant is dead remove it from vector
        if(!(*it)->areYouAlive()) {
            //erase it from map
            it = all_occupants->erase(it);
        } else {
            //make checks
            if((*it)->isThereACollision(other_size) &&
                    (*it)->getType() == "Bridge") {
                bridge = true;
                break;
            }
            ++it;
        }
    }
    return bridge;
}

std::string &Map::get_map() {
    return xml;
}

void Map::getAClosePlaceNextTo(Size& u_size, Size& fac_size) {
    bool have_position = false;
    Position fac_pos = fac_size.getPosition();
    int i = 0;
    while (!have_position) {
        int tmp_x = u_size.getWidth() + fac_size.getWidth() + fac_pos.getX()
                    + i;
        int tmp_y = u_size.getHeight() + fac_size.getHeight() + fac_pos.getY()
                    + i;
        u_size.moveTo(tmp_x,tmp_y);
        if (this->canIWalkToThisPosition(u_size, 0)) {
            have_position = true;
        }
        if (!have_position) {
            tmp_x = fac_pos.getX() - u_size.getWidth() - fac_size.getWidth()
                    - i;
            tmp_y = fac_pos.getY() - u_size.getHeight() - fac_size.getHeight()
                    - i;
            u_size.moveTo(tmp_x, tmp_y);
            if (this->canIWalkToThisPosition(u_size, 0)) {
                have_position = true;
            }
        }
        if (!have_position) {
            tmp_x = fac_pos.getX() - u_size.getWidth() - fac_size.getWidth()
                    - i;
            tmp_y = fac_pos.getY() + u_size.getHeight() + fac_size.getHeight()
                    + i;
            u_size.moveTo(tmp_x, tmp_y);
            if (this->canIWalkToThisPosition(u_size, 0)) {
                have_position = true;
            }
        }
        if (!have_position) {
            tmp_x = fac_pos.getX() + u_size.getWidth() + fac_size.getWidth()
                    + i;
            tmp_y = fac_pos.getY() - u_size.getHeight() - fac_size.getHeight()
                    - i;
            u_size.moveTo(tmp_x, tmp_y);
            if (this->canIWalkToThisPosition(u_size, 0)) {
                have_position = true;
            }
        }
        ++i;
    }
}

std::vector<Occupant *> &Map::getOccupants() {
    return *this->all_occupants;
}

void Map::updateOccupants(std::vector<Occupant *> *all_occupants) {
    this->all_occupants = all_occupants;
}

Occupant* Map::checkForEnemiesOn(Size &range, Occupant& unit, Occupant& enemy) {
    std::vector<Occupant*>::iterator it = all_occupants->begin();
    for(;it != all_occupants->end();){
        // if Unit is dead remove it from vector
        if(!(*it)->areYouAlive()) {
            //erase it from map
            it = all_occupants->erase(it);
        } else {
            //make checks
            if((*it)->getId() != unit.getId() && (*it)->isThereACollision(range)
               && types[(*it)->getType()] == "Unit" &&
                    (*it)->getTeam() != "Neutral"
               && unit.getTeam() != (*it)->getTeam()) {
                return (*it);
            }
            ++it;
        }
    }
    return &unit;
}

void Map::buildTypeMap() {
    types.insert(std::pair<std::string,std::string>("Fort","Building"));
    types.insert(std::pair<std::string,std::string>
                         ("vehiculeFactory","Building"));
    types.insert(std::pair<std::string,std::string>("robotFactory","Building"));
    types.insert(std::pair<std::string,std::string>("Factory","Building"));
    types.insert(std::pair<std::string,std::string>("Rock","Nature"));
    types.insert(std::pair<std::string,std::string>("iceblock","Nature"));
    types.insert(std::pair<std::string,std::string>("grunt","Unit"));
    types.insert(std::pair<std::string,std::string>("Psycho","Unit"));
    types.insert(std::pair<std::string,std::string>("Tough","Unit"));
    types.insert(std::pair<std::string,std::string>("Pyro","Unit"));
    types.insert(std::pair<std::string,std::string>("Sniper","Unit"));
    types.insert(std::pair<std::string,std::string>("laser","Unit"));
    types.insert(std::pair<std::string,std::string>("jeep","Unit"));
    types.insert(std::pair<std::string,std::string>("MediumTank","Unit"));
    types.insert(std::pair<std::string,std::string>("LightTank","Unit"));
    types.insert(std::pair<std::string,std::string>("HeavyTank","Unit"));
    types.insert(std::pair<std::string,std::string>("MML","Unit"));
}




