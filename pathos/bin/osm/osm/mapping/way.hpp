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
#include <vector>
#include <osmium/osm/way.hpp>

namespace Mapping
{
    class Way
    {
        private:
            unsigned long long id;
            std::string type;
            double length;
            /* Way's nodes */
            unsigned long long start_id;
            unsigned long long end_id;

            std::vector<Node> nodes;

        public:
            Way() {};
            Way(const unsigned long long&, const std::string&, const osmium::WayNodeList&);
            void add_node(unsigned long long, double, double);
            unsigned long long get_start();
            unsigned long long get_end();
            int get_nodes_count();
            std::vector<Node> get_nodes();
            unsigned long long get_id();
            std::string get_type();
            double get_length();
    };
}
