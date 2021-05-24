#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

import sys, argparse
import time
from pathlib import Path

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

def mapping(file: str, ultra: bool) -> list:
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

        bottom = Reference(bounds[1][0], bounds[0][1], config["width"], config["height"])
        top = Reference(bounds[0][0], bounds[1][1], 0, 0)

        bar.update(1)

        idx = osmium.index.create_map("sparse_file_array," + str(f) + ".nodecache")
        lh = osmium.NodeLocationsForWays(idx)
        lh.ignore_errors()

        bar.update(1)

        w = ways.WaysHandler(idx, ultra)
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

        pygame.image.save(screen, self.output)

    def update(self, dt):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

    def __init__(self, mapData, output, drwTck = False):
        pygame.init()

        self.output = output

        pygame.display.set_mode(flags=pygame.HIDDEN)
        pygame.display.set_caption("Pathos visualization")

        self.drawTick = drwTck
        self.data = mapData
    
        clock = pygame.time.Clock()
        screen = pygame.display.set_mode((config["width"], config["height"]))
        
        dt = 1 / config["fps"]

        drawed = False

        while True:
            self.update(dt)

            if self.drawTick or not drawed:
                self.draw(screen)
                drawed = True
            elif drawed:
                pygame.quit()
                return
        
            dt = clock.tick(config["fps"])

def get_args():
    parser = argparse.ArgumentParser(prog="pathos visualization", description="Visualization of Pathos algorithms")

    files = parser.add_argument_group(title="File input and output")
    files.add_argument("-i", action="store", nargs=1, metavar=("<input>"), help="OpenStreetMap input file", type=str, required=True)
    files.add_argument('-o', action="store", nargs=1, metavar="<output>", help="Image generation output file", type=str, default = "pathos_rendering_" + str(math.floor(time.time() / 10)) + ".png", required=False)

    # Configuration
    config = parser.add_argument_group(title="Configuration of the rendering")
    config.add_argument('--ultra', help="Applies the ULTRA mode. Warning, launch it only on a tiny area if you don't want your PC to caught fire.", nargs="?", const=True, default=False, type=bool)

    return parser.parse_args()

def main():
    args = get_args()

    sTime = time.time()
    print("Generating map from file...")
    result = mapping(args.i[0], args.ultra)
    print("Executed `mapping` in: " + str(time.time() - sTime))

    print("Generating image...")
    sTime = time.time()
    game = Game(result, args.o)
    print("Executed `Game` in: " + str(time.time() - sTime))

main()
