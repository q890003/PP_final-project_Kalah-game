#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;


int times = 0;
int ii = 0;


int listSuccessors(int house[], int successor[], bool isMaxPlayer)
{
	int i, start, end, count = 0;
	if (isMaxPlayer == 0)
	{
		start = 0; end = 5;
		for (i = start; i <= end; i++)
		{
			if (house[i] != 0)
			{
				successor[count] = i;
				count++;
			}
		}

		/*printf("%d [", count);
		for (i = 0; i < count - 1; i++)
		{
		printf("%d ", successor[i]);
		}
		printf("%d]", successor[count - 1]);
		printf("\n");*/
		return count;
	}
	else //if (isMaxPlayer == 1)
	{
		start = 7; end = 12;
		for (i = start; i <= end; i++)
		{
			if (house[i] != 0)
			{
				successor[count] = i;
				count++;
			}
		}

		/*printf("%d [", count);
		for (i = 0; i < count - 1; i++)
		{
		printf("%d ", successor[i]);
		}
		printf("%d]", successor[count - 1]);
		printf("\n");*/
		return count;
	}
}


//struct linkHouses {
//	int houses[14];
//	linkHouses *next[6];
//};

const int houseLength = 14;

bool relocation(int nowHouse[], int pickedHouse, int nextHouse[]) {
	int houseIndex[] = { houseLength / 2 - 1, houseLength - 1 };
	int myHouse = pickedHouse / 7;
	int left = nowHouse[pickedHouse];
	int goHouse = pickedHouse + 1;

	for (int i = 0; i < houseLength; i++) {
		if (i == pickedHouse) {
			nextHouse[i] = 0;
			continue;
		}
		nextHouse[i] = nowHouse[i];
	}

	while (left) {
		goHouse = goHouse % houseLength;
		if (goHouse != houseIndex[!myHouse]) {
			nextHouse[goHouse]++;
			left--;
		}
		goHouse++;
	} goHouse--;

	int oppsite = houseLength - 2 - goHouse;
	if (oppsite != houseIndex[0] && oppsite != houseIndex[1])
		if (goHouse / 7 == myHouse)
			if (nextHouse[goHouse] == 1 && nextHouse[oppsite] > 0) {
				nextHouse[houseIndex[myHouse]] += nextHouse[goHouse] + nextHouse[oppsite];
				nextHouse[goHouse] = nextHouse[oppsite] = 0;
			}

	if (goHouse == houseIndex[myHouse])
		return true;
	return false;
}


int evaluate(int house[])
{
	int value;
	value = house[13] - house[6];
	return value;
}


void finalScoring(int house[])
{
	int i, tmp;
	for (i = 0; i < 13; i++)
	{
		if (i == 6)
		{
			continue;
		}
		if (house[i] != 0 && i<6)
		{
			tmp = house[i];
			house[i] = 0;
			house[6] += tmp;
		}
		else if (house[i] != 0 && i > 6)
		{
			tmp = house[i];
			house[i] = 0;
			house[13] += tmp;
		}
	}
	/*printf("[");
	for (i = 0; i < 13; i++)
	{
	printf("%d ", house[i]);
	}
	printf("%d]\n", house[13]);*/

}


