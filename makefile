# Define variables for the compiler and flags
CXX = gcc
CXXFLAGS = -lraylib -lX11 -lGL -lm -ldl -lrt 

# The first target is the default one run by 'make'
all: main

# Rule to create the 'main' executable
main: raylibFile.c
	$(CXX) -o ./bin/raylibFile raylibFile.c $(CXXFLAGS) 
# A 'clean' rule to remove the executable
git:
	git add .
	git commit
	git push
