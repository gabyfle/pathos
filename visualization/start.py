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
    s = 40075016 * np.cos(np.radians(lat)) / 2 ** 23 
    r = width / (2 * np.pi)
    x = r * np.radians(lon)
    y = (height / 2) - r * np.log(np.tan(np.pi / 4 + np.radians(lat) / 2))
    return np.array([x * s, y * s, 0])

def mapping(file: str) -> list:
    """
    Reads an OSM file using Osmium and return a list of coordinates
    """

    f = Path(file)
    if not f.is_file():
        raise Exception("OSM file not found.")

    w = ways.WaysHandler()
    w.apply_file(str(f), locations=True)

    for way in w.ways:
        print(len(way))

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
    game = Game(False)

main()
