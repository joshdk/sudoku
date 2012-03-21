sudoku
======

Building
--------
	$ make

Running
-------
	$ ./build/sudoku [COUNT|all] [PATH|-]

Examples
--------
	$ ./build/sudoku - #read file on stdin
	$ ./build/sudoku /path/to/file
	$ ./build/sudoku 5 /path/to/file #find first 5 solutions
	$ ./build/sudoku all /path/to/file #find all solutions
