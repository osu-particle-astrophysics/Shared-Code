import random

import fit_module

from pathlib import Path

import numpy as np

import subprocess

import sys

class IceParameters:
    
    def __init__(self, genes=None):
        self.genes = genes
        self.fitness = 0.0
        self.true_fitness = 0.0
        self.MAX_PHI = 360 ## Rotation about z-axis
        self.MAX_THETA = 180 ## Rotation about y-axis
        self.MAX_PSI = 360 ## Rotation about z-axis
        self.MAX_DELTA = 180 ## Initial cross-polarization angle
        
    
    def initialize(self):
        '''Initialize the genes of the horn antenna. 
        The genes are: [side_length, height, x_0, y_0, z_f, y_f, 
        beta, trpzd_length, trpzd_height]'''
        
        valid_design = False
        while valid_design == False:
            # Generate random values
            phi = round(random.uniform(0.0, self.MAX_PHI),4)
            theta = round(random.uniform(0.0, self.MAX_THETA),4)
            psi = round(random.uniform(0.0, self.MAX_PSI),4)
            delta = round(random.uniform(0.0, self.MAX_DELTA),4)

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
    
    
    ## MACHTAY 
    ## modify below to functions to read in the RCS from the .txt
    ## Evaluate fitness by reading a file
    ## This is where I want to have the script call the executable
    ## Then I want it to read the file it produces for the phrase
    ## "Reduced chi-squared" and find the RCS in there
#    def evaluate_fitness():
    def evaluate_fitness(self, comparison):
        '''Calculate the euclidean distance between the genes
        of the horn antenna and the comparison genes.'''
        
        """
        euclidean_distance = 0.0
        gene_count = len(self.genes)
        for i in range(gene_count):
            numerator = (self.genes[i] - comparison[i]) ** 2
            denominator = (self.genes[i] + comparison[i]) ** 2
            euclidean_distance += numerator / denominator
            
        normalized_distance = euclidean_distance / (2 * gene_count)
        
        normalized_distance = normalized_distance ** 0.5
        
        self.fitness = 1.0 - normalized_distance
        """

        fit_args = [str(self.genes[i]) for i in range(len(self.genes))]
        rcs, self.psis = run_fit_executable(fit_args)
				self.fitness = 1/rcs ## Makes lower RCS better!

    
    ## MACHTAY
    ## This looks like it reads in our file just fine
    ## So we make this read in as a fitness
    def save_as_comparison(self, filename):
        '''save the current genes as a comparison file.'''
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)
    
    
    def __str__(self) -> str:
        '''Return a string representation of the antenna's genes.'''
        return str(self.genes)
        
