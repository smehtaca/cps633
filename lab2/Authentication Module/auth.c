#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLINE 100

typedef struct userData
{
	int first_keyCode;
	int second_keyCode;
	int flyTime;
	int first_dwellTime;
	int second_dwellTime;
} userData;

const int size = 500;
const int threshold = 40;
const int userSize = 5;

//Select file for desired user
FILE *chooseUser(int user)
{
	char line[20];
	switch(user)
	{
		case 1 : strcpy(line, "Users/User1.txt"); break;
		case 2 : strcpy(line, "Users/User2.txt"); break;
		case 3 : strcpy(line, "Users/User3.txt"); break;
		case 4 : strcpy(line, "Users/User4.txt"); break;
		case 5 : strcpy(line, "Users/User5.txt"); break;
	}
	FILE *read = fopen(line, "r");
	return read;
}


userData *createData(userData data)
{
	userData *created = (userData*) malloc(sizeof(userData));
	created->first_keyCode = data.first_keyCode;
	created->second_keyCode = data.second_keyCode;
	created->flyTime = data.flyTime;
	created->first_dwellTime = data.first_dwellTime;
	created->second_dwellTime = data.second_dwellTime;
	return created;
}

//Reads data from file and stores in userData structure
void readData(FILE *read, userData data[][size])
{
	int x = 0;
	char line[MAXLINE];
	fseek(read, 86, 0);
	while(fgets(line, MAXLINE, read) != NULL)
	{
		int key1 = atoi(strtok(line, "\t"));
		int key2 = atoi(strtok(NULL, "\t"));
		int fly = atoi(strtok(NULL, "\t"));
		int dwell1 = atoi(strtok(NULL, "\t"));
		int dwell2 = atoi(strtok(NULL, "\t"));
		userData newData = {key1, key2, fly, dwell1, dwell2};
		if(x < size)
			data[0][x] = newData;
		else if(x < 2*size)
			data[1][x-size] = newData;
		else if(x < 3*size)
			data[2][x-2*size] = newData;
		else if(x < 4*size)
			data[3][x-3*size] = newData;
		else if(x < 5*size)
			data[4][x-4*size] = newData;
		else if(x < 6*size)
			data[5][x-5*size] = newData;
		x++;
	}
}

//Calculates the deviation from the user's keyboard input
double deviation(int n, userData tRef[], userData tMon[])
{
	int x;
	double dev = 0, di = 0, mono = 0;
	for(x = 0; x < n; x++)
	{
		if(tMon[x].flyTime)
			di += abs(tRef[x].flyTime - tMon[x].flyTime)/tMon[x].flyTime;
		if(tMon[x].first_dwellTime && x < n-1)
			mono += abs(tRef[x].first_dwellTime - tMon[x].first_dwellTime)/tMon[x].first_dwellTime;
	}
	dev = (di/(n-1))+(mono/(n));
	return dev*50;
}

//If deviation is too high, return 1
int falseReject(double dev)
{
	if(dev >= threshold)
		return 1;
	return 0;
}

//If deviation lis too low, return 1
int falseAccept(double dev)
{
	if(dev <= threshold)
		return 1;
	return 0;
}

int calculateEER(double dev[])
{
	double one = falseReject(dev[0]);
	double two = falseReject(dev[1]);
	double three = falseReject(dev[2]);
	double four = falseReject(dev[3]);
	double five = falseReject(dev[4]);
	printf("False Reject: [%f, %f, %f, %f, %f]\n", one, two, three, four, five);

	double six = falseAccept(dev[0]);
	double seven = falseAccept(dev[1]);
	double eight = falseAccept(dev[2]);
	double nine = falseAccept(dev[3]);
	double ten = falseAccept(dev[4]);
	printf("False Accept: [%f, %f, %f, %f, %f]\n", six, seven, eight, nine, ten);

	double far = (one + two + three + four + five)/5;
	double frr = (six + seven + eight + nine + ten)/5;
	if(far == frr)
		printf("User access granted\n");
	else
		printf("Access failed!\n");

	return 0;
}

//Calculates deviation from all sets and equal error rate
int authenticate(userData data[][size], int user)
{
	int x;
	double dev[userSize];
	readData(chooseUser(user), data);
	printf("Deviation:\n");
	for(x = 0; x < userSize; x++)
	{
		dev[x] = deviation(size, data[0], data[x]);
		printf("%f\n", dev[x]);
	}
	return calculateEER(dev);
}

//Creates userData struct and then uses it to authenticate each user
int main()
{
	userData setData[6][size];
	int user;
	for(user = 1; user < userSize + 1; user++) {
		printf("------------------------------------\n");
		printf("User %d\n", user);
		int authen = authenticate(setData, user);
	}
	return 0;
}
