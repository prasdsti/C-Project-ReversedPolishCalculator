#include "functions.h"

/*
Process to init Reversed Polish Stack
*/
void initRPNStack(RPNStack* pRPNStack)
{
	pRPNStack->stackSize = 0;
	pRPNStack->pDoubleValue = NULL;
}



/*
Process to init Equation Stack
*/
void initEquationStack(EquationStack* pEquationStack)
{
	pEquationStack->stackSize = 0;
	pEquationStack->pCharValue = NULL;
}



/*
Process to release allocated memories to build the stack
*/
void destroyRPNStack(RPNStack* pRPNStack)
{
	if (pRPNStack->pDoubleValue != NULL)
	{
		free(pRPNStack->pDoubleValue);
		pRPNStack->pDoubleValue = NULL;
	}

	//an empty stack means no elements in the stack
	pRPNStack->stackSize = 0;

}



/*
Process to release allocated memories to build the stack
*/
void destroyEquationStack(EquationStack* pEquationStack)
{
	if (pEquationStack->pCharValue != NULL)
	{
		free(pEquationStack->pCharValue);
		pEquationStack->pCharValue = NULL;
	}

	//an empty stack means no elements in the stack
	pEquationStack->stackSize = 0;

}



/*
Function to check if the stack is empty and return a boolean
*/
BOOL isRPNStackEmpty(RPNStack* pRPNStack)
{
	BOOL result = FALSE;

	if (pRPNStack->stackSize == 0 && pRPNStack->pDoubleValue == NULL)
	{
		result = TRUE;
	}

	return result;
}



/*
Function to check if the stack is empty and return a boolean
*/
BOOL isEquationStackEmpty(EquationStack* pEquationStack)
{
	BOOL result = FALSE;

	if (pEquationStack->stackSize == 0 && pEquationStack->pCharValue == NULL)
	{
		result = TRUE;
	}

	return result;
}



/*
Function to push RPN values:
	RPNStack* pRPNStack => RPN stack to fill
	double RPNIntValue => RPN value to stack type double
*/
BOOL pushRPNValue(RPNStack* pRPNStack, double RPNIntValue)
{
	//Default value of push, will be changed to FALSE if something's wrong will happen
	BOOL succes = TRUE;

	//Checking if stack is empty
	if (isRPNStackEmpty(pRPNStack) == TRUE)
	{
		// Allocating necessary memory
		pRPNStack->pDoubleValue = (double*)malloc(sizeof(double));

		//Test if malloc succeeded, if not NULL is returned
		if (pRPNStack->pDoubleValue == NULL)
		{
			//Allocation has failed
			succes = FALSE;
		}
		else
		{
			//Allocation successed, filling firt element in stack
			pRPNStack->pDoubleValue[pRPNStack->stackSize] = RPNIntValue;
			pRPNStack->stackSize = pRPNStack->stackSize + 1;
		}
	}
	else
	{
		// take a "backup pointer" to the current stack, to avoid losing
		// a reference to the heap zone of the current stack
		double* pCurrentStackArray = pRPNStack->pDoubleValue;

		//this will be the new heap area for the increased stack
		double* pNewStackArray = NULL;
		pNewStackArray = (double*)malloc(sizeof(double) * (pRPNStack->stackSize + 1));

		//did we succeed in gaining a new area of the heap?
		if (pNewStackArray != NULL)
		{
			int loop;
			for (loop = 0; loop < pRPNStack->stackSize; loop++)
			{
				pNewStackArray[loop] = pCurrentStackArray[loop];
			}
			

			pNewStackArray[loop] = RPNIntValue;

			//swap the pointers: the stack array becomes "NewArray"
			pRPNStack->pDoubleValue = pNewStackArray;

			//increment the number of items in the stack
			pRPNStack->stackSize = pRPNStack->stackSize + 1;

			//destroy the old array
			free(pCurrentStackArray);
			//this variable is local to the else{} of the function
			//setting it to NULL is not necessary, but for the sake of consistency
			pCurrentStackArray = NULL;
		}
		else
		{
			//We failed to gain a new array for expanding the stack
			succes = FALSE;
		}
	}

	return succes;
}



