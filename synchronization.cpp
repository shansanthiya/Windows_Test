#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 2

HANDLE mu;

DWORD WINAPI mutex_thread_test(LPVOID);

int main(void)
{
	HANDLE th[THREADCOUNT];
	DWORD thID;
	int i;

	mu = CreateMutex(NULL, FALSE, NULL);            

	for (i = 0; i < THREADCOUNT; i++)
	{
		th[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mutex_thread_test, NULL, 0, &thID); 

	}

	WaitForMultipleObjects(THREADCOUNT, th, TRUE, INFINITE);

	for (i = 0; i < THREADCOUNT; i++)
		CloseHandle(th[i]);

	CloseHandle(mu);

	return 0;
}

DWORD WINAPI mutex_thread_test(LPVOID lpParam)
{
	DWORD count = 0;
	DWORD waitResult;
	
	while (count < 10)
	{
		waitResult = WaitForSingleObject(mu, INFINITE); 

		printf("Thread %d writing \n", GetCurrentThreadId());
		count++;
	
		ReleaseMutex(mu);

	}
	return TRUE;
}
