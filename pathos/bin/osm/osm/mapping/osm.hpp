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

class Osm
{
    private:
        osmium::io::File file;
    public:
        Osm(const std::string& mapFile);

        #pragma region Counting

        unsigned int count_ways(void);
        unsigned int count_nodes(void);
        unsigned int count_relations(void);

        std::tuple<unsigned int, unsigned int, unsigned int> count(void); 

        #pragma endregion Counting
};
