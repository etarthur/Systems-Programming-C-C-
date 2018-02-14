PA1.c by etarthur for CS2303

The program prints out a calendar for a year the user inputs. To run compile and run ./a.out then input a valid year(see below Data Types). If an invalid
year is inputted, then the program will continually prompt the user to input a valid one until they do. When a valid one is printed the calendar for the year
will then be printed out. All of the functions are described in depth in the source code, including the math for the startingDay and isLeap functions. Loop invariants
are described below as well as valid data entries for day, month and year.


Loops:

in function startingDay:
while(curyear <(>) refyear): Loop invariant is curyear < refyear and curyear > refyear, and curyear is either incremented by one or decremented by one every loop until it reaches the
reference year. There are two loops in the this function that follow the same invariant, one adds the other subtracts.

in function printMonth:
for(int i = 0; i < startday; i++): Loop invariant is i < startday and i is incremented by one every loop, this allows for the calendar to generate blank space for
the days on the calendar before the start of the month

for(int z = 1; z <= days; z++): Loop invariant is z <=days, and z is incremeneted by one every loop, which means that z is the day of the month, and it loops through
all the days in the month until the month finishes

in function printCalendare:
for(int month = 0; month <= 11; month++): Loop invariant month<=11, month is increased by one every run, this allows for every month to be generated and passed into
the printMonth function which in turn prints the entire year's calendar.

Data Types:
day: an integer between 0-6:
  Sunday = 0
  Monday = 1
  Tuesday = 2
  Wednesday = 3
  Thursday = 4
  Friday = 5
  Saturday = 6

month: an integer between 0-11:
  January = 0
  February = 1
  March = 2
  April = 3
  May = 4
  June = 5
  July = 6
  August = 7
  September = 8
  October = 9
  November = 10
  December = 11

year: any positive integer above 0
