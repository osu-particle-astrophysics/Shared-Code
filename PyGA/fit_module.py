# fit_module.py

import subprocess
import os
import sys

def run_fit_executable(script_args):
    """
    Runs the fit.exe executable with the given arguments and parses the output.

    Parameters:
        script_args (list): A list of arguments to pass to the executable.

    Returns:
        tuple: A tuple containing:
            - last_word (str): The last word from the second-to-last line of the output.
            - psi_median_models (list): A list of lists, each containing elements from
                                        'Elements of psi_median_model:' sections.
    """
    # Command to run your executable
    command = ["./fit.exe"] + script_args  # Replace with your executable's path

    # Run the process and capture the output
    result = subprocess.run(
        command,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,  # For Python 3.6 compatibility
        cwd="/users/PAS0654/machtay1/Alan_Birefringence/birefringence_2/birefringence"
    )

    # Check if the process was successful
    if result.returncode != 0:
        print("Error executing the command:")
        print(result.stderr)
        return None, None
    else:
        # Get the output
        output = result.stdout

        # Split the output into lines
        lines = output.strip().split('\n')

        # Extract the last word from the second-to-last line
        last_word = None
        if len(lines) >= 2:
            second_to_last_line = lines[-2]
            words = second_to_last_line.strip().split()
            if words:
                last_word = second_to_last_line  # You can change this to words[-1] if you need just the last word
                # print("Last word in second-to-last line:", second_to_last_line)
            else:
                print("Second-to-last line is empty.")
        else:
            print("The output has less than two lines.")

        # Initialize a list to hold all psi_median_model elements
        psi_median_models = []

        # Search for all occurrences of "Elements of psi_median_model:"
        for idx, line in enumerate(lines):
            if "Elements of psi_median_model:" in line:
                # Check if there is a line after this line
                if idx + 1 < len(lines):
                    next_line = lines[idx + 1]
                    # Remove the final character if it's a comma
                    if next_line.endswith(','):
                        next_line = next_line[:-1]
                    # Split the line into elements
                    elements_str = next_line.strip().split()
                    # Convert elements to floats, removing any trailing commas
                    try:
                        elements = [float(elem.strip(',')) for elem in elements_str]
                    except ValueError as e:
                        print(f"Error converting elements to float at occurrence {len(psi_median_models)+1}: {e}")
                        elements = []
                    # Store the elements in the list
                    psi_median_models.append(elements)
                else:
                    print(f"No line found after 'Elements of psi_median_model:' at line {idx}")
                    # Continue to the next occurrence
                    continue

        return last_word, psi_median_models

