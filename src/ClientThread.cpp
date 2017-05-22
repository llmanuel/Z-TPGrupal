#include <iostream>
#include "ClientThread.h"

void ClientThread::run() {
    while(true){
        mapMonitor.initializeMap(20, 20);
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 20; j++){
                mapMonitor.setCell(i, j, "Tierra");
            }
        }
        std::cout<<"hi"<<std::endl;
    }
}

ClientThread::ClientThread(PlayersMonitor &playerMonitor,
                           BuildingsMonitor &buildingsMonitor,
                           MapMonitor &mapMonitor) :
        playersMonitor(playerMonitor),
        buildingsMonitor(buildingsMonitor),
        mapMonitor(mapMonitor){
}