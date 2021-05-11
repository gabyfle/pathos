/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.hpp
 */

#include <string>

class Osm
{
    private:
        std::string mapFile;
    public:
        Osm(std::string mapFile);
};
