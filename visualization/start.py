#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
#--

from manimlib import *
import numpy as np
import xml.etree.ElementTree as xmlp

def spheric_to_cartesian(lon, lat):
    lon, lat = np.radians(lon), np.radians(lat)
    return np.array(6371 * np.cos(lon) * np.cos(lat), 6371 * np.cos(lon) * np.sin(lat))

class Escape(Scene):
    def mapping(self):
        width, height = config['frame_width'], config['frame_height']
        tree = xmlp.parse('map.osm')
        root = tree.getroot()

        bounds = {}
        nodes = {}
        ways = {}

        for child in root:
            t = child.tag
            att = child.attrib
            if t == 'bounds': bounds = att
            if t == 'node': nodes[att['id']] = spheric_to_cartesian(att['lon'], att['lat'])
            if t == 'way': ways[att['id']] = [nd.attrib['ref'] if nd.tag == 'nd' for nd in child]

    def population(self, n: int):
        return [Dot(color=random_color()) for k in range(n)]

    def construct(self):
        population = self.population(40)
        pass        
