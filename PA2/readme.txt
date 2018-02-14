To run this program first it must be made using the make function from a unix command shell. Then it can be run by calling
the exectuable in the command shell with this command:
		./life X Y gens input print pause
where:
X and Y are the rows and columns, the grid size for the game

gens is the amount of generations that are to be simulated

input is the name of a file with the starting state created using o and x. More on this below.

print being y or n, y=yes, and if yes every generation will be printed out not just the final one

pause being y or n, if yes after every generation a keystroke is needed to commence the next one generation to run.

The input file cannot be larger than 250 characters. This is an arbitrary value to prevent overflow. The steady state checker can only check for oscillating steady states of period 2, anything greater will never be detected. 
The optimal way to calculate oscillating steady states of any period is to either have a document or save in memory every state of the board, and continually compare of all them. This can be a huge memory sink
though for periods of greater than 5 so that's why I just used 2.

Loop invariants:

playOne, anyChange, emptyBoardChecker, main, printBoard all contain the same loop invariants of the type
i < rows or y< columns. These variables are incremented by one every loop until they reach rows-1 or columns-1, this means
they pass through every row and column when used in conjuction, so every cell on the board is hit. 

playGame contains this loop for(int g = 0; g <= gens; g++) with invariant g <= gens, this loop loops through all generations
until it reaches its end. 

Memory allocation loops in main, explained below
The code was also taken from the assigment write up, to explain in my own words it works by first initalizing a pointer
to a 2d array using **, then it mallocs the amount of memory necessary for rows amount of int arrays. Then all of these are
looped through and filled with elements of size int columns times. 



For further reading on the game of life rules and terminating conditions: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
