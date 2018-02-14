/* Assignment 1 - Calendar - Eric Arthur - CS2303 - 9/5/2017 */

//All loop variants, and data types for month,day, and year are described more in depth in the readme.

#include <stdio.h>

//function headers, all functions will have header comments above their actual declarations
void printCalendar(int year, int day);
int printMonth(int year, int month, int day);
int printMonthName(int year, int month); //done
int startingDay(int year); //done
int isLeap(int year); //done

/** Main runs the program using all the helper functions, it asks for a user input year and returns a calendar for that year, year must be a positive integer

Main initalizes variables necessary and prompts a user for a year which must be above 0 and an integer, if those conditions are not met it will
prompt again until a valid year is entered. Then using the function printCalendar and startingDay prints out a calendar for that year.
@return integer 0, as main always does, this number means that the function worked properly, but has no value to the program only to the compiler
*/
int main(void){
int year; // the year the calendar will be, inputed by user, must be a positive integer.
int day;// day of the week with Sunday = 0, Monday = 1,..., Saturday = 6. Used to determine
//starting day of the month
printf("Please enter year, has to be a positive integer:-  ");
scanf(" %d", &year);
if(year <= 0){ //checks if the year input is valid if not it prompts the user for another
	printf("Year not valid, please input a valid response.\n");
	main();
}
day = startingDay(year);
printCalendar(year,day);
return 0;
}

/** isLeap takes a year as input and returns 1 if the year is a leap year or 0 if it is not

isLeap consumes a year and using the leap year rules, if a year is divisible by 4 and not 100 it is a leap year, and if it is
divisible by 4,100, and 400 it is a leap year, it returns 1(for true) otherwise it will return 0(for false), ints are used
as booleans are not a default type in C
@param int year: is the year in question, must be a valid year as described by main(positive integer)
@return int, 0 if the year is not a leap year and 1 if it is
*/
int isLeap(int year){
if(year % 4 == 0 && year % 100 != 0){ //checks if the current year is a leap year by seeing if it
// is divisible by 4 and not by 100.
	return 1; //1 meaning true, since C doesn't have booleans, so 1 is a leap year
}
if(year % 4 == 0 && year % 100 == 0 && year % 400 == 0){ //checks if the current year is a leap year if it is
//divisible by 4, 100 and 400.
	return 1;
}
else{ //the branch that runs if the year is not a leap year
	return 0; //0 meaning false is not a leap year
}
}

/** startingDay consumes a year and returns the day of the week the year starts on(in the form 0-6 for days of week).

startingDay uses a reference year, 1601 in which the first day was Monday(1) and then calculates the startingDay of the input
year by adding or subtracting one or two days per year inbetween. The numbers are calculated based on the mathmetical basis that if a year is not
a leap year, then the year after it's starting day will be one later as 365/7 = 52.14. And the fact that if a year is a leap year then the next year will start
2 days later as 366/7 is 52.28. Therefore every year inbetween the input year and reference year is checked to see whether it is a leap year using isLeap, and then
the correct amount of days is added or subrtaced depending on if the year is newer than the reference or older. Then the number of days is modulused by 7 to return
the week day the year starts on in the week number system construct.
@param int year: The year that the first day wants to be known, must be a valid year(check main)
@return int day: the week day the year starts on in the form 0-6(Sunday = 0, Saturday = 6)
*/
int startingDay(int year){
//for reference the first day of the year 1601 was on a Monday(1)
	int refyear = 1601; //reference year as noted above, used to compare
	int startday = 1; //starting day of reference year as noted above, used to find starting day
	int curyear = refyear; //current year, used in the loops to find starting day
	if(year == refyear){ //checking if the input year is the reference year, if so no work is needed
		return startday;
	}
	if(year >= refyear){ //checking if the input year is above the reference year
		while(curyear < year){//Loop invariant: curyear >= year, and curyear is decremented by one every run, means this will loop through every year from 
					//user input year until it reaches the reference year
			if(isLeap(curyear)==1){ //checking if the current year is a leap year, this branch runs if it is
				startday = startday + 2;
				curyear = curyear + 1;
			}
			else{ //branch runs if the current year is not a leap year
				startday = startday + 1;
				curyear = curyear + 1;
			}
	}
		return (startday) % 7; //return the day of the week which is obtained by mod 7 to bring number back
		// to week number system used as explained above in main function
	}
	else{ //checking if the input year is below the reference year
		while (curyear > year){//Loop invariant same as one above, except this time the input year is below so the current year is incremented by one every loop.
			if(startday < 0){//check to make sure the startday is not going below 0
			startday = startday + 7;//add 7 to return the startday to the number system in place for days of the week.
			}
			if(isLeap(curyear)==1){ //checking if the current year is a leap year, this branch runs if it is
				startday = startday - 2;
				curyear = curyear - 1;
			}
			else{ //branch of the if that the current year is not a leap year
			startday = startday - 1;
			curyear = curyear - 1;
			}
		}
		return (startday + 7) % 7; //return day of week in base 7 number system declared above in main function, add 7 to prevent negative numbers
	}
}

