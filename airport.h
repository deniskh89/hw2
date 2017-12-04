#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "flight.h"
#include "ex2.h"
#include "runway.h"


Result addRunway(int runway_num, FlightType runway_type);
Result removeRunway(int runway_num);
Result addFlightToAirport(int Flight_num, FlightType Typef, char* Destenation, BOOL Emergency);
Result departFromAirport();
Result changeDest(char* Destenation_old, char* Destenation_new);
Result delay(char* Destenation);
void printAirport();
void destroyAirport();

#endif /* EX2_H_ */
