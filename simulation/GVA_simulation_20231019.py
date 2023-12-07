#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 19 07:24:10 2023

@author: Eric J. South
Dunlop Lab

This module simulates the Geometric Viability Assay (GVA) using a conical geometry 
to estimate CFU/mL concentrations. By leveraging the non-uniform probability of 
colony formation along the cone's axis, the module approximates colony density 
without the need to count all colonies.
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches


def pdf(x, h):
    """
    Probability density function (PDF) representing the probability of a colony 
    forming at a certain height `x` along the cone's axis. The probability 
    increases with height due to the increased space (cross-sectional area) 
    available. Notably, this PDF only dictates the vertical (height) distribution 
    and does not influence the radial distribution at a given height.
    
    Parameters:
    - x: The height along the cone's axis.
    - h: The total height of the cone.

    Returns:
    - Probability of a colony forming at height `x`.
    """
    return 3 * x**2 / h**3


def radius_at_height(y, h, max_radius):
    """
    Calculate the radius of the cone's cross-sectional circle at a given height `y`.

    Parameters:
    - y: The height at which the radius is to be determined.
    - h: The total height of the cone.
    - max_radius: The maximum radius of the cone (at its base).

    Returns:
    - Radius of the cone at height `y`.
    """
    return y * max_radius / h


def simulate_colonies(h, max_radius, num_colonies):
    """
    Simulate the distribution of colonies inside the cone. The height of the colonies
    is determined by the PDF, respecting the bias introduced by the cone's geometry. 
    Within a selected height, the radial distribution is uniform since the PDF only
    provides a bias along the height and not radially.

    Steps:
    1. Generate discrete sampling points for potential heights within the cone.
    2. Compute probabilities for each of these heights using the PDF.
    3. Normalize these probabilities.
    4. Randomly sample heights from the discrete points based on these probabilities.

    Parameters:
    - h: The total height of the cone.
    - max_radius: The maximum radius of the cone.
    - num_colonies: The number of colonies to simulate.

    Returns:
    - x_sampled: x-coordinates of the simulated colonies.
    - y_sampled: y-coordinates (heights) of the simulated colonies.
    """
    y_positions = np.linspace(0, h, 1000)
    probabilities = pdf(y_positions, h)
    y_sampled = np.random.choice(
        y_positions, 
        size=num_colonies, 
        p=probabilities/np.sum(probabilities))
    
    x_sampled = []
    for y in y_sampled:
        r = radius_at_height(y, h, max_radius)
        angle = np.random.uniform(0, 2 * np.pi)
        x_val = r * np.cos(angle)  # Convert radial position to x-coordinate
        x_sampled.append(x_val)
        
    return np.array(x_sampled), y_sampled


def plot_pdf(h, epsilon=1e-10):
    """
    Plot the logarithm of the PDF for a range of heights within the cone.
    
    Parameters:
    - h: The total height of the cone.
    - epsilon: A small value added to probabilities to avoid log(0) issue. Default is 1e-10.
    """
    # Generate 1000 heights linearly spaced between 0 and h
    y_positions = np.linspace(0, h, 1000)
    
    # Compute the PDF values for these heights
    probabilities = pdf(y_positions, h) + epsilon  # Add small constant to probabilities
    
    # Plot the logarithm of the probabilities against the discrete values
    plt.figure(figsize=(8, 6))
    plt.plot(y_positions, np.log10(probabilities), label='log10(PDF)', color='blue')
    plt.title('Logarithm of PDF vs Heights in Cone')
    plt.xlabel('Height in Cone (from tip to base)')
    plt.ylabel('log10(PDF)')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()