/** printMonthName consumes a year and a month and prints out the month as "Month, year" and returns the number of days in the month

printMonthName consumes a year and a month and prints out the month/year and returns the number of days in the month, checking if the year is a leap
year and incrementing the days in febuary accordingly.
@param int year: The year, necessary to print and to check if year is a leap(affects febuary)
@param int month: the month, used to return days in the month and print out
@return int days: returns the number of days in the month, febuary may be 28 or 29 depending on if the year is a leap year, otherwise 30 or 31 for months.
*/
int printMonthName(int year, int month){
switch(month){ //the switch statement uses the month input as the expression to determine which case to jump to, therefore 0-11 are just months
	//of the year with 0 being january and 11 being december
	case 0 :
	printf("January %d \n",year);
	return 31;
	break;

	case 1 :
	printf("Febuary %d \n",year);
	if(isLeap(year)==1){
	return 29;
	}
	else{
	return 28;
	}
	break;

	case 2 :
	printf("March %d \n",year);
	return 31;
	break;

	case 3 :
	printf("April %d \n",year);
	return 30;
	break;

	case 4 :
	printf("May %d \n",year);
	return 31;
	break;

	case 5 :
	printf("June %d \n",year);
	return 30;
	break;

	case 6 :
	printf("July %d \n",year);
	return 31;
	break;

	case 7 :
	printf("August %d \n",year);
	return 31;
	break;

	case 8 :
	printf("September %d \n",year);
	return 30;
	break;

	case 9 :
	printf("October %d \n",year);
	return 31;
	break;

	case 10 :
	printf("November %d \n",year);
	return 30;
	break;

	case 11 :
	printf("December %d \n",year);
	return 31;
	break;
}

return 12;//returns a value which will never be used if program runs correctly, otherwise things will break and it is easy to spot when 12 pops up
//as this number is not anywhere else in the code
}

/** printMonth consumes a year, month and a startday and prints out the calendar for that month

printMonth consumes a year which is uses to print out a header with printMonthName and calculates the days of the month from the same function, the
year is also used to check if it is a leap year, the month is printed in the header, and is used to calculate the total days, and the startday is used
to determine which day the calendar should start on. For days before the start day the function fills them in with blank space, it then increments the day
to fill out the calendar, resetting every 7 days as to not overflow the lines with days that don't exist.
@param int year: the year of the calendar, must be valid(positive integer)
@param int month: the month of the calendar, again must be valid(0-11)
@param int startday the starting day of the month, must be between 0-6
@return currentday: is the starting day of the next month, used in the following function printCalendar to print out the whole year.
*/
int printMonth(int year, int month, int startday){
	printf("\n\n");
	int currentday = startday; //currentday starts as start day then increments through the loops until the month ends
	int days = printMonthName(year, month);//days is the total number of days in the month, value from printMonthName
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat \n");
	if(startday < 7){
	for(int i = 0; i < startday; i++){//Loop invariant: i < startday, means that i will always be beneath the starting day of the month, so it is used to fill in blank space
		printf("   ");
		printf("  ");
	}}
	for(int z = 1; z <= days; z++){//Loop invariant: z <=days, this means that z will loops through all possible days in the month
		if(currentday == 7){//checks that the current day doesn't exceed the week system set in place, as described in main(i.e. Sunday = 0,... Saturday = 6)
				printf("\n");
				currentday = 0;//resets current day to start cycling again, therefore it won't exceed the 7 day line limit
		}
		printf("%3d", z);
		printf("  ");
		currentday++;
	}

	printf("\n\n");
	return currentday;//returns the day the month ended on, so the next month knows when to start

}

/** printCalendar takes a year and a startday and prints out the entire calendar for that year

printCalendar takes a year and a startday and using a loop and the printMonth function prints out the calendar for the entire year
broken into months. The starting day of each month is calculated by rolling over the final day of each month prior, starting with the first month
which starts on the startday passed in
@param int year: The year of the calendar printed must be valid
@param int startday: The starting day of the associated year so the calendar knows which day to start on
@return void, the function only prints the calendar and doesn't return anything
*/
void printCalendar(int year, int startday){
printf("\t *** Calendar for %d ***",year);
int day = startday;//sets the variable day for the starting day of the month
for(int month = 0; month <= 11; month++){//Loop invariant, month <= 11, means that month will cycle through all possible values from 0-11, relating to corresponding months.
day = printMonth(year,month,day);//changes day to update to the starting day of the next month
}
}
