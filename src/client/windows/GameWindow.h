#ifndef Z_TPGRUPAL_GAMEWINDOW_H
#define Z_TPGRUPAL_GAMEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/applicationwindow.h>
#include "../GameArea.h"
#include "../BuildingsMonitor.h"
#include "../MapMonitor.h"
#include "../ServerMessenger.h"
#include "../panels/UnitPanel.h"
#include "../panels/BuildingPanel.h"

class GameWindow : public Gtk::ApplicationWindow {
    GameArea *gameArea;
    Gtk::Box *panel;
    UnitPanel *unit_panel;
    BuildingPanel *building_panel;
    Gtk::Box *group_panel;
    Gtk::Label *panelLabel;

    UnitsMonitor *unitsMonitor;
    BuildingsMonitor *buildingsMonitor;
    MapMonitor *mapMonitor;
    ServerMessenger *messenger;

    Unit selected_unit;
    Building selected_building;

    bool unit_selection;
    bool building_selection;

    std::string me;
public:
    GameWindow(BaseObjectType *cobject,
               const Glib::RefPtr<Gtk::Builder> &builder);

    virtual ~GameWindow();

    /**
     * Saves resources' monitors and passes them to the gameArea.
     */
    void
    setResources(UnitsMonitor *unitsMonitor, BuildingsMonitor *buildingsMonitor,
                 MapMonitor *mapMonitor, ServerMessenger *messenger,
                 const std::string &owner);

    void setMapData();
    void factory_change_unit(std::string &path);

    void update_factory_panel(const std::string& type, int fire_rate, int hp);
    void update_factory_timer(int minutes, int seconds);

    void update_name(const std::string& name);

protected:
    bool onTimeout();

private:
    void update_side_panels();
    // Functions to change the window's side panel
    bool change_view_to_unit();

    bool change_view_to_building();

    bool change_view_to_unit_group();

    bool on_button_release_event(GdkEventButton *event);

    void factory_next();

    void factory_create_unit();

    void process_attack();

    bool on_key_press_event(GdkEventKey *event) override;

    void remove_side_panel();

    void factory_prev();

    void process_movement() const;
};

#endif //Z_TPGRUPAL_GAMEWINDOW_H
