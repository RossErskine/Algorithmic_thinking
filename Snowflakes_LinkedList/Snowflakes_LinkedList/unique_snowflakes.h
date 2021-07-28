#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "printVec.h"

using namespace std;
// ==== Globals ==== //
int SIZE = 10000; // size of snowflake array

// ======================= test cases ================ //
void createTestCase(string filename)
{
	vector<int> snowflake;
	vector<vector<int>> testCase_snowflakes;

	for (int i = 0; i != SIZE; i++) {

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
class Snowflake_node
{
public:
	vector<int> snowflake;
	Snowflake_node* next;
};
void push(Snowflake_node** head_ref, vector<int> new_snowflake)
{
	Snowflake_node* new_node = new Snowflake_node();
	new_node->snowflake = new_snowflake;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

int snowIndex(vector<int> snowflake) 
{
	 return (snowflake[0]+ snowflake[1]+ snowflake[2]+ snowflake[3]+ snowflake[4]+ snowflake[5]) % SIZE;
}

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
int COUNT = 0;
bool are_identical(vector<int> snow1, vector<int> snow2)
{
	COUNT++;
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

void identify_identical(vector<Snowflake_node*> snowflakes)
{
	
	Snowflake_node *node1, *node2;
	for (int i = 0; i != snowflakes.size(); i++) {
		node1 = snowflakes[i];
		if (node1 != NULL) {
			while (node1 != NULL) {
				
				node2 = node1->next;
				while (node2 != NULL) {
					if (are_identical(node1->snowflake, node2->snowflake)) {
						cout << "Twin snowflakes found.\n";
						cout << COUNT;
						return;
					}
					node2 = node2->next;
				}
				node1 = node1->next;
			}
		}
	}
	cout << "No two snowflakes are alike.\n";
	cout << COUNT;
}

vector<Snowflake_node*> createSnowflakeLinkedList(vector<vector<int>> snowflakes)
{
	vector<Snowflake_node*> snowflakes_index;
	snowflakes_index.resize(SIZE); // allocate memory on the heap
	for (int i = 0; i != snowflakes.size(); i++) {
		vector<int> snowflake;
		for (int j = 0; j != 6; j++) {
			snowflake.push_back(snowflakes[i][j]);
		}
		int index = snowIndex(snowflake);
		push(&snowflakes_index[index], snowflake);
	}
	return snowflakes_index;
}

void runUniqueSnowflakes()
{
	createTestCase("snowflakes.txt");
	vector<vector<int>> snowflakes;
	snowflakes = getTest_Case("snowflakes.txt");
	vector<Snowflake_node*> snowflakes_index = createSnowflakeLinkedList(snowflakes);
	cout << "Linked list created" << endl;
	
	identify_identical(snowflakes_index);
	
}


