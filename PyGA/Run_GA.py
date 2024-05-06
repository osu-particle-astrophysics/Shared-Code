'''Run the genetic algorithm for a generation'''
import argparse

from pathlib import Path

from GA import GA

def parse_args():
    parser = argparse.ArgumentParser(description='Run the genetic algorithm')
    parser.add_argument("run_name", type=str, help='Name of the run')
    parser.add_argument("workingdir", type=Path, help='Home Working Directory')
    parser.add_argument("gen", type=int, help="Generation number to start from")
    return parser.parse_args()


def main(args):
    '''Create antennas for the new generation'''
    # Create path variables
    last_gen = args.gen - 1
    rundir = args.workingdir / "Run_Outputs" / args.run_name
    poppath = rundir / "Generation_Data" / f"{last_gen}_population.pkl"
    fitpath = rundir / "Generation_Data" / f"{last_gen}_fitnessScores.csv"
    
    # Create the GA object
    ga = GA(args.run_name, 
            settingsfile=rundir / "settings.yaml",
            gen=args.gen)
    
    # Load the population and fitness scores
    if args.gen != 0:
        ga.load_population(poppath)
        ga.load_fitness(fitpath)
        
    # Run the genetic algorithm
    ga.advance_generation()
    

if __name__ == '__main__':
    args = parse_args()
    main(args)
