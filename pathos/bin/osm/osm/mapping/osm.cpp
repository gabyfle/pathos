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
 * Osm constructor
 * @param std::string mapFile: OSM map file to read data from
 */
Osm::Osm(std::string mapFile)
{
    try
    {
        this->file = osmium::io::File{mapFile};
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

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
        std::cerr << e.what() << '\n';
    }
    
}
