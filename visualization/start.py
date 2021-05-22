#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

import sys
from pathlib import Path

import xml.etree.ElementTree as xmlp

import pygame
from pygame.locals import *

import osmium
import ways

import numpy as np

config = {
    'fps': 60,
    'width': 1280,
    'height': 720
}

# Using Mercator projection formula
def mercator(lon, lat, width = config['width'], height = config['height']):
    lon, lat, width, height = float(lon), float(lat), float(width), float(height)
    r = width / (2 * np.pi)
    x = r * np.radians(lon)
    y = (height / 2) - r * np.log(np.tan(np.pi / 4 + np.radians(lat) / 2))
    return np.array([x, y, 0])

def to_screen(rTop, rBottom, lon, lat):
    coord = mercator(lon, lat)

    perX = ((coord[0] - rTop.pos[0]) / (rBottom.pos[0] - rTop.pos[0]))
    perY = ((coord[1] - rTop.pos[1]) / (rBottom.pos[1] - rTop.pos[1]))

    return (
        rTop.x + (rBottom.x - rTop.x) * perX,
        rBottom.y + (rBottom.y - rTop.y) * perY
    )

def mapping(file: str) -> list:
    """
    Reads an OSM file using Osmium and return a list of coordinates
    """

    class Reference():
        """
        A reference coordinate
        """
        def __init__(self, lon, lat, x, y):
            self.lon = lon
            self.lat = lat
            self.x = x
            self.y = y

            self.pos = mercator(lon, lat)


    def getCoordinates(attributes): # that's not very clean but you know what
        return ((float(attributes["minlat"]), float(attributes["minlon"])), (float(attributes['maxlat']), float(attributes['maxlon'])))

    f = Path(file)
    if not f.is_file():
        raise Exception("OSM file not found.")

    tree = xmlp.parse(str(f))
    root = tree.getroot()

    bounds = {}
    for t in root:
        if t.tag == "bounds":
            bounds = t
            break

    bounds = getCoordinates(bounds.attrib)

    bottom = Reference(bounds[0][0], bounds[0][1], config["width"], config["height"])
    top = Reference(bounds[1][0], bounds[1][1], 0, 0)

    w = ways.WaysHandler()
    w.apply_file(str(f), locations=True)

    for way in w.ways:
        for part in way.parts:
            a = to_screen(top, bottom, part.startPos()[0], part.startPos()[1])
            b = to_screen(top, bottom, part.endPos()[0], part.endPos()[1])
            part.applyCoords(a, b)

    return w

class Game:
    drawTick = False

    def draw(self, screen):
        screen.fill((0, 0, 0))

        pygame.display.flip()

    def update(self, dt):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

    def __init__(self, drwTck = False):
        pygame.init()

        self.drawTick = drwTck
    
        clock = pygame.time.Clock()
        screen = pygame.display.set_mode((config['width'], config['height']))
        
        dt = 1 / config['fps']

        drawed = False

        while True:
            self.update(dt)

            if self.drawTick or not drawed:
                self.draw(screen)
                drawed = True
        
            dt = clock.tick(config['fps'])

def main():
    result = mapping('map.osm')
    #game = Game(False)
    print('Done.')

main()
