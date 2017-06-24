#include "Game.h"
#include "ClientThread.h"

void Game::start_game(const std::vector<std::string> &names) {
    game->update_players(names);
    game->update_name(me);
    // Start up the game
    game->setResources(&units_monitor, &buildingsMonitor,
                          &mapMonitor, &messenger, me);
    auto app = Gtk::Application::create();
    app->run(*game);
}

Game::Game(GameBuilder &builder, ServerMessenger &server_messenger,
           const std::string& player_name) :
    messenger(server_messenger),
    me(player_name),
    menu(builder.get_menu_window()),
    lobby(builder.get_lobby_window()),
    game(builder.get_window())
{
    // Start thread that handles server communication
    ClientThread clientThread(units_monitor, buildingsMonitor,
                              mapMonitor, messenger, builder);
    clientThread.start();

    start_menu();

    if (menu->joined_succesfully()) {
        start_lobby();
        if (lobby->game_started()) {
            std::vector<std::string> names = lobby->get_player_names();
            clientThread.update_player_names(names);
            start_game(names);
        }
    }

    bool winner = clientThread.is_winner();
    bool loser = clientThread.is_loser();
    results_screen(winner, loser);


    /* once graphics join (window closes), we kill client thread */
    clientThread.finish();
    clientThread.join();
}

void Game::start_lobby() const {
    lobby->set_messenger(messenger);
    auto app = Gtk::Application::create();
    app->run(*lobby);
}

void Game::start_menu() {
    menu->load_messenger(&messenger);
    messenger.send("lobbyinfo");
    auto app = Gtk::Application::create();
    app->run(*menu);
}

void Game::results_screen(bool winner, bool loser) {
    if (!winner && !loser) { // Played closed the window before game was over
        play_again = false;
        return;
    } else if (winner) {
        result->display_win_screen();
    } else {
        result->display_lose_screen();
    }

    auto app = Gtk::Application::create();
    app->run(*result);
    play_again = result->go_back_to_menu();
}

bool Game::get_play_again_status() {
    return play_again;
}
