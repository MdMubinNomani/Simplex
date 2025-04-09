# Simplex Language

A simple programming language created with a custom compiler written in C++. This project was developed to gain a deeper understanding of how compilers function and the principles behind language design.

## How to run Simplex
### Step 1
Locate the text file named 'simplex_code.txt' and write Simplex code here. It is crucial to keep the file name as it is.
### Step 2
Locate the executable named 'SimplexCompilerScript.exe' and run it. If the executable is missing, open the cpp file named 'SimplexCompilerScripts.cpp' and run the C++ code in your prefered code editor atleast once. Needless to say, You will need the C/C++ compiler preinstalled.

## Simplex Syntax
Keywords:-

	set : Variable declaration. 
 
	echo : Output to the console.
 
	if-else : Executes a part of code only if set conditions are met.
 
	repeat : Loops while set conditions are true.


Operators:-

	assignment : [=]

	arithmetic : [+, -, /, *]

	comparison : [==, <=, >=, !=, >, <]


Delimiters:-

	Encapsulation : { ... }


Variable Assignment [Example]:- 

	set age = 5

	set name = "String"

	set flag = false


Arithmetic Operation [Example]:-

	set result1 = 5 + 3

	set result2 = 10 - 7

	set result3 = 4 * 2

	set result4 = 8 / 2

Conditional [Example]:-

	if a > b {
	    echo "a is greater than b"
	}

Console Outputs [Example]:-

	echo a

	echo name

	echo "Hello, World"

	echo 42

Loops [Example]:- (⚠️ not yet implemented )

	set i = 0;
	repeat i < 5 {
      if i % 2 == 0 {
          echo "i is even"
      } else {
          echo "i is odd"
      }
      i = i + 1
	}
