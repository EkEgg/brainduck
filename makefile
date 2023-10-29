EXECUTABLE=./brainduck

SOURCES_FOLDER=./src
OBJECTS_FOLDER=./obj

COMPILER=g++
COMPILER_FLAGS=-ansi -pedantic -Wall -std=c++11 -O3

CPP_SOURCES=${wildcard ${SOURCES_FOLDER}/*.cpp}
H_SOURCES=${wildcard ${SOURCES_FOLDER}/*.h}

OBJECTS=${subst .cpp,.o,${subst ${SOURCES_FOLDER},${OBJECTS_FOLDER},$(CPP_SOURCES)}}

all: ${OBJECTS_FOLDER} ${EXECUTABLE}

${OBJECTS_FOLDER}:
	mkdir ${OBJECTS_FOLDER}

${EXECUTABLE}: ${OBJECTS}
	$(COMPILER) -o $@ $^ $(COMPILER_FLAGS)

${OBJECTS_FOLDER}/%.o: ${SOURCES_FOLDER}/%.cpp ${SOURCES_FOLDER}/%.h
	$(COMPILER) -o $@ $< $(COMPILER_FLAGS) -c

${OBJECTS_FOLDER}/main.o: ${SOURCES_FOLDER}/main.cpp $(H_SOURCES)
	$(COMPILER) -o $@ $< $(COMPILER_FLAGS) -c

clean:
	rm -rf ${EXECUTABLE} ${OBJECTS_FOLDER}
