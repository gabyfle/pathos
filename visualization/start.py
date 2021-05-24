#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

import sys, getopt
import time
from pathlib import Path

import xml.etree.ElementTree as xmlp
import progressbar

import pygame
from pygame.locals import *

import osmium
import ways

import numpy as np
import math

config = {
    "fps": 60,
    "width": 7680,
    "height": 4320
}

# Using Mercator projection formula
def mercator(lat, lon, width = config["width"], height = config["height"]):
    x = (lon + 180) * (width / 360)

    lRad = (lat * np.pi) / 180

    N = np.log(math.tan((np.pi / 4) + (lRad / 2)))

    y = (height / 20) - (width * N / (2 * np.pi))

    return (x, y)

def to_screen(rTop, rBottom, lat, lon):
    coord = mercator(lat, lon)

    perX = ((coord[0] - rTop.pos[0]) / (rBottom.pos[0] - rTop.pos[0]))
    perY = ((coord[1] - rTop.pos[1]) / (rBottom.pos[1] - rTop.pos[1]))

    return (
        rTop.x + (rBottom.x - rTop.x) * perX,
        rBottom.y + (rBottom.y - rTop.y) * perY - config["height"]
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

    f = Path(file)
    if not f.is_file():
        raise Exception("OSM file not found.")

    with progressbar.ProgressBar(max_value=progressbar.UnknownLength) as bar:
        bar.update(1)

        rd = osmium.io.Reader(str(f))
        bx = rd.header().box()
        bounds = ((bx.top_right.lat, bx.top_right.lon), (bx.bottom_left.lat, bx.bottom_left.lon))

        bar.update(1)

        bottom = Reference(bounds[1][0], bounds[1][1], config["width"], config["height"])
        top = Reference(bounds[0][0], bounds[0][1], 0, 0)

        bar.update(1)

        idx = osmium.index.create_map("sparse_file_array," + str(f) + ".nodecache")
        lh = osmium.NodeLocationsForWays(idx)
        lh.ignore_errors()

        bar.update(1)

        w = ways.WaysHandler(idx)
        osmium.apply(rd, lh, w)

        bar.update(1)

        for way in w.ways:
            for part in way.parts:
                sPos = part.startPos()
                ePos = part.endPos()

                a = to_screen(top, bottom, sPos[0], sPos[1])
                b = to_screen(top, bottom, ePos[0], ePos[1])

                part.applyCoords(a, b)
            bar.update(1)

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
                pygame.draw.line(screen, (255, 255, 255), c[0], c[1], 1)

        pygame.display.flip()
        pygame.display.update()

        pygame.image.save(screen, "pathos_rendering_" + str(math.floor(time.time() / 10)) + ".png")

    def update(self, dt):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

    def __init__(self, mapData, drwTck = False):
        pygame.init()

        pygame.display.set_mode(flags=pygame.HIDDEN)
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
            elif drawed:
                pygame.quit()
                return
        
            dt = clock.tick(config['fps'])

def main(argv):
    osm = ""

    try:
        opts, args = getopt.getopt(argv, "hi:")
    except getopt.GetoptError:
        print("Usage: pathos.py -i <.osm data file>")
        sys.exit(1)

    for opt, arg in opts:
        if opt == "-h":
            print("Usage: pathos.py -i <.osm data file>")
            sys.exit(0)
        elif opt == "-i":
            osm = arg

    sTime = time.time()
    print("Generating map from file...")
    result = mapping(osm)
    print("Executed `mapping` in: " + str(time.time() - sTime))

    print("Generating image...")
    sTime = time.time()
    game = Game(result)
    print("Executed `Game` in: " + str(time.time() - sTime))

main(sys.argv[1:])
