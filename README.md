A C program that sorts input from the command line or from an INPUTFILE and displays to the standard output or an OUTPUTFILE.
The program uses binary search tree.

Usage
# With no command line arguments
gcc -o bstsort bstsort.c
./bstsort
[


Type here the words you wnat to sort.
Press enter twice after the last word.

]

# With command line arguments [-o]
gcc -o bstsort bstsort.c
./bstsort -o [OUTPUTFILE] [INPUTFILE]


# With command line arguments [-c]
# The -c option only sorts the words that are entirely upper case.
gcc -o bstsort bstsort.c
./bstsort -c [INPUTFILE]




