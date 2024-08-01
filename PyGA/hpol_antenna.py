import random

from pathlib import Path

import numpy as np

class HPOLAntenna:
    
    def __init__(self, genes=None):
        self.genes = genes
        self.fitness = 0.0
        self.true_fitness = 0.0
        # NEW HPOL SPECIFIC VARIABLES THAT ARE SUBJECT TO CHANGE
        self.num_plates_min = 4.0
        self.num_plates_max = 4.0
        self.radius_min = 0.5
        self.radius_max = 10.0
        self.arc_length_plate_min = 0.5
        self.arc_length_plate_max = 10.0
        self.height_min = 0.5
        self.height_max = 10.0
        self.ferrite_height_min = 1.0
        self.ferrite_height_max = 12.0
        self.ferrite_radius_min = 0.5
        self.ferrite_radius_max = 3.0
    
    def initialize(self):
        '''Initialize the genes of the HPOL antenna. 
        The genes are: '''
        
        # Generate random values
        num_plates = random.uniform(self.num_plates_min, self.num_plates_max)
        radius = random.uniform(self.radius_min, self.radius_max)
        arc_length_plate = random.uniform(self.arc_length_plate_min, self.arc_length_plate_max)
        height = random.uniform(self.height_min, self.height_max)
        ferrite_height = random.uniform(self.ferrite_height_min, self.ferrite_height_max)
        ferrite_radius = random.uniform(self.ferrite_radius_min, self.ferrite_radius_max)
        
        self.genes = [num_plates, radius, arc_length_plate, height, ferrite_height, ferrite_radius]
    
    def save_as_comparison(self, filename):
        '''save the current genes as a comparison file.'''
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)
    
    def check_genes(self):
        '''Check if the genes are valid. 
        Return False if the genes are invalid.'''
        
        # Load genes
        (num_plates, radius, arc_length_plate, height, ferrite_height, ferrite_radius) = self.genes

        # Variables
        valid_design = False
        
        
        # Run checks
        if (not (self.radius_min <= radius <= self.radius_max) or 
            not (self.height_min <= height <= self.height_max)):
            valid_design = False
        elif not (self.num_plates_min <= num_plates <= self.num_plates_max):
            valid_design = False
        elif not (self.arc_length_plate_min <= arc_length_plate <= self.arc_length_plate_max):
            valid_design = False
        elif not (self.ferrite_height_min <= ferrite_height <= self.ferrite_height_max):
            valid_design = False
        elif not (self.ferrite_radius_min <= ferrite_radius <= self.ferrite_radius_max):
            valid_design = False
        else:
            valid_design = True

        return valid_design
    
    
    def __str__(self) -> str:
        '''Return a string representation of the antenna's genes.'''
        return str(self.genes)
        