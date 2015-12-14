cat ProfileArea | cut --delim=' ' --f=1-1 > ProfileArea_energy
cat ProfileArea | cut --delim=' ' --f=2-2 > ProfileArea_area
FileDivide ProfileArea_area ProfileArea_energy ProfileArea_AreaOverEnergy

