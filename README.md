# C-Project-ReversedPolishCalculator
DSTI C programming project: 
The program must interactively read a algebraic expression such as: (x + 3) * 2 * y
We presume that expressions are provided well-formatted by the user,
i.e. I'm not expecting your program to check the correctness of the expression

We presume that there are no implicit operators
This is expected, the user provides explicit operators: (x + 3) * 2 * y
This is not expected, you don't have to deal with the case: (x + 3) 2 * y
This is not expected, you don't have to deal with the case: (x + 3) 2y
This is not expected, you don't have to deal with the case: (x + 3) * 2y

A formal identifier is made of one character: x, y, z, etc.
You may, but DO NOT HAVE TO, deal with an multi-character identifier, such as xy, hello, etc.
If you deal with these, xy = 1 identifier, hello = 1 identifier, etc.

Number values are integers.
You may, but DO NOT HAVE TO, deal with real-valued numbers.

Valid characters for numbers: [0-9]
Valid characters for formal identifiers: [A-Z] and [a-z]
Valid characters for operators: + - / * ( )
NO "known" function is expected to be processed ( ln, sin, cos, etc.)
NO "power" expression is expected to be processed (i.e 2^3)

Spaces must be ignored
IMPORTANT: the signature of your Reverse Polish Notation function must be:
double ReversePolish(const char* strExpression);


The program
	1. Process the input and identifies all formal identifiers
	2. Asks interactively for their effective values
	3. Process the expression using the Reverse Polish Notation
	4. Returns the value of the computation

2 Program flows examples on the console, assuming the hypotheses and restrictions above

Example 1:
Please type your formal expression: (x + 3) * 2 * y
Your expression has 2 parameters : x and y
Please give an integer value for x: 6
Please give an integer value for y: 3
Processing (6 + 3) * 2 * 3 using the Reverse Polish Notation
Result: 54

Example 2:
Please type your formal expression: ((a+b)*(a+b))*10
Your expression has 3 parameters : a and b
Please give an integer value for a: 3
Please give an integer value for b: 2
Please give an integer value for c: 10
Processing ((3+2)*(3+2))*10 using the Reverse Polish Notation
