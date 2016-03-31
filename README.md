# micpower
This is a simplified program to read the energy power consumption of the Intel Xeon Phi Card based on the KNC architecture.
This program is intended to experiment the way how one can take energy measuments on the © Intel many integrated core architecture, in particular the Knights Corner product.
The code has been tested on Intel Xeon Phi (MIC) coprocessors 5110P with 60 cores @ 1.1 GHz provided
at LRZ (Leibniz Supercomputing Centre). More information about the sytem here: https://www.lrz.de/services/compute/supermuc/supermic/

# compile
To compile the code, run: 

make

on the host system. The intel compiler 16.0 is needed.

To run the code, run:

make run

The program will copy the executable file to the target machine (MIC) and will copy back
to the host the result file with the energy measures.