def plot_colonies_in_cone(x_positions, y_positions, h, max_radius):
    """
    Plot the distribution of colonies within the cone's cross-section.
    
    Parameters:
    - x_positions: x-coordinates of the simulated colonies.
    - y_positions: y-coordinates (heights) of the simulated colonies.
    - h: The total height of the cone.
    - max_radius: The maximum radius of the cone.
    """
    fig, ax = plt.subplots(figsize=(8, 8))
    
    # Drawing the cone
    cone = patches.Polygon([[0,0], [max_radius, h], [-max_radius, h]], closed=True, alpha=0.2)
    ax.add_patch(cone)

    # Plotting the sampled colonies
    ax.scatter(x_positions, y_positions, c='r', s=10, label='Sampled colonies')
    ax.set_xlim([-max_radius-1, max_radius+1])
    ax.set_ylim([0, h+1])
    ax.set_title('Simulated Colony Distributions in Cone Cross-section')
    ax.set_xlabel('Width of Cone')
    ax.set_ylabel('Height of Cone')
    ax.legend()
    
    plt.tight_layout()
    plt.show()


def cone_volume(h, max_radius):
    """
    Calculate the volume of the cone. The volume of a cone is determined by the 
    formula V = (1/3) * pi * r^2 * h, where 'r' is the radius of the cone's base 
    and 'h' is its height. This function computes the volume based on the provided 
    height and maximum radius of the cone. Knowing the volume is essential when 
    trying to estimate the concentration of colonies in the entire medium, as it 
    allows us to extrapolate from a sampled subsection.

    Parameters:
    - h: The total height of the cone.
    - max_radius: The maximum radius of the cone.

    Returns:
    - Volume of the cone.
    """
    return (1/3) * np.pi * max_radius**2 * h


def estimate_cfus(x_positions, y_positions, h, max_radius, volume_in_ml):
    """
    Estimate the CFU/mL given the positions of simulated colonies within a conical geometry.

    In a cone, the probability of a colony forming is not uniform; instead, it's influenced
    by the cone's shape and is determined by a colony's distance from the cone's tip. 
    The non-uniform distribution is described by the probability density function (PDF):

    PDF(x) = (3 * x^2) / h^3

    The methodology followed is:
        - Identify the positions of the first (x1) and last (x2) colonies within the 
          sampled volume (or counted sub-volume).
          
        - Calculate the integral of the PDF between these two heights. This integral 
          quantifies the expected fraction or probability mass of colonies between 
          these heights considering the conical shape.
          
        - The CFUs/mL is then derived by dividing the actual number of colonies 
          observed between these heights by the product of this integral value and 
          the specified cone volume in milliliters. It provides an extrapolation 
          of the local colony density to the entire cone volume.

    Importantly, the radial position of a colony within the cone does not influence
    this probability; only its height (or distance from the tip) does.

    Parameters:
    - x_positions: x-coordinates of the simulated colonies.
    - y_positions: y-coordinates (heights) of the simulated colonies.
    - h: Total height of the cone.
    - max_radius: Maximum radius of the cone.
    - volume_in_ml: User-defined volume of the cone in milliliters.

    Returns:
    - Estimated CFUs/mL.
    """
    x1, x2 = np.min(y_positions), np.max(y_positions)  # Getting the positions of the first and last colonies
    
    # Computing the integral of the PDF between x1 and x2
    integral_value = (x2**3 - x1**3) / h**3

    # Estimating the CFUs/mL
    cfus_per_ml = len(x_positions) / (integral_value * volume_in_ml)
    
    return cfus_per_ml


# Sample usage
h = 10  # example height of the cone
max_radius = .25  # example max radius of the cone
num_colonies = 500 # tweak and see how CFUs/mL changes
tip_volume = 1.2 # volume of liquid in our simulated tip (mLs)

x_positions, y_positions = simulate_colonies(h, max_radius, num_colonies)

# Visualization
plot_pdf(h)
plot_colonies_in_cone(x_positions, y_positions, h, max_radius)

# Estimate and print the CFUs/mL
estimated_cfus = estimate_cfus(x_positions, y_positions, h, max_radius, volume_in_ml=tip_volume)
print(f"Estimated CFUs/mL: {estimated_cfus:.2f}")



if __name__ == "__main__":
    simulate_colonies(10, 5, 1000)
    # main()