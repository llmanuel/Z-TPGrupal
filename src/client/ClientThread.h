#ifndef Z_TPGRUPAL_CLIENTTREAD_H
#define Z_TPGRUPAL_CLIENTTREAD_H

#include <map>
#include <string>
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "ServerMessenger.h"
#include "commands/Command.h"
#include "UnitsMonitor.h"
#include "windows/GameWindow.h"
#include "windows/LobbyWindow.h"
#include "GameBuilder.h"
#include <Thread.h>

class ClientThread : public Thread {
    UnitsMonitor &unitsMonitor;
    BuildingsMonitor &buildingsMonitor;
    MapMonitor &mapMonitor;
    ServerMessenger &messenger;
    GameWindow &window;
    MenuWindow& menu;
    LobbyWindow& lobby;
    bool finished = false; // Flag for finishing execution
    std::map<std::string, Command *> commands;
public:
    ClientThread(UnitsMonitor &unitsMonitor,
                 BuildingsMonitor &buildingsMonitor,
                 MapMonitor &mapMonitor, ServerMessenger &messenger,
                 GameBuilder& builder);

    virtual void run();

    ~ClientThread();

    /* Finish the thread's execution */
    void finish();
private:
    /* Loads commands */
    void initCommands();

    /** Main thread loop, receives commands from the server, parses them and
     * executes them */
    void loop();

    /* Parses a command string and executes it */
    void parse(std::string &s);


};


#endif //Z_TPGRUPAL_CLIENTTREAD_H
