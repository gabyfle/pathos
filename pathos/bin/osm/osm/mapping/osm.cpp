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

using IntTriplet = std::tuple<unsigned int, unsigned int, unsigned int>;

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
     * Osm::count_relations
     * Counts the relations available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_relations(void)
    {
        return this->dataHandler.crelations;
    }

    /**
     * Osm::count
     * Counts ways, nodes and relations of the OSM file
     * @return std::tuple<uint, uint, uint>
     */
    IntTriplet Osm::count(void)
    {
        return IntTriplet{this->count_ways(), this->count_nodes(), this->count_relations()};
    }
}
