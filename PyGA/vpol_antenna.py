import random

from pathlib import Path

import numpy as np

class VPOLAntenna:
    
    def __init__(self, genes=None):
        self.genes = genes
        self.fitness = 0.0
        self.true_fitness = 0.0
        # NEW HPOL SPECIFIC VARIABLES THAT ARE SUBJECT TO CHANGE
        self.num_plates_min = 3.0
        self.num_plates_max = 4.0
        self.radius_min = 0.5
        self.radius_max = 10.0
        self.arc_length_plate_min = 0.5
        self.arc_length_plate_max = 10.0
        self.arc_length_angle_min = 0.5
        self.arc_length_angle_max = 10.0
        self.height_min = 0.5
        self.height_max = 10.0
    
    def initialize(self):
        '''Initialize the genes of the HPOL antenna. 
        The genes are: '''
        
        # Generate random values
        num_plates = random.uniform(self.num_plates_min, self.num_plates_max)
        radius = random.uniform(self.radius_min, self.radius_max)
        arc_length_plate = random.uniform(self.arc_length_plate_min, self.arc_length_plate_max)
        arc_length_angle = random.uniform(self.arc_length_angle_min, self.arc_length_angle_max)
        height = random.uniform(self.height_min, self.height_max)
        
        self.genes = [num_plates, radius, arc_length_plate, arc_length_angle, height]
    
    def save_as_comparison(self, filename):
        '''save the current genes as a comparison file.'''
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)
    
    
    def __str__(self) -> str:
        '''Return a string representation of the antenna's genes.'''
        return str(self.genes)
        