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

#include <osmium/io/any_input.hpp>

class Osm
{
    private:
        osmium::io::File file;
    public:
        Osm(std::string mapFile);
        void read(void);
};
