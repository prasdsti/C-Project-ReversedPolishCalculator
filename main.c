#include "functions.h"


/*
Version:	vbeta1.1
Autor:		Prasanth PUSHPARASAH
Function:	Translate infix equation to postfix equation and compute the Reversed Polish
Code Specification:
	1/ Ask an equation to user
	2/ Translate infix to postfix to have Reversed Polish Notation
	3/ Compute the reserved Polish Notation and give the result
Code Restriction:
	Due to time constraint with the other projects, for the moment the current code
	can only process "INTEGERS" but the result is in "DOUBLE". The code cannot handle
	negative values for given variables, but can return a negative value
*/


int main()
{


	EquationStack userInputStack = userInputInStack();
	//printf("Displaying userInputStack:\n");
	//displayEquationStack(&userInputStack);

	EquationStack inFixToPostFixStack = inFixToPostFix(&userInputStack);
	//printf("\n\nDisplaying inFixToPostFixStack:\n");
	//displayEquationStack(&inFixToPostFixStack);

	EquationStack userVariablesEvaluatedStack = userVariablesEvalution(&inFixToPostFixStack);
	//printf("\n\nDisplaying userVariablesEvaluatedStack:\n");
	//displayEquationStack(&userVariablesEvaluatedStack);


	double myResult = computeRPN(&userVariablesEvaluatedStack);
	//double myResult = computeRPN(&inFixToPostFixStack);
	printf("\nResult of your \"Reversed Polish Notation\" computation is: %lf\n\n", myResult);

	system("pause");


	return 0;
}