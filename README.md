# Micpower
## Description
This is a simplified program to read the energy power consumption of the Intel Xeon Phi Card based on the KNC architecture.
This program is intended to experiment the way how one can take energy measuments on the Intel® many integrated core architecture (MIC), in particular the Knights Corner product.
The code has been tested on Intel Xeon Phi (MIC) coprocessors 5110P with 60 cores @ 1.1 GHz provided
at LRZ (Leibniz Supercomputing Centre). More information about the system here: [Supermic](https://www.lrz.de/services/compute/supermuc/supermic/). This code has been developed during the Intel® Parallel Computing Center [IPCC](https://software.intel.com/articles/intel-parallel-computing-center-at-leibniz-supercomputing-centre-and-technische-universit-t) initiative at Leibniz Supercomputing.

## Requirements
- 64-bit Intel system for compiling
- Intel Xeon Phi 

## Compilation and Test
After dowloading the code and running `make`, the code is ready to be tested.
On the host system `make run` will run the example code.
The program will copy the executable file to the target machine (MIC) and will copy back
to the host the result file with the energy measures.

## References
https://software.intel.com/en-us/articles/measuring-power-on-intel-xeon-phi-product-family-devices
