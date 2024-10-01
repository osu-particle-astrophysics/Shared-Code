import random

from pathlib import Path

import numpy as np

class IceParameters:
    
    def __init__(self, genes=None):
        self.genes = genes
        self.fitness = 0.0
        self.true_fitness = 0.0
        self.MAX_PHI = 360 ## Rotation about z-axis
        self.MAX_THETA = 180 ## Rotation about y-axis
        self.MAX_PSI = 360 ## Rotation about z-axis
				self.MAX_CROSS_POL = 180 ## Initial cross-polarization angle
        
    
    def initialize(self):
        '''Initialize the genes of the horn antenna. 
        The genes are: [side_length, height, x_0, y_0, z_f, y_f, 
        beta, trpzd_length, trpzd_height]'''
        
        valid_design = False
        while valid_design == False:
            # Generate random values
            phi = random.uniform(0.0, self.MAX_PHI)
            theta = random.uniform(0.0, self.MAX_THETA)
            psi = random.uniform(0.0, self.MAX_PSI)
            delta = random.uniform(0.0, self.MAX_DELTA)

            self.genes = [phi, theta, psi, delta]
            
            valid_design = self.check_genes()
        
        
    
    def check_genes(self):
        '''Check if the genes are valid. 
        Return False if the genes are invalid.'''
        
        # Load genes
        (phi, theta, psi, delta) = self.genes

        # Variables
        valid_design = False
        
        # Check if phi, theta, psi give repeated orientation
				# phi, theta, psi <=> psi + pi, pi - theta, psi + pi
        
        # Run checks
				if (phi > 180 and theta > 90 and psi > 180):
            valid_design = False
        else:
            valid_design = True

        return valid_design
    
    
    ## Evaluate fitness by reading a file
#    def evaluate_fitness():
    def evaluate_fitness(self, comparison):
        '''Calculate the euclidean distance between the genes
        of the horn antenna and the comparison genes.'''
        
        euclidean_distance = 0.0
        gene_count = len(self.genes)
        for i in range(gene_count):
            numerator = (self.genes[i] - comparison[i]) ** 2
            denominator = (self.genes[i] + comparison[i]) ** 2
            euclidean_distance += numerator / denominator
            
        normalized_distance = euclidean_distance / (2 * gene_count)
        
        normalized_distance = normalized_distance ** 0.5
        
        self.fitness = 1.0 - normalized_distance
    
    
    def save_as_comparison(self, filename):
        '''save the current genes as a comparison file.'''
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)
    
    
    def __str__(self) -> str:
        '''Return a string representation of the antenna's genes.'''
        return str(self.genes)
        
