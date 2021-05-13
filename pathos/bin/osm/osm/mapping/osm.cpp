/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.cpp
 */

#include "osm.hpp"

#include <iostream>
#include <string>

#include <osmium/io/any_input.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>
#include <osmium/util/file.hpp>

/**
 * Osm::Osm
 * @param mapFile <string>: OSM map file to read data from
 */
Osm::Osm(const std::string& mapFile)
{
    this->file = osmium::io::File{mapFile};
}

/**
 * Osm::count_ways
 * Counts the ways available in the current OSM file
 * @return uint64_t
 */
unsigned int Osm::count_ways(void)
{
    struct CountHandler : public osmium::handler::Handler {
        unsigned int ways = 0;
        void way(const osmium::Way&) noexcept { ++ways; }
    };

    osmium::io::Reader reader{this->file};
    
    CountHandler handler;
    osmium::apply(reader, handler);

    return handler.ways;
}
