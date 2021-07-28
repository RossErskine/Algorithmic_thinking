#include <vector>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
// = declarations = //
void createTestCase(string, int);
vector<int> getTestCase(string);
void createResultFile(string, vector<int>);

int shortest_line(vector<int> lines)
{
	int shortestLine = 100, shortestLineIndex = 0;
	for (int i =0; i != lines.size()-1; i++) {
		if (lines[i] < shortestLine) {
			shortestLine = lines[i];
			shortestLineIndex = i;
		}
	}
	return shortestLineIndex;
}

vector<int> solve(vector<int>& lines, int& people)
{
	vector<int> result;
	for (int i = 0; i != people; i++) {
		int shortestLineIndex = shortest_line(lines);
		cout << lines[shortestLineIndex] << '\n';
		result.push_back(lines[shortestLineIndex]);
		lines[shortestLineIndex] += 1;
	}
	return result;
}

void runFoodLines()
{
	
	const string food_lines_testCase = "food_lines_testCase.txt";
	createTestCase(food_lines_testCase, 10);
	vector<int> test_lines2 = getTestCase(food_lines_testCase);
	int test_people2 = 100;
	vector<int> results = solve(test_lines2, test_people2);
	createResultFile("results1.txt", results);
}

// ======================= test cases ================ //
void createTestCase(string filename, int n)
{
	vector<int> testCase_lines;
	for (int i = 0; i != n; i++) {
		int randomNum = (rand() % 100);
		testCase_lines.push_back(randomNum);
	}
	ofstream ost{ filename };
	if (!ost)throw "cannot open output file", filename;

	for (int i : testCase_lines) {
		ost << i << '\t';
	}
	ost.close();
}

vector<int> getTestCase(string filename) {
	vector<int> testCase;
	ifstream ist{ filename };
	if (!ist)throw "cannot open input file", filename;
	for (int i; ist >> i;)
	{
		testCase.push_back(i);
	}
	return testCase;
}

void createResultFile(string filename, vector<int> results) {
	ofstream ost{ filename };
	if (!ost)throw "cannot open output file", filename;

	for (int i : results) {
		ost << i << '\t';
	}
	ost.close();
}
