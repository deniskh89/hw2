#define _CRT_SECURE_NO_WARNINGS
#include "flight.h"
#include "ex2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runway.h"
#include "airport.h"
#define MAX_LENGHT (256)

int NumOfArg(char *argument, char *argument1, char *argument2, char *argument3, char *argument4)
{
	int numofarg = 0;
	if (argument != NULL)
		numofarg++;
	if (argument1 != NULL)
		numofarg++;
	if (argument2 != NULL)
		numofarg++;
	if (argument3 != NULL)
		numofarg++;
	if (argument4 != NULL)
		numofarg++;
	return numofarg;
}

int check_Number(char *arg)
{
	int temp = atoi(arg);
	if (temp<1 || temp>MAX_ID)
		return 0;
	return temp;
}

BOOL check_type(char *arg)
{
	return((!strcmp(arg, "I")) || (!strcmp(arg, "D")));
}


BOOL check_emr(char *arg)
{
	return((!strcmp(arg, "E")) || (!strcmp(arg, "R")));
}

FlightType convert_chrtotype(char *arg)
{
	if (!strcmp(arg, "I"))
		return INTERNATIONAL;
	else
		return DOMESTIC;
}

BOOL convert_chrtoemr(char *arg)
{
	if (!strcmp(arg, "E"))
		return TRUE;
	else
		return FALSE;
}

int main()
{
	char command[MAX_LENGHT];
	char* delimiter = " \t\n";
	char *argument, *argument1, *argument2, *argument3, *argument4;
	while (fgets(command, MAX_LENGHT, stdin))
	{
		argument = strtok(command, delimiter);
		argument1 = strtok(NULL, delimiter);
		argument2 = strtok(NULL, delimiter);
		argument3 = strtok(NULL, delimiter);
		argument4 = strtok(NULL, delimiter);
		
		if (argument == NULL)
		{
			continue;
		}
		if (!strcmp(argument, "Insert"))
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 3)
			{
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0 || check_type(argument2) == FALSE)
			{
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
			if (addRunway(check_Number(argument1), convert_chrtotype(argument2))==FAILURE)
			{
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Remove"))
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 2)
			{
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0)
			{
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
			if (removeRunway(check_Number(argument1)) == FAILURE)
			{
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Add"))
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 5)
			{
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0 || check_type(argument2) == FALSE 
				|| check_emr(argument4)==FALSE) 
			{
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			if (addFlightToAirport(check_Number(argument1), convert_chrtotype(argument2),argument3,
				convert_chrtoemr(argument4))== FAILURE)
			{
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Depart"))
		{
			if (departFromAirport() == FAILURE)
			{
				fprintf(stderr, "Depart execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Change"))
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 3)
			{
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
			if (changeDest(argument1,argument2) == FAILURE)
			{
				fprintf(stderr, "Change execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Delay"))
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 2)
			{
				fprintf(stderr, "Delay failed: not enough parameters.\n");
				continue;
			}
			if (delay(argument1) == FAILURE)
			{
				fprintf(stderr, "Delay execution failed.\n");
				continue;
			}
		}
		else if (!strcmp(argument, "Print"))
		{
			printAirport();
			printf("\n");
		}
		else if (!strcmp(argument, "Exit"))
		{
			destroyAirport();
			return 0;
		}
		else
		{
			fprintf(stderr, "Command not found.\n");
		}
	}
	destroyAirport();
	return 0;
}
