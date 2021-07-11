/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: node.hpp
 */

#ifndef OSM_NODE
    #define OSM_NODE
#endif

namespace Mapping
{
    struct Node
    {
        unsigned long long id;
        double lon;
        double lat;
    };
}