/*
Function to get last element given in the stack and removing it from the stack
*/
RPNPop popRPNValue(RPNStack* pRPNStack)
{
	RPNPop result;

	//Stack is empty, nothing to pop
	if (isRPNStackEmpty(pRPNStack) == TRUE)
	{
		result.success = FALSE;
		result.doubleValue = 0;
	}
	//Stack is NOT empty, elemen can be poped
	else
	{
		result.success = TRUE;
		result.doubleValue = pRPNStack->pDoubleValue[pRPNStack->stackSize - 1];


		double* pCurrentStackArray = pRPNStack->pDoubleValue;

		//this will be the new heap area for the decreased stack
		double* pNewStackArray = NULL;
		pNewStackArray = (double*)malloc(sizeof(double) * (pRPNStack->stackSize - 1));


		//did we succeed in gaining a new area of the heap?
		if (pNewStackArray != NULL)
		{
			for (int loop = 0; loop < pRPNStack->stackSize - 1; loop++)
			{
				// we copy all the items except the last one: aIntStack->stackSize - 1
				pNewStackArray[loop] = pCurrentStackArray[loop];
			}

			//swap the pointers: the stack array becomes "NewArray"
			pRPNStack->pDoubleValue = pNewStackArray;

			//decrement the number of items in the stack
			pRPNStack->stackSize = pRPNStack->stackSize - 1;

			pCurrentStackArray = NULL;
		}
		else
		{
			result.success = FALSE;
			result.doubleValue = 0;
		}

	}

	return result;
}



/*
Function to display all elements and parameters in the built stack
*/
void displayRPNStack(const RPNStack* pRPNStack)
{
	//Stack is empty, nothing to pop
	if (isRPNStackEmpty(pRPNStack) == TRUE)
	{
		printf("The stack is empty\n");
	}
	//Stack is NOT empty, elemen can be poped
	else
	{
		//Looping on all elements in stack to print it out on screen
		for (int loop = pRPNStack->stackSize - 1; loop >= 0; loop--)
		{
			printf("pDoubleValue[%d] = %lf\n", loop, pRPNStack->pDoubleValue[loop]);
		}
	}

}



/*
Function to push equation values:
	EquationStack* pEquationStack => Equation stack to fill
	char* pEquationCharValue => Element of Equation value to stack type char
*/
BOOL pushEquationValue(EquationStack* pEquationStack, char* pEquationCharValue)
{
	BOOL succes = TRUE;

	//At this step looking if given element is a space or not, if this this is space, this is not take in account
	if (strcmp(pEquationCharValue, " ") == 1)
	{
		//Calculating length of given variable and allocating necessary memory for it
		int strLenEquationCharValue;
		strLenEquationCharValue = strlen(pEquationCharValue);
		char* pLocalEquationCharValue = (char*)malloc(sizeof(char) * strLenEquationCharValue + 1);
		strcpy(pLocalEquationCharValue, pEquationCharValue);

		//Stack is empty
		if (isEquationStackEmpty(pEquationStack) == TRUE)
		{
			//Allocating memory
			pEquationStack->pCharValue = (char*)malloc(sizeof(char));

			//test if malloc succeeded, if not NULL is returned
			if (pEquationStack->pCharValue == NULL)
			{
				//allocation has failed
				succes = FALSE;
			}
			else
			{
				//Adding first element in stack
				pEquationStack->pCharValue[pEquationStack->stackSize] = (char**)malloc(sizeof(char*) * strLenEquationCharValue + 1);
				pEquationStack->pCharValue[pEquationStack->stackSize] = pLocalEquationCharValue;
				pEquationStack->stackSize = pEquationStack->stackSize + 1;
			}
		}
		//Stack is NOT empty
		else
		{
			// Creating new pointers pointing on current value of the stack
			char** pCurrentEquationValue = pEquationStack->pCharValue;

			// Defining new dynamic pointers necessary to add new elements in the stack
			char** pNewEquationValue = NULL;

			// Allocating necessary memories for all previously created pointers
			pNewEquationValue = (char**)malloc(sizeof(char*) * (pEquationStack->stackSize + 1));

			// Checking if all pointers have been correctly allocated with memories
			if ((pNewEquationValue != NULL))
			{
				// Looping on existing elements
				int loop;
				for (loop = 0; loop < pEquationStack->stackSize; loop++)
				{
					pNewEquationValue[loop] = pCurrentEquationValue[loop];
				}

				// Allocating memories for adding the new elements
				pNewEquationValue[loop] = (char*)malloc(sizeof(char) * strLenEquationCharValue + 1);
				pNewEquationValue[loop] = pLocalEquationCharValue;

				// Affecting new elements in the stack
				pEquationStack->pCharValue = pNewEquationValue;
				pEquationStack->stackSize = pEquationStack->stackSize + 1;

				pCurrentEquationValue = NULL;
			}
			else
			{
				succes = FALSE;
			}
		}
	}

	return succes;
}



