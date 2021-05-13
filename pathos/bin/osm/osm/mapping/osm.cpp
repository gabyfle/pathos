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
#include <tuple>

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
 * @return uint
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

/**
 * Osm::count_nodes
 * Counts the nodes available in the current OSM file
 * @return uint
 */
unsigned int Osm::count_nodes(void)
{
    struct CountHandler : public osmium::handler::Handler {
        unsigned int nodes = 0;
        void nodes(const osmium::Node&) noexcept { ++nodes; }
    };

    osmium::io::Reader reader{this->file};
    
    CountHandler handler;
    osmium::apply(reader, handler);

    return handler.nodes;
}

/**
 * Osm::count_relations
 * Counts the relations available in the current OSM file
 * @return uint
 */
unsigned int Osm::count_relations(void)
{
    struct CountHandler : public osmium::handler::Handler {
        unsigned int relations = 0;
        void relations(const osmium::Relation&) noexcept { ++relations; }
    };

    osmium::io::Reader reader{this->file};
    
    CountHandler handler;
    osmium::apply(reader, handler);

    return handler.relations;
}

/**
 * Osm::count
 * Counts ways, nodes and relations of the OSM file
 * @return std::tuple<uint, uint, uint>
 */
std::tuple<unsigned int, unsigned int, unsigned int> Osm::count(void)
{
    return std::tuple<unsigned int, unsigned int, unsigned int>{this->count_ways(), this->count_nodes(), this->count_relations()};
}
