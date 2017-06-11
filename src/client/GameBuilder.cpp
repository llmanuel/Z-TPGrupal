#include <iostream>
#include <string>
#include "GameBuilder.h"
#include "PlayersMonitor.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"


GameBuilder::GameBuilder(PlayersMonitor &monitor,
                         BuildingsMonitor &buildingsMonitor,
                         MapMonitor &mapMonitor,
                         ServerMessenger& messenger) :
        playersMonitor(monitor),
        buildingsMonitor(buildingsMonitor),
        mapMonitor(mapMonitor),
        messenger(messenger){
    //Load the GtkBuilder file and instantiate its widgets:
    refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("Z.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return;
    }

    // Save the widget refs in the class attributes
    refBuilder->get_widget_derived("GameWindow", window);

    window->setResources(&playersMonitor, &buildingsMonitor, &mapMonitor,
                         &messenger);
    refBuilder->get_widget("Portrait", portrait);
    refBuilder->get_widget("SidePanel", panel);
    refBuilder->get_widget("Create", button);
    refBuilder->get_widget_derived("InitialWindow", init_window);
}


GameBuilder::~GameBuilder() {
    if (window) {
        delete window;
    }
}

GameWindow *GameBuilder::get_window() {
    return window;
}

InitialWindow *GameBuilder::get_initial_window() {
    return init_window;
}