/*
Function to get last element given in the stack and removing it from the stack
*/
EquationPop popEquationValue(EquationStack* pEquationStack)
{
	// Defining a new struc to put removing from the stack element in this struc
	EquationPop result;

	// Checking if the stack is empty
	if (isEquationStackEmpty(pEquationStack) == TRUE)
	{
		result.success = FALSE;
		result.pCharValue = NULL;
	}
	// Stack is not empty
	else
	{
		// Getting all parameters of last element in the stack
		result.success = TRUE;
		result.pCharValue = pEquationStack->pCharValue[pEquationStack->stackSize - 1];

		// Creating a temporary pointers to get last element parameters
		char** pCurrentEquationValue = pEquationStack->pCharValue;

		// Calulating string lengths for all parameters in last element of the stack
		int strLenEquationValue;
		strLenEquationValue = strlen(pCurrentEquationValue);


		// Creating new dynamic pointers in order to put last element parameters in them
		char** pNewEquationValue = NULL;

		// Allocating necessary memories for previously defined pointers
		pNewEquationValue = (char**)malloc(sizeof(char*) * (pEquationStack->stackSize - 1));

		// Checking if memory allocations have been correctly done for all previously defined pointers
		if ((pNewEquationValue != NULL))
		{
			// Looping on existing elements
			int loop;
			for (loop = 0; loop < pEquationStack->stackSize - 1; loop++)
			{
				// Allocating memories for array of caracters
				pNewEquationValue[loop] = (char*)malloc(sizeof(char) * strLenEquationValue + 1);
				pNewEquationValue[loop] = pCurrentEquationValue[loop];
			}

			// Afecting new pointers to elements in stack
			pEquationStack->pCharValue = pNewEquationValue;

			pEquationStack->stackSize = pEquationStack->stackSize - 1;

			pCurrentEquationValue = NULL;

		}
		else
		{
			result.success = FALSE;
			result.pCharValue = NULL;

		}


	}

	return result;
}



/*
Function to display all elements and parameters in the built stack
*/
void displayEquationStack(const EquationStack* pEquationStack)
{

	int loop;
	if (isEquationStackEmpty(pEquationStack) == TRUE)
	{
		printf("The stack is empty\n");
	}
	else
	{
		for (loop = pEquationStack->stackSize - 1; loop >= 0; loop--)
		{
			printf("pCharValue[%d] = %s\n", loop, pEquationStack->pCharValue[loop]);
		}
	}


}


/*
Function to check if given string an integer or not, if the given string is an integer
a struc will be built with a corresponding integer value 
*/
IntegerCheck checkInteger(char* aString)
{
	//Specific struct
	IntegerCheck result;
	//Default value at FALSE
	result.checkResult = FALSE;

	//Comparing if given string is between 0 and 9 to define the corresponding integer
	if (strcmp(aString, "0") == 0)
	{
		result.pIntegerValue = 0;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "1") == 0)
	{
		result.pIntegerValue = 1;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "2") == 0)
	{
		result.pIntegerValue = 2;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "3") == 0)
	{
		result.pIntegerValue = 3;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "4") == 0)
	{
		result.pIntegerValue = 4;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "5") == 0)
	{
		result.pIntegerValue = 5;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "6") == 0)
	{
		result.pIntegerValue = 6;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "7") == 0)
	{
		result.pIntegerValue = 7;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "8") == 0)
	{
		result.pIntegerValue = 8;
		result.checkResult = TRUE;
	}
	else if (strcmp(aString, "9") == 0)
	{
		result.pIntegerValue = 9;
		result.checkResult = TRUE;
	}
	else
	{
		result.checkResult = FALSE;
	}


	return result;
}



