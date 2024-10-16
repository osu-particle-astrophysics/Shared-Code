import sys
import copy
import pickle
import random
import csv

from pathlib import Path

import yaml
import numpy as np
from pathlib import Path

from horn_antenna import HornAntenna
#import bicone_antenna
#import hpol_antenna

class GA:
    def __init__(self, run_name, settingsfile='configs/settings.yaml', 
                 initialization=None, gen=None):
        self.run_name = run_name
        self.custom_init = initialization
        self.initialize_settings(settingsfile)
        self.run_dir = Path(self.settings["run_dir"])
        
        if gen is not None:
            self.generation = gen
        else:
            self.generation = 0
        
        self.population = []
        self.best_individual = None
        self.best_fitness = 0.0
        
        if self.settings["test_loop"]:
            self.comparison = np.array([])
            self.load_comparison()
            self.make_run_directory()
            self.initialize_tracker()
    
    
    ### Initialization ########################################################
    
    def initialize_settings(self, settingsfile):
        '''Initialize the settings from the settings file.'''
        settingspath = Path(settingsfile)
        if settingspath.exists():
            with open(settingspath, 'r') as file:
                settings = yaml.load(file, Loader=yaml.FullLoader)
        else:
            sys.exit('Settings file not found. Exiting.')
            
        if self.check_settings(settings):
            self.settings = settings
        else:
            sys.exit('Invalid settings. Exiting.')
    
    
    def check_settings(self, settings):
        '''Check if the settings are valid.'''
        if (settings['crossover_rate'] + settings['mutation_rate'] +
            settings['reproduction_rate']) > 1.0:
            print('Operator rates exceed 1.0.')
            return False
        if (settings['tournament_rate'] + settings['roulette_rate'] + 
            settings['rank_rate']) != 1.0:
            print('Selection rates do not sum to 1.0.')
            return False
        if settings['steady_state'] and settings['reproduction_rate'] != 0:
            print('Steady state and reproduction not compatible.')
            return False
        return True
    
    
    def initialize_population(self):
        '''Initialize the population of horn antennas.'''
        antenna_type = self.settings['a_type']
        if self.custom_init is None:
            for i in range(self.settings["npop"]):
                antenna = self.make_antenna(antenna_type)
                antenna.initialize()
                self.population.append(antenna)
        else:
            # load in the population from a file
            init_path = Path(f"initializations/{self.custom_init}.pkl")
            self.load_population(init_path)
    
    
    def load_comparison(self):
        '''Load the comparison genes from the comparison file.'''
        comparison_path = Path(f"comparisons/{self.settings['comparison_file']}")
        if comparison_path.exists():
            self.comparison = np.loadtxt(comparison_path)
        else:
            sys.exit('Comparison file not found. Exiting.')
    
    
    def make_run_directory(self):
        '''Create the run directory for the current run.'''
        self.run_dir.mkdir(parents=True, exist_ok=True)
        if self.settings["save_all_files"]:
            fitness_files = self.run_dir / "fitness_files"
            fitness_files.mkdir(parents=True, exist_ok=True)
            gene_files = self.run_dir / "gene_files"
            gene_files.mkdir(parents=True, exist_ok=True)
        
    
    def initialize_tracker(self):
        '''Initialize the tracker file for the run.'''
        tracker_path = self.run_dir / "tracker.csv"
        
        with open(tracker_path, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Generation", "Best Fitness", "Best Individual Genes"])
    
    
    def make_antenna(self, type, genes=None):
        '''Create an antenna object.'''
        if type == 'horn':
            return HornAntenna(genes)
        else:
            sys.exit('Invalid antenna type. Exiting.')
    
    
    ### Selection ############################################################
    
    def tournament_selection(self):
        '''Select a parent using tournament selection.'''
        
        # Select tournamentsize percentage of the population
        tournament_count = int(self.settings["tournament_size"] * self.settings["npop"])
        
        if tournament_count == 0:
            tournament_count = 1
        
        tournament = random.sample(self.population, tournament_count)
        
        # Find the best individual in the tournament 
        best_individual = max(tournament, key=lambda ind: ind.fitness)
        
        return best_individual
    
    
    def roulette_selection(self):
        '''Select a parent using roulette selection.'''
        
        # Calculate the total fitness of the population
        total_fitness = sum(individual.fitness for individual in self.population)
        
        # Calculate the probability of selection for each individual
        probabilities = [individual.fitness / total_fitness for individual in self.population]
        
        # Select an individual
        return self.get_indiv_from_prob(probabilities, self.population)
    
    
    def rank_selection(self):
        '''Select a parent using rank selection.'''
        
        # Sort the population by fitness
        sorted_population = sorted(self.population, key=lambda x: x.fitness)
        
        # Calculate the probability of selection for each individual
        probabilities = [i / len(self.population) for i in range(1, len(self.population) + 1)]
        
        # Select an individual
        return self.get_indiv_from_prob(probabilities, sorted_population)
    
    
    def get_indiv_from_prob(self, probabilities, population):
        '''Get an individual from a probability distribution.'''
        selection = random.uniform(0, 1)
        cumulative_probability = 0
        for probability, individual in zip(probabilities, population):
            cumulative_probability += probability
            if cumulative_probability > selection:
                return individual
    
    
    def selection(self, num_parents):
        '''Select parents from the population based on
        percentages.'''
        parents = []
        
        for i in range(num_parents):
            selection = random.uniform(0, 1)
            if selection < self.settings["tournament_rate"]:
                parents.append(self.tournament_selection())
            elif selection < self.settings["tournament_rate"] + self.settings["roulette_rate"]:
                parents.append(self.roulette_selection())
            else:
                parents.append(self.rank_selection())
        
        return parents
        
    
    def absolute_selection(self, num_parents):
        '''Select exactly the rate from each selection method.'''
        
        no_tournament = int(num_parents * self.settings["tournament_rate"])
        no_roulette = int(num_parents * self.settings["roulette_rate"])
        no_rank = int(num_parents - no_tournament - no_roulette)
        
        parents = []
        parents.extend(self.tournament_selection() for i in range(no_tournament))
        parents.extend(self.roulette_selection() for i in range(no_roulette))
        parents.extend(self.rank_selection() for i in range(no_rank))
        
        return parents
    
    
    ### Operators ############################################################
    
    def crossover(self, parent1, parent2):
        '''Crossover two parents to create two children.'''
        antenna_type = self.settings['a_type']
        
        valid_children = False
        cross_attempt = 0
        while not valid_children:
            child1_genes = []
            child2_genes = []
            
            # Crossover genes
            for gene_1, gene_2 in zip(parent1.genes, parent2.genes):
                coinflip = random.randint(0, 1)
                child1_genes.append(gene_1 if coinflip == 0 else gene_2)
                child2_genes.append(gene_2 if coinflip == 0 else gene_1)
                
            child1 = self.make_antenna(antenna_type, child1_genes)
            child2 = self.make_antenna(antenna_type, child2_genes)
            
            # Check if children are valid
            valid_children = child1.check_genes() and child2.check_genes()
            
            cross_attempt += 1
            if cross_attempt > 100:
                self.print("Crossover Failed")
                return parent1, parent2
            
        return child1, child2
                
    
    def mutation(self, individual):
        '''Mutate a randomly selected gene across a gaussian distribution.'''
        chosen_gene_index = random.randrange(len(individual.genes))
        chosen_gene = individual.genes[chosen_gene_index]
        new_indiv = copy.deepcopy(individual)
            
        
        valid_antenna = False
        while not valid_antenna:
            new_gene = random.gauss(chosen_gene, chosen_gene * self.settings["sigma"])
            new_indiv.genes[chosen_gene_index] = new_gene
            valid_antenna = new_indiv.check_genes()
            
        return new_indiv
    
    
    def reproduction(individual):
        '''Asexual Reproduction.'''
        return individual
    
    
    def injection(self):
        '''Inject a new individual into the population.'''

        individual = self.make_antenna(self.settings['a_type'])
        individual.initialize()
        
        return individual
    
    
    ### Write/ReadFunctions ##################################################
    
    def write_population_genes(self, filepath=None):
        '''Write the genes of the population to the run directory.'''
        if filepath is None:
            filepath = self.run_dir / "Generation_Data" / f"{self.generation}_generationDNA.csv"

        with open(filepath, "w") as file:
            writer = csv.writer(file)
            for individual in self.population:
                writer.writerow(individual.genes)
    
    
    def write_population_fitness(self, filepath=None):
        '''Write the fitness of the population to the run directory.'''
        if filepath is None:
            filepath = self.run_dir / "Generation_Data" / f"{self.generation}_fitnessScores.csv"   
        np.savetxt(filepath, [individual.fitness for individual in self.population])
    
    
    def save_population(self, filepath=None):
        '''Save the antenna objects to a pickle file.'''
        if filepath is None:
            filepath = self.run_dir / "Generation_Data" / f"{self.generation}_population.pkl"
        with open(filepath, 'wb') as file:
            pickle.dump(self.population, file)
    
    
    def save_ga(self, filepath=None):
        '''Save the GA object to a pickle file.'''
        if filepath is None:
            filepath = self.run_dir / "GA.pkl"
        with open(filepath, 'wb') as file:
            pickle.dump(self, file)
    
            
    def load_population(self, filepath):
        '''Load the population from a pickle file.'''
        with open(filepath, 'rb') as file:
            self.population = pickle.load(file)
    
    
    def load_fitness(self, filepath):
        '''Load the fitness of the population from a csv file.'''
        fitness_list = np.loadtxt(filepath)
        for individual, fitness in zip(self.population, fitness_list):
            individual.fitness = fitness
            
            
    def save_to_tracker(self):
        '''Append the current best to the tracker file.'''
        filepath = self.run_dir / "tracker.csv"
        with open(filepath, 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([self.generation-1, self.best_fitness, self.best_individual.genes])
    
    
    def save_files(self):
        '''Save current generation files.'''
        if self.settings["test_loop"]:
            self.save_to_tracker()
            self.evaluate_population()
                
        if self.settings["save_all_files"]:
            self.save_population()
            self.write_population_genes()
            #self.write_population_fitness()
            

    def print_stats(self):
        print(f"Generation: {self.generation}")
        print(f"Best Fitness: {self.best_fitness}")
        print(f"Best Individual: {self.best_individual.genes}")
        
        
    def print(self, *args, **kwargs):
        if self.settings["verbose"]:
            print(*args, **kwargs)
    
    
    ### Generational Methods #################################################
    
    def evaluate_population(self):
        '''Evaluate the fitness of the entire population.'''
        for individual in self.population:
            individual.evaluate_fitness(self.comparison)
            if individual.fitness > self.best_fitness:
                self.best_fitness = individual.fitness
                self.best_individual = individual
    
    
    def get_operator_numbers(self):
        '''Get the integer number of each operator from percentage
        size and population size.'''
        mutation_no = int(self.settings["mutation_rate"] * self.settings["npop"])
        crossover_no = int(self.settings["crossover_rate"] * self.settings["npop"])
        reproduction_no = int(self.settings["reproduction_rate"] * self.settings["npop"])
        
        if crossover_no % 2 != 0:
            crossover_no += 1
        
        if mutation_no + crossover_no + reproduction_no < self.settings["npop"]:
            injection_no = self.settings["npop"] - mutation_no - crossover_no - reproduction_no
        else:
            injection_no = 0
            reproduction_no = self.settings["npop"] - mutation_no - crossover_no
            
        return [crossover_no, mutation_no, reproduction_no, injection_no]
    
    
    ### SSGA Methods #########################################################
    
    def choose_operator(self):
        '''Choose an operator from the operator set of 
        REPRODUCTION, CROSSOVER, MUTATION, INJECTION.'''
        # choose a random number from 0 to 1
        choice = random.uniform(0, 1)
        
        limit = self.settings["crossover_rate"]
        if choice <= limit:
            return "crossover"
        
        limit += self.settings["mutation_rate"]
        if choice <= limit:
            return "mutation"
        
        limit += self.settings["reproduction_rate"]
        if choice <= limit:
            return "reproduction"
        
        return "injection"    

    
    def create_individual(self, operator, parents):
        '''Create an individual from the given operator and parents.'''
        
        if operator == "crossover":
            new_indiv = self.crossover(parents[0], parents[1])[0]
        elif operator == "mutation":
            new_indiv = self.mutation(parents[0])
        elif operator == "injection":
            new_indiv = self.injection()
        else:
            new_indiv = parents[0]
        
        return copy.deepcopy(new_indiv)
    
    
    def get_num_parents(self, operator):
        '''Get the number of parents for a SSGA operator.'''
        return 2 if operator == "crossover" else 1
    
    
    def replace_individual(self, new_indiv):
        '''Choose an individual in the population to replace'''
        if self.settings["replacement_method"] == "random":
            index = random.randrange(len(self.population))
            self.population[index] = new_indiv
        else:
            sys.exit('Invalid replacement method. Exiting.')
    
    
    ### Constraint Functions #################################################
    
    def test_diverse(self, new_indiv, new_population=None):
        '''Test if an individual is identical to any
        individuals currently in the population.'''
        for individual in self.population:
            if new_indiv.genes == individual.genes:
                return False
        
        if new_population is not None:
            for individual in new_population:
                if new_indiv.genes == individual.genes:
                    return False
        
        return True
    
    
    ### Main Loop Functions #########################################################
    
    def advance_generation(self):
        '''Advance the generation of the population.'''
        
        # check if initial generation
        if self.generation == 0:
            self.initialize_population()
            self.save_files()
            self.generation += 1
            return
        
        if self.settings["steady_state"]:
            self.advance_generation_steady_state()
        else:
            self.advance_generation_generational()
        
        self.save_files()
        self.generation += 1
        return
    
    
    def advance_generation_steady_state(self):
        '''Advance the state of the GA in a steady state manner,
        creating new individuals one by one.'''
        
        for i in range(self.settings["npop"]):
            
            # Create a new antenna
            valid_individual = False
            while not valid_individual:
                # Create a new individual
                
                operator = self.choose_operator()
                num_parents = self.get_num_parents(operator)
                parents = self.selection(num_parents)
                
                new_indiv = self.create_individual(operator, parents)
                
                # Check if the antenna is unique if required
                if self.settings["forced_diversity"]:
                    valid_individual = self.test_diverse(new_indiv)
                else:
                    valid_individual = True
                
            # Test Fitness and replace an individual
            new_indiv.evaluate_fitness(self.comparison)
            self.replace_individual(new_indiv)
            
            if new_indiv.fitness > self.best_fitness:
                self.best_fitness = new_indiv.fitness
                self.best_individual = new_indiv
    
    
    def advance_generation_generational(self):
        '''Advance to the next generation of the Generational GA.'''
        new_population = []
        operator_nos = self.get_operator_numbers()
        
        self.print("Crossover")
        parents = self.absolute_selection(operator_nos[0]*2)
        for i in range(int(operator_nos[0]/2)):  
            # Create children
            valid_children = False
            diverse_attempt = 0
            
            while not valid_children:
                parent1_index = random.randrange(len(parents))
                parent2_index = random.randrange(len(parents))
                parent_attempt = 0
                while parents[parent1_index].genes == parents[parent2_index].genes:
                    parent2_index = random.randrange(len(parents))
                    parent_attempt += 1
                    if parent_attempt > 100:
                        diverse_attempt += 100
                        break

                children = self.crossover(parents[parent1_index], parents[parent2_index])
                
                if self.settings["forced_diversity"]:
                    valid_children = (self.test_diverse(children[0], new_population) and
                                      self.test_diverse(children[1], new_population))
                else:
                    valid_children = True
                
                diverse_attempt += 1
                
                if diverse_attempt > 100:
                    self.print("Crossover Failed, adding rest to mutation")
                    operator_nos[1] += (operator_nos[0] - i) * 2
                    break
            
            else:
                # remove the parents from the list
                parents.pop(parent1_index)
                if parent1_index < parent2_index:
                    parents.pop(parent2_index - 1)
                else:
                    parents.pop(parent2_index)
                
                # Add the children to the new population
                new_population.extend(children)
                continue
            
            break  

        self.print("Mutation")
        parents = self.absolute_selection(operator_nos[1])
        for i in range(operator_nos[1]):
            valid_individual = False
            while not valid_individual:
                new_indiv = self.mutation(parents[i])
                
                if self.settings["forced_diversity"]:
                    valid_individual = self.test_diverse(new_indiv, new_population)
                else:
                    valid_individual = True
            
            new_population.append(new_indiv)
        
        self.print("Reproduction")
        parents = self.absolute_selection(operator_nos[2])
        for i in range(operator_nos[2]):
            new_population.append(copy.deepcopy(parents[i]))
        
        self.print("Injection")
        for i in range(operator_nos[3]):
            new_population.append(self.injection())
            
        self.print("Evaluation")
        self.population = new_population
        
        if self.settings["test_loop"]:
            self.evaluate_population()
        
    
    def run(self):
        '''Run the genetic algorithm test loop'''
        print("Running Genetic Algorithm...")
        for i in range(self.settings["ngens"]):
            self.advance_generation()
            if self.settings["verbose"]:
                self.print_stats()
        print("Genetic Algorithm Complete")
    