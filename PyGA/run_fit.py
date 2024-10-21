## Imports
import argparse
import pandas as pd
import numpy as np
from pathlib import Path

## Modules
import fit_module

## Args
def parse_args():
    parser = argparse.ArgumentParser(description='Run the genetic algorithm')
    parser.add_argument("run_dir", type=str, help='Name of the run')
    parser.add_argument("gen", type=Path, help='Home Working Directory')
    parser.add_argument("ind", type=int, help="Generation number to start from")
    return parser.parse_args()

## Main
def main(args):
    ## Read in genes and append remaining parameters for fitting script
    fit_args = fit_module.read_genes(args.run_dir, args.gen, args.ind)
    fit_args.append('1')
    fit_args.append('0')
    fit_args.append('4')

    ## Run the birefringence script to get RCS and psis
    fitness, psi_models, chi_squareds = fit_module.run_fit_executable(fit_args)
    print("fitness score: ", fitness)
    fit_module.write_results(args.run_dir, args.gen, args.ind, fitness, psi_models, chi_squareds)


if __name__ == '__main__':
    args = parse_args()
    main(args)