/*
Function to get user inputs and put it in specific Stack
*/
EquationStack userInputInStack()
{
	//Stack to put user inputs
	EquationStack myUserInputInStack;

	//Stack initialization
	initEquationStack(&myUserInputInStack);

	//Allocating memory for buffer to be used to catch user entries
	char* equationBuffer = (char*)malloc(sizeof(char) * MAX_STR_SIZE);
	if (equationBuffer == NULL) {
		printf("No enough memory to allocate\n");
		myUserInputInStack.pCharValue = "FAILED";
		return myUserInputInStack;
	}

	//Asking to user to enter his equation
	printf("Enter your equation to compute:\n");
	
	//Using fgets to take in account spaces
	fgets(equationBuffer, MAX_STR_SIZE, stdin);

	//Specific buffer to be used to copy character by character in the stack
	char equationOneCharBuffer[2];

	//Getting size of given string by user
	int myEquationStrLen = strlen(equationBuffer);

	//To check if this is an integer or not
	IntegerCheck evalCharIfInt;

	//Looping on all chacacters 
	for (int loop = 0; loop < myEquationStrLen - 1; loop++)
	{
		//Buffers need for comutation
		//Buffer to concatanate numbers
		char bufferTmp[MAX_STR_SIZE] = "";
		//Buffer to copy simple element
		char bufferTmp2[MAX_STR_SIZE] = "";

		//While end condition, will be setted at 1 to end the loop
		int loopWhileEndFlag = 0;

		//Loop to concatate numbers: e.g. 1 2 3 => 123
		while (loopWhileEndFlag == 0)
		{
			//copying only one element
			strncpy(equationOneCharBuffer, &equationBuffer[loop], 1);
			//strncpy doesn't put \0 a the end, need to do it manually
			equationOneCharBuffer[1] = '\0';

			//Evaluating if current element is number or not
			evalCharIfInt = checkInteger(&equationOneCharBuffer);

			//If current element is a number, starting concatanation until current is not a number
			if (evalCharIfInt.checkResult == TRUE)
			{
				strcat(bufferTmp, equationOneCharBuffer);
				loop++;
			}
			//If current element is NOT a number, simply copying it in the buffer
			else
			{
				strcpy(bufferTmp2, equationOneCharBuffer);
				loopWhileEndFlag = 1;
			}
		}

		//Pushing all elements in the stack, one simple element if this not a number or concatanated number
		pushEquationValue(&myUserInputInStack, &bufferTmp);
		pushEquationValue(&myUserInputInStack, &bufferTmp2);



	}


	//Just to print a cleaned version of equation enterred by user on screen 
	char bufferTmp3[MAX_STR_SIZE] = "";

	int nbOfElemInMyUserInputInStack = myUserInputInStack.stackSize;

	for (int loop = 0; loop < nbOfElemInMyUserInputInStack; loop++)
	{
		strcat(bufferTmp3, myUserInputInStack.pCharValue[loop]);
		strcat(bufferTmp3, " ");
	}

	printf("\nYour equation to compute is: %s\n", bufferTmp3);

	return myUserInputInStack;
}



