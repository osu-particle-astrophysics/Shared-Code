from pathlib import Path
import numpy as np

class AraAntennas:
    def __init__(self, settings, genes=None):
        self.settings = settings
        self.antenna_type = settings["antenna_type"].lower()  # "vpol" or "hpol"
        self.rng_seed = int(settings["run"]["rng_seed"])
        self.rng = np.random.default_rng(self.rng_seed)
        self.genes = genes
        self.fitness = 0.0

        if self.antenna_type == "vpol":
            self.a_cfg = self.settings["antennas"]["vpol"]
            self._set_vpol_limits()
        elif self.antenna_type == "hpol":
            self._set_hpol_limits()
        else:
            raise ValueError(f"Unsupported antenna_type: {self.antenna_type}")

    # ----- Initialization Helpers -----

    def _set_vpol_limits(self):
        self.min_rad, self.max_rad = 0.0, 7.5
        self.min_length, self.max_length = 37.5, 140.0
        if self.a_cfg["curved"] == 0:
            self.min_theta = 0.0
            self.max_theta = np.arctan(self.max_rad / self.min_length)
            self.min_separation = self.max_separation = 2.5
        else:
            self.min_a, self.max_a = -1, 1
            self.min_b, self.max_b = -1, 1

    def _set_hpol_limits(self):
        self.hpol_limits = {
            "num_plates": (4.0, 4.0),
            "radius": (0.5, 10.0),
            "arc_length_plate": (0.5, 10.0),
            "height": (0.5, 10.0),
            "ferrite_height": (1.0, 12.0),
            "ferrite_radius": (0.5, 3.0),
        }

    def _rand(self, low, high):
        return self.rng.uniform(low, high)

    def _enforce_symmetry(self, val1, val2, enforce):
        return val1 if enforce == 0 else val2

    # ----- Initialization -----

    def initialize(self):
        if self.antenna_type == "vpol":
            self._initialize_vpol()
        elif self.antenna_type == "hpol":
            self._initialize_hpol()

    def _initialize_vpol(self):
        if self.a_cfg["curved"] == 0:
            self._initialize_vpol_straight()
        else:
            self._initialize_vpol_curved()

    def _initialize_vpol_straight(self):
        radius = self._rand(self.min_rad, self.max_rad)
        length = self._rand(self.min_length, self.max_length)
        theta = self._rand(self.min_theta, self.max_theta)

        if self.a_cfg["nsections"] == 1:
            self.genes = np.array([radius, length, theta])
        else:
            sep = self._rand(self.min_separation, self.max_separation)
            radius1 = self._enforce_symmetry(radius, self._rand(self.min_rad, self.max_rad), self.a_cfg["radius"])
            length1 = self._enforce_symmetry(length, self._rand(self.min_length, self.max_length), self.a_cfg["length"])
            theta1 = self._enforce_symmetry(theta, self._rand(self.min_theta, self.max_theta), self.a_cfg["angle"])
            self.genes = np.array([radius, length, theta, sep, radius1, length1, theta1])

    def _initialize_vpol_curved(self):
        radius = self._rand(self.min_rad, self.max_rad)
        length = self._rand(self.min_length, self.max_length)
        a = self._rand(self.min_a, self.max_a)
        b = self._rand(self.min_b, self.max_b)

        radius1 = self._enforce_symmetry(radius, self._rand(self.min_rad, self.max_rad), self.a_cfg["radius"])
        length1 = self._enforce_symmetry(length, self._rand(self.min_length, self.max_length), self.a_cfg["length"])
        a1 = self._enforce_symmetry(a, self._rand(self.min_a, self.max_a), self.a_cfg["a"])
        b1 = self._enforce_symmetry(b, self._rand(self.min_b, self.max_b), self.a_cfg["b"])

        self.genes = np.array([radius, length, a, b, radius1, length1, a1, b1])

    def _initialize_hpol(self):
        self.genes = np.array([
            self._rand(*self.hpol_limits["num_plates"]),
            self._rand(*self.hpol_limits["radius"]),
            self._rand(*self.hpol_limits["arc_length_plate"]),
            self._rand(*self.hpol_limits["height"]),
            self._rand(*self.hpol_limits["ferrite_height"]),
            self._rand(*self.hpol_limits["ferrite_radius"]),
        ])

    # ----- Other Methods -----

    def check_genes(self):
        if self.antenna_type != "hpol":
            raise NotImplementedError("check_genes is only implemented for HPOL")
        keys = list(self.hpol_limits.keys())
        return all(
            self.hpol_limits[k][0] <= val <= self.hpol_limits[k][1]
            for k, val in zip(keys, self.genes)
        )

    def save_as_comparison(self, filename):
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)

    def __str__(self):
        return str(self.genes)
