#ifndef FLIGHT_H_
#define FLIGHT_H_
#include "ex2.h"

// Typedef of the struct.
typedef struct flight_t *PFlight;

// Function that we had to do.
PFlight createFlight(int Flight_num, FlightType Typef, char* Destenation, BOOL Emergency);
void destroyFlight(PFlight flight);
void printFlight(PFlight flight);

//	Auxilary function that we made for us .
int getFlightId(PFlight flight);
FlightType getFlightType(PFlight flight);
BOOL getFlightEmr(PFlight flight);
char* getFlightDes(PFlight flight);
void setFlightDes(PFlight flight , char* newDest);
#endif