/*
Function to translate infix to postfix
*/
EquationStack inFixToPostFix(EquationStack* pUserInputInStack)
{
	//Stack to inverted given stack to have elements in right order
	EquationStack UserInputInStackInverted;
	//RPN stack to build
	EquationStack RPNStackInString;
	//Stack to manage only numbers or variables
	EquationStack myEquationStack;
	//Stack to manage only operators
	EquationStack myOperatorStack;

	//Initializing all defined stacks
	initEquationStack(&UserInputInStackInverted);
	initEquationStack(&RPNStackInString);
	initEquationStack(&myEquationStack);
	initEquationStack(&myOperatorStack);

	//Defining some pop structs necessary to process
	EquationPop UserInputInStackPop;
	EquationPop UserInputInStackInvertedPop;
	EquationPop OperatorStackPop;

	//buffer
	char bufferTmp[MAX_STR_SIZE] = "";

	//Looping on elements in given stack, poping element by element and put them in new stack
	//Nacessary to compute the RPN in right order
	int nbOfElemInUserInputInStack = pUserInputInStack->stackSize;
	for (int loop = 0; loop < nbOfElemInUserInputInStack; loop++)
	{
		UserInputInStackInvertedPop = popEquationValue(pUserInputInStack);
		strcpy(bufferTmp, UserInputInStackInvertedPop.pCharValue);
		pushEquationValue(&UserInputInStackInverted, &bufferTmp);
	}

	//Starting Algorithm to translate infix to postfix
	int nbOfElemInUserInputInStackInverted = UserInputInStackInverted.stackSize;
	for (int loop = 0; loop<nbOfElemInUserInputInStackInverted; loop++)
	{
		//Poping element in inverted stack
		UserInputInStackPop = popEquationValue(&UserInputInStackInverted);

		//If the stack is not empty, copying the current elment in a buffer
		if (UserInputInStackPop.success != FALSE)
		{
			strcpy(bufferTmp, UserInputInStackPop.pCharValue);
		}

		//If the current element is "(", simply bypass it
		if (strcmp(bufferTmp, "(") != 0)
		{
			//Look if the current element is an operator
			if ((strcmp(bufferTmp, "+") == 0)
				|| (strcmp(bufferTmp, "-") == 0)
				|| (strcmp(bufferTmp, "*") == 0)
				|| (strcmp(bufferTmp, "/") == 0))
			{
				//pushing the operator his specific stack
				pushEquationValue(&myOperatorStack, &bufferTmp);

				//Looking if the operator is "/", because of priority
				if ((strcmp(bufferTmp, "/") == 0))
				{
					//Looking next element, to see how to proceed
					UserInputInStackPop = popEquationValue(&UserInputInStackInverted);
					strcpy(bufferTmp, UserInputInStackPop.pCharValue);
					//Incrementing the loop
					loop++;

					//if the next element is a "(", doing nothing
					if ((strcmp(bufferTmp, "(") == 0))
					{
						//loop++;
					}
					else
					{
						//pushing element in RPN stack
						pushEquationValue(&RPNStackInString, &bufferTmp);

						//Only getting last element putted in operator stack
						int nbOfElemInOperatorStack = myOperatorStack.stackSize;
						for (int loop = 0; loop < 1; loop++)
						{
							OperatorStackPop = popEquationValue(&myOperatorStack);
							strcpy(bufferTmp, OperatorStackPop.pCharValue);
							pushEquationValue(&RPNStackInString, &bufferTmp);
						}
					}
				}
				//Looking if the operator is "*", because of priority
				else if ((strcmp(bufferTmp, "*") == 0))
				{
					//Looking next element, to see how to proceed
					UserInputInStackPop = popEquationValue(&UserInputInStackInverted);
					strcpy(bufferTmp, UserInputInStackPop.pCharValue);
					//Incrementing the loop
					loop++;

					if ((strcmp(bufferTmp, "(") == 0))
					{
						//loop++;
					}
					else
					{
						//pushing element in RPN stack
						pushEquationValue(&RPNStackInString, &bufferTmp);

						//Only getting last element putted in operator stack
						int nbOfElemInOperatorStack = myOperatorStack.stackSize;
						for (int loop = 0; loop < 1; loop++)
						{
							OperatorStackPop = popEquationValue(&myOperatorStack);
							strcpy(bufferTmp, OperatorStackPop.pCharValue);
							pushEquationValue(&RPNStackInString, &bufferTmp);
						}
					}
				}
				else
				{
					//Do nothing for the moment
				}

			}
			//Looking if current element is NOT ")", because of prority
			else if ((strcmp(bufferTmp, ")") != 0))
			{
				//pushing element in RPN stack
				pushEquationValue(&RPNStackInString, &bufferTmp);

			}
			//Looking if current element is ")", because of prority
			else if ((strcmp(bufferTmp, ")") == 0))
			{
				//Poping all elements in operator stack and put them in RPN stack
				int nbOfElemInOperatorStack = myOperatorStack.stackSize;
				for (int loop = 0; loop < nbOfElemInOperatorStack; loop++)
				{
					EquationPop OperatorStackPop = popEquationValue(&myOperatorStack);
					strcpy(bufferTmp, OperatorStackPop.pCharValue);
					pushEquationValue(&RPNStackInString, &bufferTmp);
				}
			}
			else
			{
				//Do Nothing
			}
		}


	}


	//Looping on all rest of stack Equation and Operators and putting them in RPN Stack
	int nbOfElemInEquationStack = myEquationStack.stackSize;
	for (int loop = 0; loop < nbOfElemInEquationStack; loop++)
	{
		EquationPop EquationStackPop = popEquationValue(&myEquationStack);
		strcpy(bufferTmp, EquationStackPop.pCharValue);
		pushEquationValue(&RPNStackInString, &bufferTmp);
	}

	int nbOfElemInOperatorStack = myOperatorStack.stackSize;
	for (int loop = 0; loop < nbOfElemInOperatorStack; loop++)
	{
		EquationPop OperatorStackPop = popEquationValue(&myOperatorStack);
		strcpy(bufferTmp, OperatorStackPop.pCharValue);
		pushEquationValue(&RPNStackInString, &bufferTmp);
	}

	//Just to print out on screen the processed RPN expression
	char bufferTmp3[MAX_STR_SIZE] = "";
	int nbOfElemInRPNStackInString = RPNStackInString.stackSize;
	for (int loop = 0; loop < nbOfElemInRPNStackInString; loop++)
	{
		strcat(bufferTmp3, RPNStackInString.pCharValue[loop]);
		strcat(bufferTmp3, " ");
	}

	printf("\nYour equation translated in \"Reversed Polish Notation\" is: %s\n", bufferTmp3);

	return RPNStackInString;


}



