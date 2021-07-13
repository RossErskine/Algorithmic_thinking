#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "printVec.h"

using namespace std;

// ======================= test cases ================ //
void createTestCase(string filename)
{
	vector<int> snowflake;
	vector<vector<int>> testCase_snowflakes;

	for (int i = 0; i != 1000; i++) {

		for (int j = 0; j != 6; j++) {
			int randomNum = (rand() % 100);
			snowflake.push_back(randomNum);
		}
		testCase_snowflakes.push_back(snowflake);
		snowflake.clear();
	}

	ofstream ost{ filename };
	if (!ost)throw "cannot open output file", filename;

	for (int i = 0; i != testCase_snowflakes.size(); i++) {
		for (int j = 0; j != testCase_snowflakes[i].size(); j++) {
			ost << testCase_snowflakes[i][j] << '\t';
		}
		ost << '\n';
	}
	ost.close();
}

vector<vector<int>> getTest_Case(string filename) {
	vector<vector<int>> testCase_snowflakes;
	vector<int> snowflake;
	vector<int> temp;
	ifstream ist{ filename };
	if (!ist)throw "cannot open input file", filename;
	
	for (int i; ist >> i; ) {
		temp.push_back(i);
	}
	int count = 0;
	for (int i = 0; i != temp.size(); i++) {
		snowflake.push_back(temp[i]);
		count++;
		if (count == 6) {
			testCase_snowflakes.push_back(snowflake);
			snowflake.clear();
			count = 0;
		}
		
	}
	return testCase_snowflakes;
}
/*
void createResultFile(string filename, vector<int> results) {
	ofstream ost{ filename };
	if (!ost)throw "cannot open output file", filename;

	for (int i : results) {
		ost << i << '\t';
	}
	ost.close();
}*/

// ========= solution ============== //

bool identical_left(vector<int> snow1, vector<int> snow2, int start)
{
	for (int i = 0; i != snow1.size(); i++) {
		if (snow1[i] != snow2[start ])return false;
		start--;
		if (start < 0) start = 5; 
	}
	return true;
}

bool identical_right(vector<int> snow1, vector<int> snow2, int start)
{
	for (int i = 0; i != snow1.size(); i++) {
		if (snow1[i] != snow2[start])return false;	
		start++;
		if (start > 5)start -= 6;
	}
	return true;
}

bool are_identical(vector<int> snow1, vector<int> snow2)
{
	for (int i = 0; i < snow1.size(); i++) {
		if (identical_right(snow1, snow2, i)) {
			return true;
		}
		if (identical_left(snow1, snow2, i)) {
			return true;
		}
	}
	return false;
}

void identify_identical(vector<vector<int>> values)
{
	for (int i = 0; i != values.size()-1; i++) {
		for (int j = i + 1; j != values.size()-1; j++) {
			if (are_identical(values[i],values[j])) {
				cout << "Twin snowflakes found.\n"; 
				return;
			}
		}
	}
	cout << "No two snowflakes are alike.\n";
}

void runUniqueSnowflakes()
{
	createTestCase("snowflakes.txt");
	vector<vector<int>> snowflakes;
	snowflakes = getTest_Case("snowflakes.txt");
	//printVector(snowflakes);
	//cout << snowflakes[0].size();

	vector<vector<int>> a = { { 1,2,3,4,5,6 },{7,8,9,10,1,4}, {7,1,2,3,4,5}, {9,8,9,80,1,2} };
	identify_identical(snowflakes);
	
}


