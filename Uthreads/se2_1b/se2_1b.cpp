// se2_1d.cpp : Tests function BOOL UtAlive(HANDLE thread)
//

#include "stdafx.h"
#include "..\Include\USynch.h"
#include "..\Include\List.h"
#include <crtdbg.h>
#include <stdio.h>
#include "..\Include\Uthread.h"

#define MAX_THREADS 3

VOID PrintUtThreadAlive(HANDLE handle[]);
ULONG Test1_Count;
HANDLE handleArray[MAX_THREADS];


VOID PrintUtThreadAlive(HANDLE handle[]) {
	ULONG Index;
	for (Index = 0; Index < MAX_THREADS; ++Index) {
		printf("Client %d:  %d  (1-Alive; 0-Dead)", Index, UtAlive(handle[Index]));
		printf("\n");
	}
	getchar();
}

VOID Test1_Thread(UT_ARGUMENT Argument) {
	UCHAR Char;
	ULONG Index;
	Char = (UCHAR)Argument;

	for (Index = 0; Index < 7; ++Index) {
		putchar(Char);

		printf("Print Threads State Before UtYield() \n");
		PrintUtThreadAlive(handleArray);

		if ((rand() % 4) == 0) {
			UtYield();

			printf("Print Threads State After UtYield() \n");
			PrintUtThreadAlive(handleArray);
		}
	}
	++Test1_Count;

}

VOID Test1() {
	ULONG Index;
	Test1_Count = 0;

	printf("\n :: Test 1 b) - BEGIN :: \n\n");

	for (Index = 0; Index < MAX_THREADS; ++Index) {
		handleArray[Index] = UtCreate(Test1_Thread, (UT_ARGUMENT)('0' + Index));
	}

	printf("Print Threads Alive \n");
	PrintUtThreadAlive(handleArray);

	UtRun();

	_ASSERTE(Test1_Count == MAX_THREADS);
	printf("\n\n :: Test 1 b) - END :: \n");
}

int main() {
	UtInit();

	Test1();

	printf("Press any key to finish");
	getchar();


	UtEnd();
	return 0;
}

