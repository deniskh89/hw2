#ifndef RUNWAY_H_
#define RUNWAY_H_
#include "ex2.h"
#include "flight.h"

typedef struct runway_t *PRunway;

PRunway createRunway(int runway_num, FlightType runway_type);
void destroyRunway(PRunway runway);//not done
BOOL isFlightExists(PRunway runway, int flight_num);
int getFlightNum(PRunway runway);
int getEmergencyNum(PRunway runway);
Result addFlight(PRunway runway, PFlight flight);
Result removeFlight(PRunway runway, int flight_num);
Result depart(PRunway runway);
void printRunway(PRunway runway);

int getRunwayID(PRunway runway);
FlightType getRunwayType(PRunway runway);
void changeDestInRunway(PRunway runway , char* newDest, char* oldDest);
Result delayRunway(PRunway runway, char* Dest);
#endif