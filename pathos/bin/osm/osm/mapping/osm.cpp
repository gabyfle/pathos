/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: osm.cpp
 */

#include "osm.hpp"

#include <iostream>
#include <string>

#include <osmium/io/any_input.hpp>
#include <osmium/util/file.hpp>
#include <osmium/util/progress_bar.hpp>

/**
 * error
 * Little snippet to handle error messages
 * @param string func: Function where the error occured
 * @param string e: the error
 */
inline void error(std::string func, std::string e)
{
    std::cerr << "An error occurred in function : " << func << ". Error: " << std::endl;
    std::cerr << e << std::endl;
}

/**
 * Osm::Osm
 * @param std::string mapFile: OSM map file to read data from
 */
Osm::Osm(std::string mapFile)
{
    try
    {
        this->file = osmium::io::File{mapFile};
        std::cout << mapFile << std::endl;
    }
    catch(const std::exception& e)
    {
        error("Osm::Osm", e.what());
    }
}

/**
 * Osm::read
 * Reads a file and displays a progress bar
 */
void Osm::read(void)
{
    try
    {
        osmium::io::Reader reader{this->file};
        osmium::ProgressBar progress{reader.file_size(), osmium::isatty(2)};

        // OSM data comes in buffers, read until there are no more.
        while (osmium::memory::Buffer buffer = reader.read()) {
            // Update progress bar for each buffer.
            progress.update(reader.offset());
        }

        // Progress bar is done.
        progress.done();

        // You do not have to close the Reader explicitly, but because the
        // destructor can't throw, you will not see any errors otherwise.
        reader.close();
    }
    catch(const std::exception& e)
    {
        error("Osm::read", e.what());
    }
    
}
