#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#--
# pathos - pathfinding algorithm's results visualization
# 2021 - Gabriel Santamaria
#
# visualization - visualize algorithms throught animations
# Roads handling algorithms
#--

from osmium import *

def getLocation(node):
    return (node.location.lat, node.location.lon)

class Part():
    """
    A little portion of a way
    """
    start: float
    end:   float

    def __init__(self, start, end):
        self.start = start
        self.end = end

    def startPos(self) -> float:
        return self.start
    
    def endPos(self) -> float:
        return self.end
    
    def applyCoords(self, x, y) -> None:
        self.x = x
        self.y = y

    def coords(self):
        return (self.x, self.y)

class Way():
    """
    A way is a connection between two nodes
    We're also handling a "size" of the road to know how to draw it
    """
    parts: list
    nodes: list

    length: float # way length

    def __init__(self, nodes):
        self.parts = []
        self.nodes = [getLocation(node) for node in nodes]

        self.length = geom.haversine_distance(nodes)

        n = len(nodes) - 1    
        for k in range(n):
            if k == n: break
            self.parts += [Part(getLocation(nodes[k]), getLocation(nodes[k +1]))]
        
    def distance(self):
        return self.length

class WaysHandler(SimpleHandler):
    ways: list

    def __init__(self):
        SimpleHandler.__init__(self)
        self.ways = []
    
    def way(self, w): # this is heavy
        self.ways += [Way(w.nodes)]
