#include <stdio.h>
#include <time.h>
#include <thread>
#include <iostream>	
#include <vector>

static long long int iterCnt = 1000000;
	
void comupteRolls(long long int &a, long long int &d)
{
	int rolls[2];

	for (int i = 0; i < iterCnt; i++) {
		rolls[0] = rand() % 20 + 1;
		rolls[1] = rand() % 20 + 1;
		a += rolls[0] > rolls[1] ? rolls[0] : rolls[1];
		d += rolls[0] < rolls[1] ? rolls[0] : rolls[1];
	}
}

int main() {
	srand(time(NULL));

	std::vector<std::thread> threads;
	int threadNum = 16;
	long long int sumAdv = 0;
	long long int sumDadv = 0;

	std::vector<long long int> buffer1(threadNum, 0);
	std::vector<long long int> buffer2(threadNum, 0);

	for (int i = 0; i < threadNum; i++)
	{
		threads.push_back(std::thread(comupteRolls, std::ref(buffer1[i]), std::ref(buffer2[i])));
	}
	
	for (std::thread& t : threads)
	{
		if (t.joinable()) 
		{
			t.join();
		}
	}
	
	for (int i = 0; i < threadNum; i++)
	{
		sumAdv += buffer1[i];
		sumDadv += buffer2[i];
	}

	double advantageExpextedRoll = (double)sumAdv / ((double)iterCnt * threadNum);
	double disadvantageExpextedRoll = (double)sumDadv / ((double)iterCnt * threadNum);

	printf("Advantage expected roll: %f (Diff: %f)\n", advantageExpextedRoll, advantageExpextedRoll - 10.5f);
	printf("Disadvantage expected roll: %f (Diff: %f)\n", disadvantageExpextedRoll, 10.5f - disadvantageExpextedRoll);
}
