//
// Created by rodian on 29/05/17.
//

#ifndef Z_TPGRUPAL_MENU_H
#define Z_TPGRUPAL_MENU_H


#include <vector>
#include "player.h"
class Player;
class Lobby;

class Menu {
private:
    std::vector<Player*> players;
    std::mutex& m;
    int lobby_counter;
    std::vector<Lobby*> lobbys;
public:
    Menu(std::mutex& m);

    void addPlayer(Messenger* msgr, Menu& menu, std::string player_id);

    void createNewLobby(Player* player);

    std::string getLobbiesInfo();

    void addToLobbie(int id_lobbie, Player& player);

    ~Menu();
};


#endif //Z_TPGRUPAL_MENU_H
