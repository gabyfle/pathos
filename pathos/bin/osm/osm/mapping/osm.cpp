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

namespace Mapping
{
    /**
     * Osm::Osm
     * @param mapFile <string>: OSM map file to read data from
     */
    Osm::Osm(const std::string& mapFile)
    {
        this->file = osmium::io::File{mapFile};

        this->countHandler = new CountHandler;
    }

    /**
     * Osm::count_ways
     * Counts the ways available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_ways(void)
    {
        osmium::io::Reader reader{this->file};
        
        if (!counted)
            osmium::apply(reader, *this->countHandler);
        this->counted = true;

        return (*this->countHandler).ways;
    }

    /**
     * Osm::count_nodes
     * Counts the nodes available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_nodes(void)
    {
        osmium::io::Reader reader{this->file};
        
        if (!counted)
            osmium::apply(reader, (*this->countHandler));
        this->counted = true;

        return (*this->countHandler).nodes;
    }

    /**
     * Osm::count_relations
     * Counts the relations available in the current OSM file
     * @return uint
     */
    unsigned int Osm::count_relations(void)
    {
        osmium::io::Reader reader{this->file};

        if (!counted)
            osmium::apply(reader, (*this->countHandler));
        this->counted = true;

        return (*this->countHandler).relations;
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
}