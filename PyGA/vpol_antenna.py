import random

from pathlib import Path

import numpy as np

import sys

import yaml

class VPOLAntenna:
    
    def __init__(self, rundir, genes=None):
        settingsfile=Path(rundir) / "settings.yaml"

        self.initialize_settings(settingsfile)
        self.genes = genes
        self.fitness = 0.0
        self.true_fitness = 0.0
        # VPOL Variables
        if self.settings['curved'] == 1: # Curved
            self.min_rad = 0.0
            self.max_rad = 7.5
            self.min_length = 37.5
            self.max_length = 140.0
            self.min_a = -1
            self.max_a = 1
            self.min_b = -1
            self.max_b = 1
        else: # Not curved
            self.min_rad = 0.0
            self.max_rad = 7.5
            self.min_length = 37.5
            self.max_length = 140.0
            self.min_theta = 0.0
            self.max_theta = np.arctan(self.max_rad/self.min_length)
            self.max_seperation = 2.5
            self.min_seperation = 2.5
                
    def initialize(self):
        '''Initialize the genes of the HPOL antenna. 
        The genes are: '''
        
        # Generate random values
        if self.settings['curved'] == 0: # not curved
            if self.settings['nsections'] == 1: # symmetric
                radius = random.uniform(self.min_rad, self.max_rad)
                length = random.uniform(self.min_length, self.max_length)
                theta = random.uniform(self.min_theta, self.max_theta)
                # Set the genes
                self.genes = np.array([radius, length, theta])
            else: # asymmetric
                radius = random.uniform(self.min_rad, self.max_rad)
                length = random.uniform(self.min_length, self.max_length)
                theta = random.uniform(self.min_theta, self.max_theta)
                seperation = random.uniform(self.min_seperation, self.max_seperation)
                radius1 = random.uniform(self.min_rad, self.max_rad)
                length1 = random.uniform(self.min_length, self.max_length)
                theta1 = random.uniform(self.min_theta, self.max_theta)
                # Check for if symmetries are enforced for one parameter strictly in setup
                if self.settings['radius'] == 0:
                    radius1 = radius
                if self.settings['length'] == 0:
                    length1 = length
                if self.settings['angle'] == 0:
                    angle1 = angle
                # Set the genes
                self.genes = np.array([radius, length, theta, seperation, radius1, length1, theta1])
        else: # Curved
            radius = random.uniform(self.min_rad, self.max_rad)
            length = random.uniform(self.min_length, self.max_length)
            a = random.uniform(self.min_a, self.max_a)
            b = random.uniform(self.min_b, self.max_b)
            radius1 = random.uniform(self.min_rad, self.max_rad)
            length1 = random.uniform(self.min_length, self.max_length)
            a1 = random.uniform(self.min_a, self.max_a)
            b1 = random.uniform(self.min_b, self.max_b)
            # Check for if symmetries are enforced for one parameter strictly in setup
            if self.settings['radius'] == 0:
                radius1 = radius
            if self.settings['length'] == 0:
                length1 = length
            if self.settings['a'] == 0:
                a1 = a
            if self.settings['b'] == 0:
                b1 = b
            # Set the genes
            self.genes = np.array([radius, length, a, b, radius1, length1, a1, b1])
            
    def initialize_settings(self, settingsfile):
        '''Initialize the settings from the settings file.'''
        settingspath = Path(settingsfile)
        if settingspath.exists():
            with open(settingspath, 'r') as file:
                settings = yaml.load(file, Loader=yaml.FullLoader)
        else:
            sys.exit('Settings file not found. Exiting.')
            
        self.settings = settings
    
    def save_as_comparison(self, filename):
        '''save the current genes as a comparison file.'''
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)
    
    
    def __str__(self) -> str:
        '''Return a string representation of the antenna's genes.'''
        return str(self.genes)
        