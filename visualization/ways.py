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

    disabled = False

    def __init__(self, start, end):
        self.start = start
        self.end = end

    def startPos(self) -> float:
        return self.start
    
    def endPos(self) -> float:
        return self.end
    
    def applyCoords(self, x, y) -> None:
        self.startCoords = x
        self.endCoords = y

    def coords(self):
        if self.disabled:
            raise Exception("This part has been disabled")
        return (self.startCoords, self.endCoords)

    def disable(self):
        self.disabled = True

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
            self.parts += [Part(getLocation(nodes[k]), getLocation(nodes[k + 1]))]
        
    def distance(self):
        return self.length

class WaysHandler(SimpleHandler):
    ways: list

    def __init__(self, idx, ultra):
        super(WaysHandler, self).__init__()
        self.ways = []
        self.idx = idx
        self.ultra = ultra
    
    def way(self, w): # this is heavy
        if not self.ultra and w.ends_have_same_id():
            return
        self.ways += [Way(w.nodes)]
