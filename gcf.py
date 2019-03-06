#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Feb  8 18:58:54 2019

@author: victortaksheyev
"""

# program will find the gf of a number

factors = [];
"""
def gcfCalc(number):
    for x in range(number):
        if (number % (x+1)) == 0:
            factors.append(x+1)
"""

def gcfCalc(number):
    for x in range(number):
        if (number % (x+1)) == 0:
            factors.append(x+1)
            
        

gcfCalc(523)