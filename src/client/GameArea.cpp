#include <gtkmm/builder.h>
#include <utility>
#include <gdkmm.h>
#include <iostream>
#include "GameArea.h"
#include <string>


#define TILESIZE 16    //tile width in pixels
#define NUMBER_OF_TILES_TO_SHOW 10

GameArea::GameArea(BaseObjectType *cobject,
                   const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::DrawingArea(cobject),
        flagCounter(0),
        playersMonitor(nullptr),
        buildingsMonitor(nullptr),
        mapMonitor(nullptr),
        /* camera is initialized with size 0,0 because we dont
         * have this data yet */
        camera(TILESIZE, 0, 0, NUMBER_OF_TILES_TO_SHOW) {
    /* load blue flag imgs */
    blueFlagVector.emplace_back(Gdk::Pixbuf::create_from_file(
            "res/assets/buildings/fort/flag_blue_n00.png"));

    blueFlagVector.emplace_back(Gdk::Pixbuf::create_from_file(
            "res/assets/buildings/fort/flag_blue_n01.png"));

    blueFlagVector.emplace_back(Gdk::Pixbuf::create_from_file(
            "res/assets/buildings/fort/flag_blue_n02.png"));

    blueFlagVector.emplace_back(Gdk::Pixbuf::create_from_file(
            "res/assets/buildings/fort/flag_blue_n03.png"));

    /* load some img */
    someImg = Gdk::Pixbuf::create_from_file("res/portraits/grunt.png");

    /* Load tiles */
    tiles["Tierra"] = Gdk::Pixbuf::create_from_file
            ("res/assets/tiles/tierra.png");
    tiles["Agua"] = Gdk::Pixbuf::create_from_file
            ("res/assets/tiles/agua.png");
    tiles["Lava"] = Gdk::Pixbuf::create_from_file("res/assets/tiles/lava.png");
}

GameArea::~GameArea() { }

bool GameArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    drawBaseMap(cr, camera.getPosition());
    drawFlagAnimation(cr, 500, 500);
    return true;
}

void GameArea::drawBaseMap(const Cairo::RefPtr<Cairo::Context> &cr,
                           std::pair<unsigned int, unsigned int>
                           cameraPosition) {
    /* cameraPosition is given in pixels.
     * i,j indicate TILES. */
    for (unsigned int i = cameraPosition.first/TILESIZE-
            NUMBER_OF_TILES_TO_SHOW/2;
         i < cameraPosition.first/TILESIZE+NUMBER_OF_TILES_TO_SHOW/2; ++i){
        for (unsigned int j = cameraPosition.second/TILESIZE-
                NUMBER_OF_TILES_TO_SHOW/2;
             j < cameraPosition.second/TILESIZE+NUMBER_OF_TILES_TO_SHOW/2; ++j){
            drawTileAt(cr, i, j, mapMonitor->getTerrainTypeAt(i, j));
        }
    }
}

void GameArea::drawTileAt(const Cairo::RefPtr<Cairo::Context> &cr,
                          unsigned int xCoordinate, unsigned int yCoordinate,
                          std::string terrainType) {
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, tiles.at(terrainType),
                                  xCoordinate*get_width()/
                                  NUMBER_OF_TILES_TO_SHOW,
                                  yCoordinate*get_height()/
                                  NUMBER_OF_TILES_TO_SHOW);

    cr->rectangle(xCoordinate * get_width()/NUMBER_OF_TILES_TO_SHOW,
                  yCoordinate * get_height()/NUMBER_OF_TILES_TO_SHOW,
                  get_width()/NUMBER_OF_TILES_TO_SHOW,
                  get_height()/NUMBER_OF_TILES_TO_SHOW);
    cr->fill();
    cr->restore();
}

void GameArea::drawFlagAnimation(const Cairo::RefPtr<Cairo::Context> &cr,
                                 int xCoordinate, int yCoordinate) {
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, blueFlagVector.at(flagCounter),
                                  xCoordinate, yCoordinate);
    cr->rectangle(xCoordinate, yCoordinate,
                  blueFlagVector.at(flagCounter)->get_width(),
                  blueFlagVector.at(flagCounter)->get_height());
    cr->fill();
    if (flagCounter == blueFlagVector.size()-1){
        flagCounter = 0;
    }else{
        flagCounter++;
    }
    cr->restore();
}

void
GameArea::displaySomeStaticImg(const Cairo::RefPtr<Cairo::Context> &cr,
                               int xCoordinate,
                               int yCoordinate) {
    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, someImg, xCoordinate, yCoordinate);
    cr->rectangle(xCoordinate, yCoordinate,
                  someImg->get_width(), someImg->get_height());
    cr->fill();
    cr->restore();
}

void GameArea::setResources(PlayersMonitor *playersMonitor,
                            BuildingsMonitor *buildingsMonitor,
                            MapMonitor *mapMonitor) {
    this->playersMonitor = playersMonitor;
    this->buildingsMonitor = buildingsMonitor;
    this->mapMonitor = mapMonitor;
    this->camera.setMapWidth(mapMonitor->getXSize());
    this->camera.setMapHeight(mapMonitor->getYSize());
}
