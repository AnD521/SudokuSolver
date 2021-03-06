/*
*	ANKUR DUBEY
*	PROJECT INVOLVING FILE HANDLING:SUDOKU SOLVER
*/

/*
*	SUDOKUSOLVER.CPP
*	a)Code follows the ISO C++ 11 standard
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SudokuMatrix.h"
//#include "stdafx.h"

class SudokuCollection {
	/*
	*	Aggregation of SudokuMatrix(s)
	*
	*	Private Data Members:
	*	_Sudoku[]:					Collection of Sudoku Matrix(s) to solve Sudoku
	*	_problemNum:				Total number of problems
	*
	*	Public Methods:
	*	displaySudokuSolution():	Displays solution on screen
	*/

private:
	SudokuMatrix _Sudoku[100];
	int _problemNum;

public:
	SudokuCollection(char pathInputFile_bin[], char pathOutputFile_bin[], char pathOutputFile_text[]);
	void displaySudokuSolution(int serialNum);
};
SudokuCollection::SudokuCollection(char pathInputFile_bin[], char pathOutputFile_bin[], char pathOutputFile_text[]) {
	/*
	*	Populate _Sudoku[] with all problems stored in input file (max 100)
	*	Store total no of problems in _problemNum
	*/
	std::fstream inputFile(pathInputFile_bin, std::ios::in | std::ios::binary);
	_problemNum = 0;
	rawMatrix temp;
	if (inputFile.is_open()) {
		while (!inputFile.eof()) {
			inputFile.read((char*)&temp, sizeof(rawMatrix));
			_Sudoku[_problemNum++].initialize(temp);
		}
	}
	inputFile.close();

	//Store all SudokuMatrix objects in a new binary file
	std::fstream outputFile(pathOutputFile_bin, std::ios::out | std::ios::binary);
	if (outputFile.is_open()) {
		for (int i = 0; i < _problemNum; ++i) {
			outputFile.write((char*)&_Sudoku[i], sizeof(SudokuMatrix));
		}
	}
	outputFile.close();

	//Store all Sudoku solutions in a new text file
	for (int i = 0; i < _problemNum; ++i) {
		_Sudoku[i].exportFile(pathOutputFile_text);
	}
}
void SudokuCollection::displaySudokuSolution(int serialNum) {
	_Sudoku[serialNum - 1].displaySolution();
}


void intro() {
	system("clear");
	std::cout << "\t\t\t\t\t\t\tSudoku Solver" << std::endl << std::endl;
}

int main() {
	intro();
	std::cout << "How many Sudoku(s) are to be solved(max: 100) ? ";
	int count;
	std::cin >> count;
	rawMatrix temp[100];
	for (int n = 0; n < count; ++n) {
		temp[n].serialNum = n + 1;
		intro();
		int t[9][9];
		std::cout << "Enter Sudoku Elements in Orderly Fashion with blanks represented by 0" << std::endl;
		std::cout << "Enter Elements for Sudoku #" << n + 1 << ":" << std::endl;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				std::cin >> t[i][j];
			}
		}
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				temp[n].matrix[i][j] = t[i][j];
			}
		}
	}
	char outputBin[] = "raw.bin";
	std::fstream outputFile(outputBin, std::ios::out | std::ios::binary);
	for (int i = 0; i < count; ++i) {
		if (outputFile.is_open()) {
			outputFile.write((char*)&temp[i], sizeof(rawMatrix));
		}
	}
	outputFile.close();
	intro();
	std::cout << "Raw Matrix Data has been stored in raw.bin";
	std::cout << std::endl << "All solutions have been stored in output.txt";
	char outputTextPath[] = "output.txt";
	char outputBin2[] = "solvedSudoku.bin";
	SudokuCollection Final(outputBin, outputBin2, outputTextPath);
	int choice = 1;
	std::cout << std::endl << "Enter sudoku number to show solution: (0 to exit)";
	std::cin >> choice;
	while (choice != 0) {
		Final.displaySudokuSolution(choice);
		std::cout << std::endl << "Enter sudoku number to show solution: (0 to exit)";
		std::cin >> choice;
		intro();
	}
	return 0;
}