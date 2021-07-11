/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.hpp
 */

#ifndef OSM_NODE
    #include "node.hpp"
#endif
#include "way.hpp"

#include <iostream>

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

#include <osmium/io/any_input.hpp>
#include <osmium/handler.hpp>

namespace Mapping
{
    /**
     * DataHandler
     * Handle data of the OSM file
     */
    class DataHandler : public osmium::handler::Handler {

        std::unordered_map<unsigned long long, unsigned int> nodes{};
        std::unordered_map<unsigned long long, Way> ways{};

        public:
            unsigned int cways = 0;
            unsigned int cnodes = 0;

            void way(const osmium::Way& w) noexcept
            {
                ++cways;

                const char* highway = w.tags()["highway"];
                if (!highway) { return; }
                if (w.ends_have_same_id()) { return; }

                const osmium::WayNodeList& ndl = w.nodes();

                unsigned long long way_id = w.positive_id();

                ways[way_id] = Way(way_id, highway, ndl);

                for (const auto* nd = ndl.begin(); nd != ndl.end(); ++nd) {
                    auto id = nd->positive_ref();
                    auto location = nd->location();
                    ways[way_id].add_node(id, location.lon(), location.lat()); /* adding this node to the way obj */
                    auto exists = nodes.find(id);
                    if (exists != nodes.end()) {
                        nodes[id] += 1;
                    } else nodes[id] = 1; 
                }
            }
            
            void node(const osmium::Node&) noexcept { ++cnodes; }

            unsigned int get_node_count(unsigned long long id)
            {
                return this->nodes[id];
            }

            int get_connected_nodes_count()
            {
                return this->nodes.size();
            }

            std::unordered_map<unsigned long long, Way>* get_ways()
            {
                return &this->ways;
            }
    };

    class Osm
    {
        private:
            osmium::io::File file;
            DataHandler dataHandler;
            bool counted = false;
        public:
            Osm(const std::string& mapFile);
            void read();
            std::unordered_map<unsigned long long, Way> get_ways();

            #pragma region Counting

            unsigned int count_ways();
            unsigned int count_nodes();
            unsigned int count_relations();

            int count_connected_nodes();

            std::tuple<unsigned int, unsigned int> count(); 

            #pragma endregion Counting
    };
}
