CXX = icpc
CXXFLAGS = -std=c++11 -O2 -pthread -qopenmp 
MICFLAGS = $(CXXFLAGS) -mmic

OBJECTS = main.o micpower.o

EXE = power-mic
CXX = icpc

.SUFFIXES: .o .cpp

all: $(EXE) help

%-mic: $(OBJECTS)
	$(info )
	$(info Linking process:)
	$(CXX) $(MICFLAGS) -o $@ $(OBJECTS)

.cpp.o:
	$(info )
	$(info Compiling the example code for power measurements:)
	$(CXX) -c $(MICFLAGS) -o "$@" "$<"

help:
	$(info )
	$(info TO EXECUTE THE APPLICATION: )
	$(info "make run" to run the application on the coprocessor)
	$(info )

run: power-mic
	scp power-mic $(HOST)-mic0:~/
	ssh $(HOST)-mic0 OMP_NUM_THREADS=60 ./power-mic
	scp $(HOST)-mic0:~/mic_energy.log .

clean: 
	rm -f $(OBJECTS) $(EXE) 