/*
Function to convert given string as double
*/
double convertStringToInt(char* aNumInString)
{
	//Getting length of string
	int strLenaNumInString;
	strLenaNumInString = strlen(aNumInString);
	
	//Will be used in sum need to be done to compute the number in string to number in double
	int expo = strLenaNumInString;

	//Buffer to be used in computation
	char aNumOneChar[2];

	//Specific struc to defined is current element is an interger or not
	IntegerCheck evalCharIfInt;

	double result = 0;

	//Looping on elements of given string
	for (int loop = 0; loop < strLenaNumInString; loop++)
	{
		//Exposant of 10, e.g. 10^1000 => pow(10,3)
		expo--;

		//Copying one char by char to process the conversion string to number
		strncpy(aNumOneChar, &aNumInString[loop], 1);
		//Need to /0 for strncpy
		aNumOneChar[1] = '\0';

		//Checking if current element is a number
		evalCharIfInt = checkInteger(&aNumOneChar);
		if (evalCharIfInt.checkResult == TRUE)
		{
			//Doing sum for conversion: e.g. "123" => 1*100 + 2*20 + 3*1
			result = result + evalCharIfInt.pIntegerValue*pow(10, expo);
		}

	}

	return result;
}



/*
Function to compute operations based on given numbers and operator
*/
double computeOperation(double aNum1, double aNum2, char* operator)
{
	double result = 0;

	if ((strcmp(operator, "+") == 0))
	{
		//printf("Debug in +\n");
		result = aNum2 + aNum1;
	}
	else if (((strcmp(operator, "-") == 0)))
	{
		//printf("Debug in -\n");
		result = aNum2 - aNum1;
	}
	else if (((strcmp(operator, "*") == 0)))
	{
		//printf("Debug in *\n");
		result = aNum2 * aNum1;
	}
	else if (((strcmp(operator, "/") == 0)))
	{
		//printf("Debug in /\n");
		result = aNum2 / aNum1;
	}
	else
	{
		printf("Operator \"%s\" not defined !\n", operator);
	}

	return result;
}



