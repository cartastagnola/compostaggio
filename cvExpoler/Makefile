CFLAGS = -g -w `pkg-config --cflags opencv4` -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces 
INCLUDE_PATHS = -Wall -D_DEFAULT_SOURCE -Wno-missing-braces -I/home/arcblock/gitHubs/eigen/ -I/usr/local/include -I. -L. -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
# deleted from the CFLAGS -s -O1 to make gcc to create the debugging symbol
#LFLAGS = `-w`
LIBS = -lSDL2 -lSDL2_image -lSDL2_gfx `pkg-config --libs opencv4 `
#LIBS = `pkg-config --libs opencv4 `

#all: 
#	g++ $< cvExpoler.cpp math_slam.h $(CFLAGS) $(LIBS) $(INCLUDE_PATHS) -o exp 

cvExpoler : cvExpoler.cpp math_slam.o
	g++ $< $(CFLAGS) $(LIBS) $(INCLUDE_PATHS) -o $@ 

math_slam.o : math_slam.h
	g++ -c $< $(INCLUDE_PATHS) -o $@ 

clean:
	rm *.o


#%.o:%.cpp,%.h
#	echo "ello wolr" 
#	$(CC) $(CFLAGS) -c -o %<
#

##OBJS specifies which files to compile as part of the project
#OBJS = 01_hello_SDL.cpp
#
##CC specifies which compiler we're using
#CC = g++
#
##COMPILER_FLAGS specifies the additional compilation options we're using
## -w suppresses all warnings
##  COMPILER_FLAGS = -w
##
##  #LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = -lSDL2
#
##OBJ_NAME specifies the name of our exectuable
#OBJ_NAME = 01_hello_SDL
#
##This is the target that compiles our executable
#all : $(OBJS)
#		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
