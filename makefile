CC = gcc
CFLAGS = -g -Wall 
CCLINK = $(CC)
LIBS = 
OBJS = main.o airport.o runway.o flight.o
RM = rm -f 


airport: $(OBJS)
	$(CCLINK) -o airport $(OBJS) $(LIBS)
	

main.o: main.c airport.h runway.h flight.h ex2.h
airport.o: airport.c airport.h runway.h flight.h ex2.h
runway.o: runway.c runway.h flight.h ex2.h
flight.o: flight.c flight.h ex2.h

clean:
	$(RM) airport *.o *.bak *~ "#"* core