/*
Function to compute the RPN
*/
double computeRPN(EquationStack* pRPNStackInString)
{
	//Defining RPN Stack
	RPNStack myRPNStack;
	//Defining Equation, necessary to inver given stack to proceed in right order
	EquationStack RPNStackInStringInverted;

	//Initializing all stacks
	initRPNStack(&myRPNStack);
	initEquationStack(&RPNStackInStringInverted);

	//Definig Pop varibales
	EquationPop RPNStackInStringInvertedPop;
	RPNPop myRPNStackPop;

	//Defining necessary buffers for computation
	char bufferTmp[MAX_STR_SIZE] = "";
	char myOpeator[2];

	//Looping all elements of given stack to pop them one by one, 
	//and to put them in new stack, necessary to have elements
	//in right order to process the polish
	int nbOfElemInRPNStackInString = pRPNStackInString->stackSize;
	for (int loop = 0; loop < nbOfElemInRPNStackInString; loop++)
	{
		RPNStackInStringInvertedPop = popEquationValue(pRPNStackInString);
		strcpy(bufferTmp, RPNStackInStringInvertedPop.pCharValue);
		pushEquationValue(&RPNStackInStringInverted, &bufferTmp);
	}

	//While stop condition, will be setted at 1 to get out of the loop
	int stopWhile = 0;

	//Looping on elements on the RPN stack
	while (stopWhile == 0)
	{
		//Poping element for RNP stack
		RPNStackInStringInvertedPop = popEquationValue(&RPNStackInStringInverted);
		
		//If the poped element is not empty
		if (RPNStackInStringInvertedPop.success == TRUE)
		{
			//Copying the current element in a buffer to process
			strcpy(bufferTmp, RPNStackInStringInvertedPop.pCharValue);

			//Checking if the current element is an operator
			//to compute the operation
			if ((strcmp(bufferTmp, "+") == 0)
				|| (strcmp(bufferTmp, "-") == 0)
				|| (strcmp(bufferTmp, "*") == 0)
				|| (strcmp(bufferTmp, "/") == 0))
			{
				//Poping the last 2 elements to proccess the computation
				myRPNStackPop = popRPNValue(&myRPNStack);
				double myNum1 = myRPNStackPop.doubleValue;
				myRPNStackPop = popRPNValue(&myRPNStack);
				double myNum2 = myRPNStackPop.doubleValue;

				//Performing the operation
				double tmpResult = computeOperation(myNum1, myNum2, &bufferTmp);

				//Pushing the result of the operation the RPN stack
				pushRPNValue(&myRPNStack, tmpResult);
			}
			//If the current element is not an operator push it in the stack
			else
			{
				double myNumToPush = convertStringToInt(&bufferTmp);
				pushRPNValue(&myRPNStack, myNumToPush);
			}
		}
		else
		{
			//Stopping loop if the stack is empty
			stopWhile = 1;
		}
	}

	//Poping last element in the stack which is the final result
	myRPNStackPop = popRPNValue(&myRPNStack);
	double result = myRPNStackPop.doubleValue;

	return result;
}



