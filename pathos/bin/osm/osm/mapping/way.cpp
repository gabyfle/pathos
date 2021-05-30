/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: way.cpp
 */

#include "way.hpp"

#include <string>
#include <osmium/osm/way.hpp>
#include <osmium/geom/haversine.hpp>

namespace Mapping
{
    Way::Way(const unsigned long long& id, const std::string& type, const osmium::WayNodeList& nodes)
    {
        this->id = id;
        this->type = type;

        this->length = osmium::geom::haversine::distance(nodes);
    }

    unsigned long long Way::get_id()
    {
        return this->id;
    }

    std::string Way::get_type()
    {
        return this->type;
    }

    double Way::get_length()
    {
        return this->length;
    }
}
