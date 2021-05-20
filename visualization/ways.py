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

class Part():
    """
    A little portion of a way
    """
    start: osm.Node
    end:   osm.Node

    def __init__(self, start, end):
        self.start = start
        self.end = end

    def startPos(self) -> osm.Location:
        return self.start
    
    def endPos(self) -> osm.Location:
        return self.end

class Way():
    """
    A way is a connection between two nodes
    We're also handling a "size" of the road to know how to draw it
    """
    parts: list
    nodes: list

    def __init__(self, nodes):
        self.parts = []
        self.nodes = nodes

        n = len(nodes) - 1    
        for k in range(n):
            if k == n: break
            self.parts += [Part(nodes[k], nodes[k + 1])]
        
    def __len__(self):
        return geom.haversine_distance(self.nodes)

class WaysHandler(SimpleHandler):
    ways: list

    def __init__(self):
        SimpleHandler.__init__(self)
        self.ways = []
    
    def way(self, w): # this is heavy
        print(type(w.nodes))
        self.ways += [Way(w.nodes)]
