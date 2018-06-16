#pragma once
#include <stdio.h>
#include <math.h>


// Defining boolean TRUE
#ifndef TRUE
#define TRUE 0
#endif


// Defining boolean FALSE
#ifndef FALSE
#define FALSE 1
#endif

// Defining new type boolean
typedef int BOOL;


// Defining max string 
#define MAX_STR_SIZE 256


// Struct to define equation stack in string
typedef struct
{
	char** pCharValue; 
	int stackSize; 
} EquationStack;


// Struct to define equation pop value stack in string
typedef struct {
	char* pCharValue; 
	BOOL success; 
} EquationPop;


// Struct to define equation stack in double
typedef struct
{
	double* pDoubleValue; 
	int stackSize; 
} RPNStack;


// Struct to define equation pop value in double
typedef struct {
	double doubleValue; 
	BOOL success; 
} RPNPop;


// Struc to check if given string is a number
typedef struct
{
	int pIntegerValue; 
	BOOL checkResult; 
} IntegerCheck;



// Functions signatures
void initEquationStack(EquationStack* pRPNStack);
void destroyEquationStack(EquationStack* pRPNStack);
BOOL isEquationStackEmpty(EquationStack* pRPNStack);
void initRPNStack(RPNStack* pRPNStack);
void destroyRPNStack(RPNStack* pRPNStack);
BOOL isRPNStackEmpty(RPNStack* pRPNStack);
BOOL pushEquationValue(EquationStack* pEquationStack, char* pEquationCharValue);
EquationPop popEquationValue(EquationStack* pEquationStack);
BOOL pushRPNValue(RPNStack* pRPNStack, double RPNIntValue);
RPNPop popRPNValue(RPNStack* pRPNStack);
void displayRPNStack(const RPNStack* pRPNStack);
IntegerCheck checkInteger(char* aString);
EquationStack inFixToPostFix(EquationStack* pUserInputInStack);
EquationStack userInputInStack();
double computeRPN(EquationStack* pRPNStack);
double convertStringToInt(char* aNumInString);
double computeOperation(double aNum1, double aNum2, char* operator);
EquationStack userVariablesEvalution(EquationStack* pUserInputInStack);

