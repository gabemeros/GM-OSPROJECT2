# GM-OSPROJECT2
Bankers-Algorithim Assignment for CS33211

This Assignment implements the Bankers ALgoithim to avoid deadlock and allocate resources for proccesses. Source code includes inlined comments
to help navigate the code. Takes input from "input.txt", which is formatted with no spaces and commas seperating the rows of matricies. File data is read 
into 3 vectors, all for allocated resources, max for the maximum resources and ava for the available resources list. The program iterates through each process,
determining if their is a position in the sequence in which the process will finish and its needed resources will be found through iteration. The program iterates through all finished processes and then though all points in the finish arrary, and checks if they were finished. If a process is not finished, the program will
print "Sequence is unsafe". 

Safe Sequence is:
P1 TO P2 TO P4 TO P0 TO P2
