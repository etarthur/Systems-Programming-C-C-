PA3 by Eric Arthur

to run this program first compile by running make, then to run it in the command shell:

	./PA3 output.txt input.txt ... 

where output.txt is the file you wish to print to and input.txt is the file you wish be to read. There can be as
many input files as you wish, there has to be at least one though.

The program will then scan through all the input files and enter them into a tree, which then all the strings
are printed alphabetically with the amount of times they appear. 


My stringCleaner algorithm comes from this stack exchange post: https://stackoverflow.com/questions/9283555/removing-punctuations-in-a-string-in-c

I can explain exactly how it works, it initializes another pointer to the same string, and sets up a for loop to increment
that pointer, it will then use the function isalpha and check if the first char is an ' or - and if so it will set it equal
to the same spot in the input string. If not then the loop is incremented but the element of the input string is not, therefore
it will remove all punctuation and then at the end, set the last spot equal to the terminating character.

LOOP INVARIANTS: 
in Main:
for(int i = 2; i < argc; i++){//loops through all user input files, INVARIANT i < argc, means i is less than the amount, i=0...argc-2

while(fscanf(ftr,"%s",string)==1){//loops through every string in the file, INVARIANT fscanf==1, means will only run while there are things to scan, otherwise EOF is returned and while ends

for(int i = 0; i < argc-2; i++){//loops through all user input, same as above INVARIANT: i < argc-2 means i is less than the amount of user input +1 -2, so it starts at 0, useful to call array elements since they start at 0
	for(int j = 0; j < numWords[i]; j++){loops through the number of words per input file INVARIANT: j < numWords[i] means j will loop from 0... till end of file

loops were not used in other functions, instead recursion was.

Loop invariants in the string functions class, specifically found within the function stringCleaner
have the invariant while(*s) which means the loop will run until an ending char is found.


	
