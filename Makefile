# Makefile for the smash program
TARGET = HW1
CC=g++
CXXFLAGS = -g -Wall
CCLINK = ${CC}
OBJS = smash.o commands.o signals.o
RM = rm -f
# Creating the  executable
$(TARGET): $(OBJS)
	${CCLINK} -o ${TARGET} ${OBJS}
# Creating the object files
commands.o: commands.cpp commands.h
smash.o: smash.cpp commands.h signals.h
signals.o: signals.cpp signals.h
# Cleaning old files before new make
clean:
	${RM} ${TARGET} *.o *~ "#"* core.*

