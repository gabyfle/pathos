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
import math

config = {
    'fps': 60,
    'width': 640,
    'height': 360
}

# Using Mercator projection formula
def yolo(lon, lat, width = config['width'], height = config['height']):
    lon, lat, width, height = float(lon), float(lat), float(width), float(height)
    r = width / (2 * np.pi)
    x = r * np.radians(lon)
    y = (height / 2) - r * np.log(np.tan(np.pi / 4 + np.radians(lat) / 2))
    return np.array([x, y, 0])

def mercator(lon, lat, minlat, maxlat):
    r = 6371
    x = r * lon * np.cos(np.radians((minlat + maxlat) / 2))
    y = r * lat

    return np.array([x, y, 0])

def to_screen(rTop, rBottom, lat, lon):
    coord = mercator(lat, lon, rBottom.lat, rTop.lat)

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
        def __init__(self, lat, lon, x, y, minlat, maxlat):
            self.lon = lon
            self.lat = lat
            self.x = x
            self.y = y

            self.pos = mercator(lat, lon, minlat, maxlat)

        def getCoords(self):
            return (self.lat, self.lon)


    def getCoordinates(attributes): # that's not very clean but you know what
        return ((float(attributes["maxlat"]), float(attributes["minlon"])), (float(attributes['minlat']), float(attributes['maxlon'])))

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

    bottom = Reference(bounds[1][0], bounds[1][1], config["width"], config["height"], bounds[1][0], bounds[0][0])
    top = Reference(bounds[0][0], bounds[0][1], 0, 0, bounds[1][0], bounds[0][0])

    w = ways.WaysHandler()
    w.apply_file(str(f), locations=True)

    for way in w.ways:
        for part in way.parts:
            a = to_screen(top, bottom, part.startPos()[0], part.startPos()[1])
            b = to_screen(top, bottom, part.endPos()[0], part.endPos()[1])
            part.applyCoords(a, b)

    return w.ways

class Game:
    drawTick = False

    def draw(self, screen):
        screen.fill((0, 0, 0))

        for way in self.data:
            for part in way.parts:
                c = part.coords()
                print(c)
                pygame.draw.line(screen, (255, 255, 255), c[0], c[1], 2)

        pygame.display.flip()

    def update(self, dt):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

    def __init__(self, mapData, drwTck = False):
        pygame.init()

        self.drawTick = drwTck
        self.data = mapData
    
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
    game = Game(result)

main()
