/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.hpp
 */

#include <string>
#include <tuple>

#include <osmium/io/any_input.hpp>
#include <osmium/handler.hpp>

/**
 * CountHandler
 * Handle counting of the differents data such as ways, relations and nodes
 */
struct CountHandler : public osmium::handler::Handler {
    unsigned int ways = 0;
    void way(const osmium::Way&) noexcept { ++ways; }

    unsigned int nodes = 0;
    void node(const osmium::Node&) noexcept { ++nodes; }

    unsigned int relations = 0;
    void relation(const osmium::Relation&) noexcept { ++relations; }
};

class Osm
{
    private:
        osmium::io::File file;
        CountHandler *countHandler;
        bool counted = false;
    public:
        Osm(const std::string& mapFile);

        #pragma region Counting

        unsigned int count_ways(void);
        unsigned int count_nodes(void);
        unsigned int count_relations(void);

        std::tuple<unsigned int, unsigned int, unsigned int> count(void); 

        #pragma endregion Counting
};
