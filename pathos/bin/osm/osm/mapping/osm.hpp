/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.hpp
 */

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
        public:
            unsigned int cways = 0;
            unsigned int cnodes = 0;
            unsigned int crelations = 0;

            std::unordered_map<unsigned long long, unsigned int> nodes{};
            std::vector<Way> ways;

            void way(const osmium::Way& way) noexcept
            {
                ++cways;

                const char* highway = way.tags()["highway"];
                if (!highway) { return; }
                if (way.ends_have_same_id()) { return; }

                const osmium::WayNodeList& ndl = way.nodes();

                ways.push_back(Way(way.positive_id(), highway, ndl));

                for (const auto* nd = ndl.begin(); nd != ndl.end(); ++nd) {
                    auto id = (*nd).positive_ref();
                    auto exists = nodes.find(id);
                     if (exists != nodes.end()) {
                         nodes[id] += 1;
                     } else nodes[id] = 1;
                }
            }
            
            void node(const osmium::Node&) noexcept { ++cnodes; }        
            void relation(const osmium::Relation&) noexcept { ++crelations; }
    };

    class Osm
    {
        private:
            osmium::io::File file;
            DataHandler dataHandler;
            bool counted = false;
        public:
            Osm(const std::string& mapFile);
            void read(void);

            #pragma region Counting

            unsigned int count_ways(void);
            unsigned int count_nodes(void);
            unsigned int count_relations(void);

            std::tuple<unsigned int, unsigned int, unsigned int> count(void); 

            #pragma endregion Counting
    };
}
