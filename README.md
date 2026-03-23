# ALOHA_Protocols
Simulation and comparison of Slotted, Threshold, and Mini-slot Threshold ALOHA protocols.

## Overview
This project simulates and compares multiple ALOHA protocols, including:

- **Pure ALOHA (SA)**
- **Slotted ALOHA (TA)**
- **Threshold ALOHA**
- **Mini-slot Threshold ALOHA (MuMiSTA)** (simulation in progress)
- **EAF-MuMiSTA** (simulation not completed)

Objectives:
- Analyze the AAOI (Average Age of Information) performance of different protocols
- Compare success rates, collision probabilities, and efficiency
- Provide a simulation framework for future protocol optimization
  
## How to Run
1. Install a C/C++ compiler
2. Compile and run each file:
``gcc pure_aloha.c -o pure_aloha -lm``
``./pure_aloha``
3. Repeat for other files

## Current Progress
- Simulations completed for: Pure ALOHA, Slotted ALOHA, Threshold ALOHA
- MuMiSTA and EAF-MuMiSTA simulations in progress
- Computes AAOI for each device and network average AAOI

## Future Work
- Complete EAF-MuMiSTA simulation
- Optimize MuMiSTA and EAF-MuMiSTA parameters (mini-slot number, threshold)
- Compare protocol performance under different network sizes and traffic loads
- Visualize simulation results with plots

## Author
Yi-An, Yang

## References
- Ahmetoglu, M., Yavascan, O. T., & Uysal, E. (Year). *MiSTA: Threshold-ALOHA with Mini Slots*. Dept. of Electrical and Electronics Engineering, METU, Ankara, Turkey.
- Yavascan, O. T., & Uysal, E. (Year). *Analysis of Slotted ALOHA with an Age Threshold*. Dept. of Electrical and Electronics Engineering, METU, Ankara, Turkey.
