#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

from manim import config
from manimlib import *
import numpy as np
import xml.etree.ElementTree as xmlp

# Using Mercator projection formula
def mercator(lon, lat, width = 14, height = 8):
    lon, lat, width, height = float(lon), float(lat), float(width), float(height)
    s = 40075016 * np.cos(np.radians(lat)) / 2 ** 23 
    r = width / (2 * PI)
    x = r * np.radians(lon)
    y = (height / 2) - r * np.log(np.tan(PI / 4 + np.radians(lat) / 2))
    return np.array([x * s, y * s, 0])

class Escape(Scene):
    def mapping(self):
        tree = xmlp.parse('map.osm')
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
            for node in nds:
                print(nodes[node])
            lines.append([Dot(nodes[node]) for node in nds])

        return lines

    def population(self, n: int):
        return [Dot(color=random_color()) for k in range(n)]

    def construct(self):
        for l in self.mapping():
            for n in l:
                self.add(n)
        for p in self.population(40):
            self.add(p)
        
