#define _CRT_SECURE_NO_WARNINGS
#include "flight.h"
#include "ex2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runway.h"
#include "airport.h"
#define MAX_LENGHT (256)

/*************************************************************************************
// function name :  NumOfArg
// Description   :	Function that Counts the number of arguments in a command.
// Parameters    :	5 strinrgs of arguments.
// Return value  :	the number of non null arguments.
//**************************************************************************************/
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

/*************************************************************************************
// function name :  check_Number
// Description   :	checks if the number is valid and returns it as an integer.
// Parameters    :	a stirng with a number in it.
// Return value  :	0 if the number if not valid, else the number as an int.
//**************************************************************************************/
int check_Number(char *arg)
{
	int temp = atoi(arg);
	if (temp<1 || temp>MAX_ID)
		return 0;
	return temp;
}

/*************************************************************************************
// function name :  check_type
// Description   :	Function that checks if the type is International or Domestic.
// Parameters    :	a string that represents a type of runway or flight.
// Return value  :	sucsess if the string is international or domestic, else faliure.
//**************************************************************************************/
BOOL check_type(char *arg)
{
	return((!strcmp(arg, "I")) || (!strcmp(arg, "D")));
}

/*************************************************************************************
// function name :  check_emr
// Description   :	Function that checks if it is emergency or not.
// Parameters    :	a string that represents an emergency or not.
// Return value  :	sucsess if the string is emergency or regular, else faliure.
//**************************************************************************************/
BOOL check_emr(char *arg)
{
	return((!strcmp(arg, "E")) || (!strcmp(arg, "R")));
}

/*************************************************************************************
// function name :  check_type
// Description   :	Function that checks if the type is International or Domestic.
// Parameters    :	a string that represents a type of runway or flight.
// Return value  :	sucsess if the string is international or domestic, else faliure.
//**************************************************************************************/
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

/*************************************************************************************
// function name :  main
// Description   :	a main function that runs and calls al the other function
accordnig to the users input.
// Parameters    :	none.
// Return value  :	0 if finished with no errors.
//**************************************************************************************/
int main()
{
	char command[MAX_LENGHT];// a string the holds the current command.
	char* delimiter = " \t\n"; // diffrent chars to cut by in the command.
	char *argument, *argument1, *argument2, *argument3, *argument4;//command arguments.
	while (fgets(command, MAX_LENGHT, stdin))//loops over all the input until EOF and put the input line in command.
	{
		argument = strtok(command, delimiter);//puts the 1st argument in the command.
		argument1 = strtok(NULL, delimiter);//puts the 2nd argument in the command.
		argument2 = strtok(NULL, delimiter);//puts the 3rd argument in the command.
		argument3 = strtok(NULL, delimiter);//puts the 4th argument in the command.
		argument4 = strtok(NULL, delimiter);//puts the 5th argument in the command.
		
		if (argument == NULL)//advances if the command is empty.
		{
			continue;
		}
		if (!strcmp(argument, "Insert"))// if the command is Insert.
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 3)//checks if the number of paramters are not valid.
			{
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0 || check_type(argument2) == FALSE)//checks if the arguments are valid.
			{
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
			if (addRunway(check_Number(argument1), convert_chrtotype(argument2))==FAILURE)//calls the addrunway function.
			{
				fprintf(stderr, "Insert execution failed.\n");//if addrunway has failed.
				continue;
			}
		}
		else if (!strcmp(argument, "Remove"))//if the command is Remove
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 2)//checks if the number of paramters are not valid.
			{
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0)//checks if the argument is valid.
			{
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
			if (removeRunway(check_Number(argument1)) == FAILURE)//calls the removeRunway function.
			{
				fprintf(stderr, "Remove execution failed.\n");//if removeRunway has failed.
				continue;
			}
		}
		else if (!strcmp(argument, "Add"))//if the command is Add.
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 5)//checks if the number of paramters are not valid.
			{
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			if (check_Number(argument1) == 0 || check_type(argument2) == FALSE 
				|| check_emr(argument4)==FALSE) //checks if the arguments are valid.
			{
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			if (addFlightToAirport(check_Number(argument1), convert_chrtotype(argument2),argument3,
				convert_chrtoemr(argument4))== FAILURE)// calls the addFlighttoAirport function.
			{
				fprintf(stderr, "Add execution failed.\n");//if the add has failed
				continue;
			}
		}
		else if (!strcmp(argument, "Depart"))//if the command is Depart
		{
			if (departFromAirport() == FAILURE)//calls the depart function.
			{
				fprintf(stderr, "Depart execution failed.\n");//if depart has failed.
				continue;
			}
		}
		else if (!strcmp(argument, "Change"))//if the command is Change
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 3)//checks if the number of paramters are not valid.
			{
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
			if (changeDest(argument1,argument2) == FAILURE)//calls the changeDest function.
			{
				fprintf(stderr, "Change execution failed.\n");//if change has failed.
				continue;
			}
		}
		else if (!strcmp(argument, "Delay"))//if the command if Delay.
		{
			if (NumOfArg(argument, argument1, argument2, argument3, argument4) < 2)//checks if the number of arguments is valid.
			{
				fprintf(stderr, "Delay failed: not enough parameters.\n");
				continue;
			}
			if (delay(argument1) == FAILURE)//calls the delay function.
			{
				fprintf(stderr, "Delay execution failed.\n");//if delay has failed.
				continue;
			}
		}
		else if (!strcmp(argument, "Print"))//if the command is Print.
		{
			printAirport();//prints the airports status.
			printf("\n");
		}
		else if (!strcmp(argument, "Exit"))//if the command is Exit
		{
			destroyAirport();//destroys the airport.
			return 0;
		}
		else//the command is not valid(none of the above).
		{
			fprintf(stderr, "Command not found.\n");
		}
	}
	destroyAirport();//destroys the airport at the end of the run.
	return 0;
}
