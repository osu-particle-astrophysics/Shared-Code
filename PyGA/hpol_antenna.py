from pathlib import Path
import numpy as np

class HPOLAntenna:
    def __init__(self, settings, genes=None):
        self.settings = settings
        self.rng_seed = int(self.settings["run"]["rng_seed"])
        self.rng = np.random.default_rng(self.rng_seed)
        self.genes = genes
        self.fitness = 0.0

        # Parameter limits
        self.limits = {
            "num_plates": (4.0, 4.0),
            "radius": (0.5, 10.0),
            "arc_length_plate": (0.5, 10.0),
            "height": (0.5, 10.0),
            "ferrite_height": (1.0, 12.0),
            "ferrite_radius": (0.5, 3.0)
        }

    def _rand(self, param):
        """Get a random value for a given parameter name."""
        low, high = self.limits[param]
        return self.rng.uniform(low, high)

    def initialize(self):
        """Randomly initialize genes for the HPOL antenna."""
        self.genes = [
            self._rand("num_plates"),
            self._rand("radius"),
            self._rand("arc_length_plate"),
            self._rand("height"),
            self._rand("ferrite_height"),
            self._rand("ferrite_radius")
        ]

    def save_as_comparison(self, filename):
        """Save current genes to a comparison file."""
        filepath = Path(f"comparisons/{filename}.txt")
        np.savetxt(filepath, self.genes)

    def check_genes(self):
        """Return True if genes are within allowed parameter ranges."""
        keys = [
            "num_plates", "radius", "arc_length_plate",
            "height", "ferrite_height", "ferrite_radius"
        ]
        return all(
            self.limits[key][0] <= val <= self.limits[key][1]
            for key, val in zip(keys, self.genes)
        )

    def __str__(self):
        return str(self.genes)
