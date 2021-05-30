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
            Way() {};
            Way(const unsigned long long&, const std::string&, const osmium::WayNodeList&);
            unsigned long long get_id();
            std::string get_type();
            double get_length();
    };
}