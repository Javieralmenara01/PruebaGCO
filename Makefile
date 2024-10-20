# Make file for the SistemaRecomendador project
main: src/main.cc
	g++ -std=c++17 -o main src/main.cc src/Functions/auxFunctions.cc src/Functions/inputFunctions.cc src/Functions/predictionFunctions.cc src/Functions/similarityFunctions.cc src/Class/Data.cc

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -rf *~ main b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name main -exec rm {} \;