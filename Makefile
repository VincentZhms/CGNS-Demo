################################################################################
ccomp = g++ -Wall -O3 -g
CGNS_ROOT = /opt/cgns
HDF5_ROOT = /opt/hdf5
lib_flag = -L$(CGNS_ROOT)/lib -L$(HDF5_ROOT)/lib -lcgns -lhdf5
inc_flag = -I$(CGNS_ROOT)/include -I$(CGNS_ROOT)/include
################################################################################
main.out : main.cpp
	$(ccomp) main.cpp $(inc_flag) $(lib_flag) -o main.out
################################################################################
clean:
	rm *.out *.cgns
################################################################################
run:
	./main.out
