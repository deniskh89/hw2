#ifndef RUNWAY_H_
#define RUNWAY_H_
#include "ex2.h"
#include "flight.h"

//	Typedef of the struct.
typedef struct runway_t *PRunway;

// Function that we had to do.
PRunway createRunway(int runway_num, FlightType runway_type);
void destroyRunway(PRunway runway);
BOOL isFlightExists(PRunway runway, int flight_num);
int getFlightNum(PRunway runway);
int getEmergencyNum(PRunway runway);
Result addFlight(PRunway runway, PFlight flight);
Result removeFlight(PRunway runway, int flight_num);
Result depart(PRunway runway);
void printRunway(PRunway runway);

//	Auxilary function that we made for us .
int getRunwayID(PRunway runway);
FlightType getRunwayType(PRunway runway);
void changeDestInRunway(PRunway runway , char* newDest, char* oldDest);
Result delayRunway(PRunway runway, char* Dest);
#endif