/*
Function to evaluate the user input variables
Double iteration to avoid redondant question to user if the variable is already defined
*/
EquationStack userVariablesEvalution(EquationStack* pUserInputInStack)
{
	//Stack to invert given stack, necessary to compute elements in right order
	EquationStack userInputInStackInverted;
	//Same as previous one, but need it the second iteration
	EquationStack userInputInStackInverted2;
	//New stack with variables replaced with their values
	EquationStack userEvaluatedStack;
	//Stack to store user's given variables
	EquationStack myVariablesStack;
	//Stack to store user's given values for variables
	EquationStack myVariablesValuesStack;

	//Initializing all stacks
	initEquationStack(&userInputInStackInverted);
	initEquationStack(&userInputInStackInverted2);
	initEquationStack(&userEvaluatedStack);
	initEquationStack(&myVariablesStack);
	initEquationStack(&myVariablesValuesStack);

	//Defining all pop varibales
	EquationPop userInputInStackInvertedPop;
	EquationPop userInputInStackInvertedPop2;
	EquationPop userEvaluatedStackPop;
	EquationPop myVariablesStackPop;
	EquationPop myVariablesValuesStackPop;

	//Defining some buffers necessary for computation
	char bufferTmp[MAX_STR_SIZE] = "";
	char bufferTmp2[MAX_STR_SIZE] = "";
	char bufferTmp3[MAX_STR_SIZE] = "";
	char userVarBufferTmp[MAX_STR_SIZE] = "";

	//Looping on elements of given stack to invert order
	int nbOfElemInUserInputInStack = pUserInputInStack->stackSize;
	for (int loop = 0; loop < nbOfElemInUserInputInStack; loop++)
	{
		userInputInStackInvertedPop = popEquationValue(pUserInputInStack);
		strcpy(bufferTmp, userInputInStackInvertedPop.pCharValue);

		pushEquationValue(&userInputInStackInverted, &bufferTmp);
		pushEquationValue(&userInputInStackInverted2, &bufferTmp);
	}


	//Looping on elements of inverted stack
	int nbOfElemInUserInputInStackInverted = userInputInStackInverted.stackSize;
	for (int loop = 0; loop < nbOfElemInUserInputInStack; loop++)
	{
		//Poping element from the stack
		userInputInStackInvertedPop = popEquationValue(&userInputInStackInverted);

		//If the stack is not empty
		if (userInputInStackInvertedPop.success == TRUE)
		{
			//Copying the current element in a buffer
			strcpy(bufferTmp, userInputInStackInvertedPop.pCharValue);
			
			//Size of current string
			int myBuffferLen = strlen(bufferTmp);
			//Flag used to check if this is a variable, will be setted at 1 if this a variable
			int charFlag = 0;
			//Flag used to check if the variable already exists
			int charAlreadyPresentFlag = 1;

			//Looping on string 
			for (int loop = 0; loop < myBuffferLen; loop++)
			{
				//If the current element is character between a and z or A and Z, this is defined as a variable
				if ((bufferTmp[0] >= 'a' && bufferTmp[0] <= 'z') || (bufferTmp[0] >= 'A' && bufferTmp[0] <= 'Z'))
				{
					charFlag = 1;
				}
			}

			//If the current element is variable
			if (charFlag == 1)
			{
				//Looping on elements of variable stack, to check if the variable is already defined
				int nbOfElemInMyVariablesStack = myVariablesStack.stackSize;
				//Process only if the stack is not empty
				if (nbOfElemInMyVariablesStack > 0)
				{
					for (int loop = 0; loop < nbOfElemInMyVariablesStack; loop++)
					{
						//Comparing current variable to variable already in stack 
						strcpy(bufferTmp2, myVariablesStack.pCharValue[loop]);

						if ((strcmp(bufferTmp, bufferTmp2) == 0))
						{
							//If the variable is already in stack, exit the loop
							charAlreadyPresentFlag = 0;
							break;
						}
					}

					//If the varible is not detected in previous step, push in variable stack
					if (charAlreadyPresentFlag == 1)
					{
						pushEquationValue(&myVariablesStack, &bufferTmp);
					}
				}
				else
				{
					pushEquationValue(&myVariablesStack, &bufferTmp);
				}
			}
		}
	}

	//Looping on all stored variables in stack to ask about their values to user
	int nbOfElemInMyVariablesStack = myVariablesStack.stackSize;
	for (int loop = 0; loop < nbOfElemInMyVariablesStack; loop++)
	{
		strcpy(bufferTmp, myVariablesStack.pCharValue[loop]);
		printf("\nEnter your value for your variable \"%s\" (only INTEGER, and no negative value): ", bufferTmp);
		scanf("%s", &bufferTmp);

		//Pushing variables values given by user in the stack
		pushEquationValue(&myVariablesValuesStack, &bufferTmp);
	}

	//Looping again on the second inverted stack, because the fisrt one is now empty after the previous computation
	//to replace variables by their values
	for (int loop = 0; loop < nbOfElemInUserInputInStack; loop++)
	{
		//Poping the element in the stack
		userInputInStackInvertedPop = popEquationValue(&userInputInStackInverted2);

		//if the stack is not empty
		if (userInputInStackInvertedPop.success == TRUE)
		{
			//Copying the current element in buffer to process
			strcpy(bufferTmp, userInputInStackInvertedPop.pCharValue);

			//Same as previous iteration
			int myBuffferLen = strlen(bufferTmp);
			int charFlag = 0;
			int charAlreadyPresentFlag = 1;

			//Checking if the current element is variable or not
			for (int loop = 0; loop < myBuffferLen; loop++)
			{
				if ((bufferTmp[0] >= 'a' && bufferTmp[0] <= 'z') || (bufferTmp[0] >= 'A' && bufferTmp[0] <= 'Z'))
				{
					charFlag = 1;
				}
			}

			//If the current element is a variable
			if (charFlag == 1)
			{
				//Looping on all variables in varibles stack
				int nbOfElemInMyVariablesStack = myVariablesStack.stackSize;
				//If the variables stack is not empty
				if (nbOfElemInMyVariablesStack > 0)
				{
					for (int loop = 0; loop < nbOfElemInMyVariablesStack; loop++)
					{
						//Comparing the variable and replacing it final stack 
						strcpy(bufferTmp2, myVariablesStack.pCharValue[loop]);
						strcpy(bufferTmp3, myVariablesValuesStack.pCharValue[loop]);

						if ((strcmp(bufferTmp, bufferTmp2) == 0))
						{
							pushEquationValue(&userEvaluatedStack, &bufferTmp3);
						}
					}
				}
			}
			else
			{
				pushEquationValue(&userEvaluatedStack, &bufferTmp);
			}
		}

	}



	return userEvaluatedStack;

}