/*class listHouse2
{
public:
int mValue = 0;
vector<listHouse2> next[6];

listHouse2(int inputHouses[14], int depthMAX, int nowDepth, bool isMaxPlayer, bool canRelocation)
{
//printf("\n");


if (nowDepth == depthMAX)
{
mValue = evaluate(inputHouses);
if (nowDepth <= 1)
//if (true)
{
printf("the expanded node is at the depth of depthMAX\n"); //print
printf("depth = %d, mValue = %d, houses = ", nowDepth, mValue); //print
for (int i = 0; i <= 13; i++)
{
if (i == 6 || i == 13)
printf("[%d] ", inputHouses[i]);

else
printf("%d ", inputHouses[i]);
}
printf("\n");
}
return;
}


int successor[14] = { 0 };
int number_of_possible_actions;
number_of_possible_actions = listSuccessors(inputHouses, successor, isMaxPlayer); //listSuccessors
if (number_of_possible_actions == 0)											  //there is no successor
{
finalScoring(inputHouses);
mValue = evaluate(inputHouses);
if (nowDepth <= 1)
//if (true)
{
printf("there is no successor\n"); //print
printf("depth = %d, mValue = %d, houses = ", nowDepth, mValue); //print
for (int i = 0; i <= 13; i++)
{
if (i == 6 || i == 13)
printf("[%d] ", inputHouses[i]);

else
printf("%d ", inputHouses[i]);
}
printf("\n");
}
return;
}


int relocationHouses[6][14];
bool seed_fall_in_player_store[6];
if (canRelocation == true)
{
for (int i = 0; i < number_of_possible_actions; i++) {                            //relocation
seed_fall_in_player_store[i] = relocation(inputHouses, successor[i], relocationHouses[i]);
}
}
else
{
for (int i = 0; i < number_of_possible_actions; i++) {                            //relocation
for (int j = 0; j <= 13; j++) {
relocationHouses[i][j] = inputHouses[j];
}
}
}


for (int i = 0; i < number_of_possible_actions; i++)			//將 next[6] 一一指向下一個 listHouse2
{
if (seed_fall_in_player_store[i] == true)
{
next[i].push_back(listHouse2(relocationHouses[i], depthMAX, nowDepth + 1, !isMaxPlayer, false));//如果 final seed 掉在得分盤裡isMaxPlayer不變
}
else
{
next[i].push_back(listHouse2(relocationHouses[i], depthMAX, nowDepth + 1, !isMaxPlayer, true));//如果 final seed 沒掉在得分盤裡，傳入 [ ! isMaxPlayer]
}
}


//int bestActionIndex = number_of_possible_actions - 1;
//mValue = next[number_of_possible_actions - 1][0].mValue;
//if (player == true)						//get mValue
//{
//	for (int i = number_of_possible_actions - 1; i >= 0; i--)
//	{
//		if (next[i][0].mValue > mValue)
//		{
//			mValue = next[i][0].mValue;
//			bestActionIndex = i;
//		}
//	}
//}
//else
//{
//	for (int i = number_of_possible_actions - 1; i <= 0; i--)
//	{
//		if (next[i][0].mValue < mValue)
//		{
//			mValue = next[i][0].mValue;
//			bestActionIndex = i;
//		}
//	}
//}
int bestActionIndex = 0;
mValue = next[0][0].mValue;
if (isMaxPlayer == true)						//get mValue
{
for (int i = 0; i < number_of_possible_actions; i++)
{
if (next[i][0].mValue > mValue)
{
mValue = next[i][0].mValue;
bestActionIndex = i;
}
}
}
else
{
for (int i = 0; i < number_of_possible_actions; i++)
{
if (next[i][0].mValue < mValue)
{
mValue = next[i][0].mValue;
bestActionIndex = i;
}
}
}

if (nowDepth <= 1)
//if (true)
{
printf("depth = %d, mValue = %d, houses = ", nowDepth, mValue); //print
for (int i = 0; i <= 13; i++)
{
if (i == 6 || i == 13)
printf("[%d] ", inputHouses[i]);

else
printf("%d ", inputHouses[i]);
}
printf(", Best action is %d", successor[bestActionIndex]);
printf("\n");
}
}


~listHouse2() {}


};*/


