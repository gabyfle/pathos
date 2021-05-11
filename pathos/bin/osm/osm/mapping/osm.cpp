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


Osm::Osm(int x, int y)
{
    this->one = x;
    this->two = y;
}

void Osm::displayValues(void)
{
    std::cout << "one: " << this->one << std::endl;
    std::cout << "two: " << this->two << std::endl;
}
