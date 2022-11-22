# -*- coding: utf-8 -*-
"""
Created on Tue Nov 22 11:05:46 2022

@author: audre
"""
import numpy as np

class queue():
    def __init__(self,capacity=32):
        self.capacity = capacity
        self.start = 0
        self.array = np.zeros(capacity)
        
    def push(self, elt):
        self.start += 1
        self.start %= self.capacity
        self.array[self.start]=elt
        
    def at(self, index):
        return self.array[(self.start + index)%self.capacity]
            

#THIS QUEUE ALLOWS FOR NEGATIVE INDEXES!!!!!
queue = queue()
            