void listHouse3(int inputHouses[14], int depthMAX, int nowDepth, bool isMaxPlayer, bool canRelocation, int *mValue)
{
	//printf("\n");
	int mValue_of_successor[6] = { 0 };

	if (nowDepth >= depthMAX)
	{
		*mValue = evaluate(inputHouses);
		if (nowDepth <= 1)
			//if (true)
		{
			printf("the expanded node is at the depth of depthMAX\n"); //print
			printf("depth = %d, *mValue = %d, houses = ", nowDepth, *mValue); //print
			for (int i = 0; i <= 13; i++)
			{
				if (i == 6 || i == 13)
					printf("[%d] ", inputHouses[i]);

				else
					printf("%d ", inputHouses[i]);
			}
			printf("\n");
		}
		return;
	}


	int successor[14] = { 0 };
	int number_of_possible_actions = 0;
	number_of_possible_actions = listSuccessors(inputHouses, successor, isMaxPlayer); //listSuccessors
	if (number_of_possible_actions <= 0)											  //there is no successor
	{
		finalScoring(inputHouses);
		*mValue = evaluate(inputHouses);
		if (nowDepth <= 1)
			//if (true)
		{
			printf("there is no successor\n"); //print
			printf("depth = %d, *mValue = %d, houses = ", nowDepth, *mValue); //print
			for (int i = 0; i <= 13; i++)
			{
				if (i == 6 || i == 13)
					printf("[%d] ", inputHouses[i]);

				else
					printf("%d ", inputHouses[i]);
			}
			printf("\n");
		}
		return;
	}


	int relocationHouses[6][14];
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 13; j++)
		{
			relocationHouses[i][j] = 0;
		}
	}
	bool seed_fall_in_player_store[6] = { 0 };
	if (canRelocation)
	{
		for (int i = 0; i < number_of_possible_actions; i++) {                            //relocation
			seed_fall_in_player_store[i] = relocation(inputHouses, successor[i], relocationHouses[i]);
		}
	}
	else
	{
		for (int i = 0; i < number_of_possible_actions; i++) {                            //relocation
			for (int j = 0; j <= 13; j++) {
				relocationHouses[i][j] = inputHouses[j];
			}
		}
	}


	for (int i = 0; i < number_of_possible_actions; i++)
	{
		if (seed_fall_in_player_store[i])
		{
			listHouse3(relocationHouses[i], depthMAX, nowDepth + 2, isMaxPlayer, true, &mValue_of_successor[i]);
		}
		else
		{
			listHouse3(relocationHouses[i], depthMAX, nowDepth + 1, !isMaxPlayer, true, &mValue_of_successor[i]);
		}
	}


	//int bestActionIndex = number_of_possible_actions - 1;
	//*mValue = next[number_of_possible_actions - 1][0].mValue;
	//if (player == true)						//get mValue //
	//{
	//	for (int i = number_of_possible_actions - 1; i >= 0; i--)
	//	{
	//		if (next[i][0].*mValue > mValue)
	//		{
	//			*mValue = next[i][0].mValue;
	//			bestActionIndex = i;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int i = number_of_possible_actions - 1; i <= 0; i--)
	//	{
	//		if (next[i][0].*mValue < mValue)
	//		{
	//			*mValue = next[i][0].mValue;
	//			bestActionIndex = i;
	//		}
	//	}
	//}
	int bestActionIndex = 0;
	*mValue = mValue_of_successor[0];
	if (isMaxPlayer == true)						//get mValue
	{
		for (int i = 0; i < number_of_possible_actions; i++)
		{
			if (mValue_of_successor[i] > *mValue)
			{
				*mValue = mValue_of_successor[i];
				bestActionIndex = i;
			}
		}
	}
	else
	{
		for (int i = 0; i < number_of_possible_actions; i++)
		{
			if (mValue_of_successor[i] < *mValue)
			{
				*mValue = mValue_of_successor[i];
				bestActionIndex = i;
			}
		}
	}
	/*if (nowDepth < 100)
	{

	printf("depth = %d, house#%d, %s (%d) [%d", nowDepth, successor[bestActionIndex], isMaxPlayer ? "max" : "min", *mValue, inputHouses[0]);
	for (int i = 1; i < 14; i++)
	if (i == 6 || i == 13)
	printf(" (%d)", inputHouses[i]);
	else
	{
	printf(" %d", inputHouses[i]);

	}
	printf("]\n");
	}*/
	/*if (nowDepth <= 1)
	//if (true)
	{
	printf("depth = %d, *mValue = %d, houses = ", nowDepth, *mValue); //print
	for (int i = 0; i <= 13; i++)
	{
	if (i == 6 || i == 13)
	printf("[%d] ", inputHouses[i]);

	else
	printf("%d ", inputHouses[i]);
	}
	printf(", Best action is %d", successor[bestActionIndex]);
	printf("\n");
	}*/
	if (nowDepth == 0 && ii < times - 1) {
		//printf("%d\n", successor[bestActionIndex]);
		cout << successor[bestActionIndex]<< endl;
	}
	else if (nowDepth == 0 && ii == times - 1) {
		//printf("%d", successor[bestActionIndex]);
		cout << successor[bestActionIndex];
	}
}

int main()
{
	//int depthMAX, nowDepth = 0, inputHouses[14], successor[14] = { 0 };     //value = return value
	//value = return value

	//bool isMaxPlayer = true;
	//vector<listHouse2> listHouse;
	//list<listHouse2>::iterator _iterator = listHouse.begin();

	scanf("%d", &times);
	for (ii = 0; ii < times; ii++)
	{
		int depthMAX, inputHouses[14], mValue = 0;
		int *p;
		p = &mValue;

		for (int j = 0; j < 14; j++)
		{
			scanf("%d", &inputHouses[j]);
		}
		scanf("%d", &depthMAX);


		//bool canRelocation = true;
		//listHouse.push_back( listHouse2(inputHouses, depthMAX, nowDepth, isMaxPlayer, canRelocation) );

		listHouse3(inputHouses, depthMAX, 0, true, true, p);//listHouse3(int inputHouses[14], int depthMAX, int nowDepth, bool isMaxPlayer, bool canRelocation, int mValue)
	}

	/*int i = 0, MAX;
	MAX = listHouse[0].next[0][0].mValue;
	for (i = 0; i < 5; i++)
	{
	if (listHouse[0].next[0][0].mValue > MAX)
	MAX = listHouse[0].next[0][0].mValue;
	}
	printf("\n\n\nroot's mValue = %d, MAX = %d, Best action is %d", listHouse[0].mValue, MAX, i + 8);*/






	printf("\n");
	return 0;
}//7 0 5 6 10 9 4 5 4 2 3 0 11 6
 //4->10
 //6->7
 //ALL 10