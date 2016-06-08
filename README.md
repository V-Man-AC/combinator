# combinator
Takes two word lists and combines them using permutations into an exponentially larger word list.

Compilation tested on g++ 5.3.1 20160528.

Usage: combinator [input file 1] [input file 2] [output file]

Combinator will start at the first word of the first file. It will concatenate it with the first word of the second file, then with the second word of the second file, and so on until the end of the second file. It will then move to the second word of the first file and repeat the process until the end of the first file. Be aware that this could potentially produce a file with unmanageable size.
