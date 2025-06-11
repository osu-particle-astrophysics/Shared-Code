from pathlib import Path
import numpy as np
import yaml
import sys

class VPOLAntenna:
    def __init__(self, settings, genes=None):
        self.settings = settings
        self.rng_seed = int(self.settings["run"]["rng_seed"])
        self.rng = np.random.default_rng(self.rng_seed)
        self.a_cfg = self.settings["antennas"]["vpol"]
        self.genes = genes
        self.fitness = 0.0

        # Limits based on configuration
        self._set_param_limits()

    def _set_param_limits(self):
        self.min_rad, self.max_rad = 0.0, 7.5
        self.min_length, self.max_length = 37.5, 140.0

        if self.a_cfg['curved'] == 0:
            self.min_theta = 0.0
            self.max_theta = np.arctan(self.max_rad / self.min_length)
            self.min_separation = self.max_separation = 2.5
        else:
            self.min_a, self.max_a = -1, 1
            self.min_b, self.max_b = -1, 1

    def _rand(self, low, high):
        return self.rng.uniform(low, high)

    def _enforce_symmetry(self, value1, value2, enforce):
        return value1 if enforce == 0 else value2

    def initialize(self):
        if self.a_cfg['curved'] == 0:
            self._initialize_straight()
        else:
            self._initialize_curved()

    def _initialize_straight(self):
        # Base section
        radius = self._rand(self.min_rad, self.max_rad)
        length = self._rand(self.min_length, self.max_length)
        theta = self._rand(self.min_theta, self.max_theta)

        if self.a_cfg['nsections'] == 1:
            self.genes = np.array([radius, length, theta])
        else:
            separation = self._rand(self.min_separation, self.max_separation)
            radius1 = self._enforce_symmetry(radius, self._rand(self.min_rad, self.max_rad), self.a_cfg['radius'])
            length1 = self._enforce_symmetry(length, self._rand(self.min_length, self.max_length), self.a_cfg['length'])
            theta1 = self._enforce_symmetry(theta, self._rand(self.min_theta, self.max_theta), self.a_cfg['angle'])
            self.genes = np.array([radius, length, theta, separation, radius1, length1, theta1])

    def _initialize_curved(self):
        radius = self._rand(self.min_rad, self.max_rad)
        length = self._rand(self.min_length, self.max_length)
        a = self._rand(self.min_a, self.max_a)
        b = self._rand(self.min_b, self.max_b)

        radius1 = self._enforce_symmetry(radius, self._rand(self.min_rad, self.max_rad), self.a_cfg['radius'])
        length1 = self._enforce_symmetry(length, self._rand(self.min_length, self.max_length), self.a_cfg['length'])
        a1 = self._enforce_symmetry(a, self._rand(self.min_a, self.max_a), self.a_cfg['a'])
        b1 = self._enforce_symmetry(b, self._rand(self.min_b, self.max_b), self.a_cfg['b'])

        self.genes = np.array([radius, length, a, b, radius1, length1, a1, b1])

    def save_as_comparison(self, filename):
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)

    def __str__(self) -> str:
        return str(self.genes)
