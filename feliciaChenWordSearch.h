//
// Created by felic on 8/3/2022.
//

#ifndef FELICIACHENWORDSEARCH_FELICIACHENWORDSEARCH_H
#define FELICIACHENWORDSEARCH_FELICIACHENWORDSEARCH_H
#include <iostream>
#include <fstream>
#include <string>

/* pre: program is running
 * post: main menu is open */
void openMainMenu();

/* pre: maxLength is determined, something is in the array (if using to create, numOfWords determined)
 * post: array is output to the console */
void display(char arr[][45], int maxLength, std::string words[100], int numOfWords);

/* pre: maxLength is initialized
 * post: every variable in array is filled with blank spaces */
void clearPuzzle(char arr[][45], int maxLength);

/* pre: array and max length are initialized
 * post: blank spaces in the array is filled with random letters*/
void fillPuzzle(char arr[][45], int maxLength);


/* pre: the word is gotten from the user
 * post: the word is randomly printed backwards or forwards vertically */
void vertical(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty);

/* pre: the word is gotten from the user
 * post: the word is randomly printed backwards or forwards horizontally */
void horizontal(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty);

/* pre: the word is gotten from the user
 * post: the word is randomly printed backwards or forwards diagonally */
void diagonal(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty);

/* pre: the word is gotten from the user
 * post: all spaces in the random spot are empty*/
void fillRandomPlacement(char arr[][45], std::string words[100], int maxLength, int numOfWords);

/* pre: the word search is outputted to the console
 * post: file is created and word search is inside the file*/
void writeToFile(char arr[][45], int maxLength, std::string words[100], int numOfWords);

/* post: the puzzle is created and output to console*/
void createPuzzle(char arr[][45], std::string words[100]);

/* pre: the filename is provided by user
 * post: the file is output to the console*/
void openPuzzle(std::string filename);

/* pre: a string is provided
 * post: the string is returned backwards */
std::string makeBackwards(std::string x);

/* pre: the filename of the word search is provided
 * post: the max length is initialized*/
int getMaxLength(std::string filename);

/* pre: the filename of the word search is provided
 * post: the max length is initialized*/
void getArray(char array[][45], std::string filename, int& maxLength, std::string solutions[45], int& solutionAmt);

/* pre: the word that we are looking for is determined
 * post: false if word is not found, true if it is*/
bool findRows(char array[][45], std::string& word, int&r, int&c, int maxLength);
bool findColumns(char array[][45], std::string& word, int&r, int&c, int maxLength);
bool findRightDiag(char array[][45], std::string& word, int&r, int&c, int maxLength);
bool findLeftDiag(char array[][45], std::string& word, int&r, int&c, int maxLength);

/*pre: int r and c are the index of the word
 * post: word is in empty array */
void fillArrayRow(char final[][45], std::string word, int r, int c);
void fillArrayCol(char final[][45], std::string word, int r, int c);
void fillArrayRightDiag(char final[][45], std::string word, int r, int c);
void fillArrayLeftDiag(char final[][45], std::string word, int r, int c);

/* pre: puzzle is unsolved
 * post: puzzle is solved and output to the screen*/
void solvePuzzle();



#endif //FELICIACHENWORDSEARCH_FELICIACHENWORDSEARCH_H
