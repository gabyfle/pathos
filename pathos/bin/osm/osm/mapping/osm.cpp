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
#include <osmium/visitor.hpp>
#include <osmium/util/file.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

using Index = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
using LocationHandler = osmium::handler::NodeLocationsForWays<Index>;

namespace Mapping
{
    /**
     * Osm::Osm
     * @param mapFile <string>: OSM map file to read data from
     */
    Osm::Osm(const std::string& mapFile)
    {
        this->file = osmium::io::File{mapFile};
    }

    /**
     * Osm::read
     * Reads the file and proceed the data into usable one
     */
    void Osm::read(void)
    {
        osmium::io::Reader reader{this->file, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};
        Index index;
        LocationHandler location{index};

        osmium::apply(reader, location, this->dataHandler);
    }

    /**
     * Osm::count_ways
     * Counts the ways available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_ways(void)
    {
        return this->dataHandler.cways;
    }

    /**
     * Osm::count_nodes
     * Counts the nodes available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_nodes(void)
    {
        return this->dataHandler.cnodes;
    }

    /**
     * Osm::count
     * Counts ways and nodes of the OSM file
     * @return std::tuple<uint, uint>
     */
    std::tuple<unsigned int, unsigned int> Osm::count(void)
    {
        return std::tuple<unsigned int, unsigned int>{this->count_ways(), this->count_nodes()};
    }

    /**
     * Osm::count_connected_nodes()
     * Returns the number of connected nodes (ie. nodes that are connected to at least one way) in the given file
     * @return int
     */
    int Osm::count_connected_nodes()
    {
        return this->dataHandler.get_connected_nodes_count();
    }

    /**
     * Osm::get_ways()
     * Returns an iterator throught file's ways (that starts at the first way)
     * @return std::unordered_map<unsigned long long, Way>
     */
    std::unordered_map<unsigned long long, Way> Osm::get_ways()
    {
        auto ways = this->dataHandler.get_ways();

        return *ways;
    }
}
