#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

import sys

import pygame
from pygame.locals import *
import numpy as np
import xml.etree.ElementTree as xmlp

config = {
    'fps': 60,
    'width': 1280,
    'height': 720
}

# Using Mercator projection formula
def mercator(lon, lat, width = 14, height = 8):
    lon, lat, width, height = float(lon), float(lat), float(width), float(height)
    s = 40075016 * np.cos(np.radians(lat)) / 2 ** 23 
    r = width / (2 * np.pi)
    x = r * np.radians(lon)
    y = (height / 2) - r * np.log(np.tan(np.pi / 4 + np.radians(lat) / 2))
    return np.array([x * s, y * s, 0])

def mapping(data):
    """
    Gets every nodes from an entry XML file and calculates every coordinates
    with the Mercator projection
    """
    tree = xmlp.parse(data)
    root = tree.getroot()

    bounds = {}
    nodes = {}
    ways = {}

    for child in root:
        t = child.tag
        att = child.attrib
        if t == 'bounds': bounds = att
        if t == 'node':
            bds = [mercator(bounds['minlon'], bounds['minlat']), mercator(bounds['maxlon'], bounds['maxlat'])]
            s = (bds[1][0] - bds[0][0], bds[1][1] - bds[0][1])
            xy = mercator(att['lon'], att['lat'])
            nodes[att['id']] = np.array([xy[0], xy[1], 0])
        if t == 'way': ways[att['id']] = [nd.attrib['ref'] for nd in child if nd.tag == 'nd']

    lines = []
    for way, nds in ways.items():
        lines.append([nodes[node] for node in nds])

    return lines


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
    game = Game(False)

main()
