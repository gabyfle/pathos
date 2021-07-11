/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: way.cpp
 */

#ifndef OSM_NODE
    #include "node.hpp"
#endif
#include "way.hpp"

#include <string>
#include <vector>
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

    void Way::add_node(unsigned long long id, double lon, double lat)
    {
        Node nd;

        nd.id = id;
        nd.lon = lon;
        nd.lat = lat;

        this->nodes.push_back(nd);
    }

    int Way::get_nodes_count()
    {
        return this->nodes.size();
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
