# PRM_SimpleG4PairProduction
A G4 study on the kinematics of pair productions in the AMBER PRM setup. Analyses kinematic quantities and correlations of pair production processes (through muons and photons) in a Geant4 enviroment based on the 2022 AMBER proton radius measurement.

Based on https://github.com/cdreisbach/PRM_SimpleG4.

# PRM_SimpleG4
Simple G4 simulation for testing components of the PRM setup. Can serve as a basis for several studies.

## Installation
Simply usage of ./bootstrap
- will create a build/ directory
- will execute cmake (cmake3)
- will execute make

## Usage
The executable will be created in the build/bin directory:
   - build/bin/Simulation
 
Controls can be made for instance via the macros located in simulation/macros/:
- run.mac (used for batch mode)
- init_vis.mac (used for visualization)
- vis.mac (used in init_vis.mac as example)

## Visualization
Example:
- ./Simulation
- this will make use of the init_vis.mac

## Batch mode
Data can be generated via usage of the both commands.
- ./Simulation outputFile.root
- ./Simulation outputFile.root ../simulation/macros/run.mac

The output is a *.root file containing simple information for single steps. 



