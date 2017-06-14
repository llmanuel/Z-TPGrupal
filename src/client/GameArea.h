#ifndef Z_TPGRUPAL_GAMEAREA_H
#define Z_TPGRUPAL_GAMEAREA_H


#include <gtkmm/drawingarea.h>
#include <utility>
#include "PlayersMonitor.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "Camera.h"
#include "enums/FlagEnum.h"
#include "enums/TeamEnum.h"
#include "enums/ActionsEnum.h"
#include "enums/UnitsEnum.h"
#include "enums/BuildingsEnum.h"
#include "enums/RotationsEnum.h"
#include <map>
#include <string>
#include <vector>

class GameArea : public Gtk::DrawingArea{
private:
    /* shared resources */
    PlayersMonitor *playersMonitor;
    BuildingsMonitor *buildingsMonitor;
    MapMonitor *mapMonitor;

    Camera camera;

    /* general resources */
    std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> tiles;

    Glib::RefPtr<Gdk::Pixbuf> someImg;

    /* map holding all flags */
    std::map<FlagEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> flags;

    /* map holding all units imgs */
    std::map<TeamEnum,
            std::map<UnitsEnum,
                    std::map<ActionsEnum,
                            std::map<RotationsEnum,
                                    std::vector<Glib::RefPtr<Gdk::Pixbuf>>>>>>
            unitsAnimations;

    /* BUILDINGS RESOURCES */
    std::map<BuildingsEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> buildings;

    std::map<RotationsEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> jeepTires;

    /* declare counter used to know which of the flag imgs
     * which compose the flag's animation should be showed. This counters are
     * updated every time on_draw() is called.
     * */
    unsigned long flagCounter;
    unsigned short standingRobotCounter;
    unsigned short walkingRobotCounter;
    unsigned short shootingRobotCounter;
    unsigned short jeepCounter;
    unsigned short tireCounter;
    unsigned short tankCounter;
    unsigned short mmlCounter;

    /* DRAWING METHODS */
    void drawBaseMap(const Cairo::RefPtr<Cairo::Context> &cr,
                     std::pair<unsigned int, unsigned int> cameraPosition);

    void drawTileAt(const Cairo::RefPtr<Cairo::Context> &cr,
                    unsigned int xCoordinate, unsigned int yCoordinate,
                    std::string terrainType);

    void drawFlagAnimation(const Cairo::RefPtr<Cairo::Context> &ptr,
                           int xCoordinate, int yCoordinate);

    void displaySomeStaticImg(const Cairo::RefPtr<Cairo::Context> &refPtr,
                              int xCoordinate, int yCoordinate);


    /* Event handling methods */
    bool on_key_press_event(GdkEventKey *event) override;

    bool on_button_press_event(GdkEventButton *event) override;

    bool on_button_release_event(GdkEventButton *event) override;

    /* vars. for event handling */
    gdouble xStartCoordinate;
    gdouble xFinishCoordinate;
    gdouble yStartCoordinate;
    gdouble yFinishCoordinate;
    bool selectionMade;
    /* unitsSelected is true if the players' units are selected. This is used
     * to manage user clicks. */
    bool unitsSelected;

    void makeSelection();

    /* FLAG res loading */
    void loadFlagAnimations();

    /* UNIT FIRE res loading */
    void loadUnitsResources();

    void loadGruntFireAnimations();

    void loadLaserFireAnimations();

    void loadPsychoFireAnimations();

    void loadPyroFireAnimations();

    void loadSniperFireAnimations();

    void loadToughFireAnimations();

    void loadBlueGruntFireAnimations();

    void loadGreenGruntFireAnimations();

    void loadRedGruntFireAnimations();

    void loadYellowGruntFireAnimations();

    void loadBlueLaserFireAnimations();

    void loadGreenLaserFireAnimations();

    void loadRedLaserFireAnimations();

    void loadYellowLaserFireAnimations();

    void loadBluePsychoFireAnimations();

    void loadGreenPsychoFireAnimations();

    void loadRedPsychoFireAnimations();

    void loadYellowPsychoFireAnimations();

    void loadBlueSniperFireAnimations();

    void loadGreenSniperFireAnimations();

    void loadRedSniperFireAnimations();

    void loadYellowSniperFireAnimations();

    void loadBlueToughFireAnimations();

    void loadGreenToughFireAnimations();

    void loadRedToughFireAnimations();

    void loadYellowToughFireAnimations();

    /* UNIT WALK res loading */
    void loadBlueWalkingAnimations();

    void loadGreenWalkingAnimations();

    void loadRedWalkingAnimations();

    void loadYellowWalkingAnimations();

    /* UNIT STAND res loading */
    void loadBlueStandingAnimations();

    void loadGreenStandingAnimations();

    void loadRedStandingAnimations();

    void loadYellowStandingAnimations();

    /* BUILDING res loading */
    void loadBuildingsResources();

    /* VEHICLES res loading */
    void loadTiresAnimations();

    void loadJeepTires();

    void loadNeuterVehiclesAnimations();

    void loadNeuterJeepAnimations();

    void loadBlueVehiclesAnimations();

    void loadGreenVehiclesAnimations();

    void loadRedVehiclesAnimations();

    void loadYellowVehiclesAnimations();

    void loadBlueJeepAnimations();

    void loadBlueLightTankAnimations();

    void loadBlueMediumTankAnimations();

    void loadBlueMMLAnimations();

    void loadBlueHeavyTankAnimations();

    void loadGreenJeepAnimations();

    void loadGreenLightTankAnimations();

    void loadGreenMediumTankAnimations();

    void loadGreenMMLAnimations();

    void loadGreenHeavyTankAnimations();

    void loadRedJeepAnimations();

    void loadRedLightTankAnimations();

    void loadRedMediumTankAnimations();

    void loadRedMMLAnimations();

    void loadRedHeavyTankAnimations();

    void loadYellowJeepAnimations();

    void loadYellowLightTankAnimations();

    void loadYellowMediumTankAnimations();

    void loadYellowMMLAnimations();

    void loadYellowHeavyTankAnimations();

    void drawJeepTires(const Cairo::RefPtr<Cairo::Context> &cr,
                       unsigned int xCoordinate, unsigned int yCoordinate,
                       RotationsEnum rotation);

    void drawUnit(TeamEnum team, UnitsEnum unitType, ActionsEnum actionType,
                  RotationsEnum rotation, unsigned short unitCounter,
                  const Cairo::RefPtr<Cairo::Context> &cr,
                  unsigned int xCoordinate, unsigned int yCoordinate);

    void loadResources();

    /**
     * draws all units that are in camera's scope
     * @param cr receive smart pointer to cairo context
     */
    void drawUnitsInMap(const Cairo::RefPtr<Cairo::Context> &cr);

    /**
     * counters used to know whic img of each animation should be drawn are
     * updated. This method should get called once per frame, otherwise it is
     * not guaranteed that animations will be correctly drawn.
     */
    void updateCounters();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

public:
    virtual ~GameArea();
    GameArea(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& builder);

    /**
     * initialize shared resources.
     */
    void
    setResources(PlayersMonitor *playersMonitor,
                 BuildingsMonitor *buildingsMonitor,
                 MapMonitor *mapMonitor);

    void processSelection();

    void processClickWithUnitsSelected();

    void processClick();
};


#endif //Z_TPGRUPAL_GAMEAREA_H