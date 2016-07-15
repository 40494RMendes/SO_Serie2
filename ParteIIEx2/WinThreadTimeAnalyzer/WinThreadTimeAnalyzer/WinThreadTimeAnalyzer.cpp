#include<windows.h>
#include<stdio.h>

#define MAX_THREADS 1606

LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
LARGE_INTEGER Frequency;
HANDLE hThreads[MAX_THREADS];

VOID func(){}

VOID testCreationTimes() {
	printf("*** Testing Thread Creation Times ***\n");

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < MAX_THREADS; i++) {
		hThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, NULL, CREATE_SUSPENDED, NULL);
	}

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	printf("\n\tPerformance Stats:\n");
	printf("\t-> Total Threads Creation Time: %d MicroSeconds\n", ElapsedMicroseconds);
	printf("\t-> Average Thread Creation Time: %d MicroSeconds\n", ElapsedMicroseconds.QuadPart / MAX_THREADS);
}

VOID testDestructionTimes() {
	printf("*** Testing Thread Destruction Times ***\n");

	DWORD ExitCode;
	PDWORD PExitCode = &ExitCode;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < MAX_THREADS; i++) {
		GetExitCodeThread(hThreads[i], PExitCode);
		TerminateThread(hThreads[i], ExitCode);
	}

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	printf("\n\tPerformance Stats:\n");
	printf("\t-> Total Threads Destruction Time: %d MicroSeconds\n", ElapsedMicroseconds);
	printf("\t-> Average Thread Destruction Time: %d MicroSeconds\n", ElapsedMicroseconds.QuadPart / MAX_THREADS);
}

int main(VOID) {

	testCreationTimes();

	getchar();

	testDestructionTimes();

	getchar();

	for (int i = 0; i < MAX_THREADS; i++) {
		CloseHandle(hThreads[i]);
	}
}