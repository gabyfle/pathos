/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: way.hpp
 */

#include <string>
#include <osmium/geom/util.hpp>
#include <osmium/osm/way.hpp>

namespace Mapping
{
    class Way
    {
        private:
            unsigned long long id;
            std::string type;
            double length;

        public:
            Way(const unsigned long long& id, const std::string& type, const osmium::WayNodeList& nodes);
    };
}