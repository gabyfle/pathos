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
    'width': 1920,
    'height': 1080
}

# Using Mercator projection formula
def mercator(lat, lon, width = config["width"], height = config["height"]):
    x = (lon + 180) * (width / 360)

    lRad = (lat * np.pi) / 180

    N = np.log(np.tan((np.pi / 4) + (lRad / 2)))

    y = (height / 2) - (width * N / (2 * np.pi))

    return (x, y)

def to_screen(rTop, rBottom, lat, lon):
    coord = mercator(lat, lon)

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
        def __init__(self, lat, lon, x, y):
            self.lon = lon
            self.lat = lat
            self.x = x
            self.y = y

            self.pos = mercator(lat, lon)

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

    bottom = Reference(bounds[1][0], bounds[1][1], config["width"], config["height"])
    top = Reference(bounds[0][0], bounds[0][1], 0, 0)

    w = ways.WaysHandler()
    w.apply_file(str(f), locations=True)

    def is_in_area(p):
        return top.lat < p[0] or p[1] < top.lon or bottom.lon < p[1] or p[0] < bottom.lat

    for way in w.ways:
        for part in way.parts:
            sPos = part.startPos()
            ePos = part.endPos()

            a = to_screen(top, bottom, sPos[0], sPos[1])
            b = to_screen(top, bottom, ePos[0], ePos[1])

            part.applyCoords(a, b)

    return w.ways

class Game:
    drawTick = False

    def draw(self, screen):
        screen.fill((0, 0, 0))

        for way in self.data:
            for part in way.parts:
                try:
                    c = part.coords()
                except Exception as e:
                    continue
                pygame.draw.line(screen, (255, 255, 255), (c[0][1], c[0][0]), (c[1][1], c[1][0]), 2)

        pygame.display.flip()
        pygame.display.update()

    def update(self, dt):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

    def __init__(self, mapData, drwTck = False):
        pygame.init()

        pygame.display.set_caption("Pathos visualization")

        self.drawTick = drwTck
        self.data = mapData
    
        clock = pygame.time.Clock()
        screen = pygame.display.set_mode((config["width"], config["height"]))
        
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
