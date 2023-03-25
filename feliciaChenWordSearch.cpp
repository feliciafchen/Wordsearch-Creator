//
// Created by felic on 8/3/2022.
//
#include "feliciaChenWordSearch.h"
void openMainMenu()
{
    const int size = 100;
    std::string words[size];
    char puzzle[45][45];
    int choice;
    std::string filename;

    do
    {
        std::cout << "Choose an option\n"
                     "(1) Create a new puzzle\n"
                     "(2) Open an existing puzzle\n"
                     "(3) Solve an existing puzzle\n"
                     "(4) Exit\n";

        std::cin >> choice;
        if(choice == 1)
        {
            createPuzzle(puzzle, words);
        }
        if(choice == 2)
        {
            std::cout << "Enter file name: \n";
            std::cin >> filename;
            openPuzzle(filename);
        }
        if(choice == 3)
        {
            solvePuzzle();
        }
    }
    while (choice != 4);

    std::cout << "Goodbye!\n";
}
void display(char arr[][45], int maxLength, std::string words[100], int numOfWords)
{
    int num = 0;
    for(int i = 0; i < maxLength; i++)
    {
        for(int j = 0; j < maxLength; j++)
        {
            std::cout << arr[i][j] << " ";
            num++;

            if(num > maxLength - 1)
            {
                std::cout << std::endl;
                num = 0;
            }
        }
    }
    std::cout << std::endl;

    for(int i = 0; i < numOfWords; i++)
    {
        std::cout << words[i] << std::endl;
    }

    std::cout << std::endl;

}

void clearPuzzle(char arr[][45], int maxLength)
{
    for(int i = 0; i < maxLength; i++)
    {
        for(int j = 0; j < maxLength; j++)
        {
            arr[i][j] = ' ';
        }
    }
}

void fillPuzzle(char arr[][45], int maxLength)
{
    for(int i = 0; i < maxLength; i++)
    {
        for(int j = 0; j < maxLength; j++)
        {
            if(arr[i][j] == ' ')
            {
                arr[i][j] = rand() % 26 + 'a';
            }
        }
    }
}
void vertical(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty)
{
    int backwards = rand() % 2;
    empty = false;

    while(!empty)
    {
        do
        {
            //find a rand row in the arr
            r = rand() % maxLength;
            //find a rand col in the arr
            c = rand() % maxLength;
        }
        while(word.size()+r > maxLength);


        for(int j = r; j < r+word.size(); j++)
        {
            if(arr[j][c] == ' ')
            {
                empty = true;
            }
            else
            {
                empty = false;
                break;
            }
        }
    }


    if(backwards == 0)
    {
        if(empty)
        {
            for(int y = r; y < r+word.size(); y++)
            {
                arr[y][c] = word[x];
                x++;
            }
        }
    }
    else if(backwards == 1)
    {
        x = word.size()-1;
        if(empty)
        {
            for(int y = r; y < r+word.size(); y++)
            {
                if(arr[y][c] == ' ')
                {
                    arr[y][c] = word[x];
                    x--;
                }
            }
        }
    }

}

void horizontal(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty)
{
    int backwards = rand() % 2;
    empty = false;

    while(!empty)
    {
        do
        {
            //find a rand row in the arr
            r = rand() % maxLength;
            //find a rand col in the arr
            c = rand() % maxLength;
        }
        while(word.size()+c > maxLength);

        empty = false;
        for(int j = c; j < c+word.size(); j++)
        {
            if(arr[r][j] == ' ')
            {
                empty = true;
            }
            else
            {
                empty = false;
                break;
            }
        }
    }


    if(backwards == 0)
    {
        for (int y = c; y < c + word.size(); y++) {
            if (arr[r][y] == ' ') {
                arr[r][y] = word[x];
                x++;
            }
        }
    }
    else if(backwards == 1)
    {
        x = word.size()-1;
        for(int y = c; y < c+word.size(); y++)
        {
            arr[r][y] = word[x];
            x--;
        }
    }

}
void diagonal(char arr[][45], std::string word, int& i, int& r, int& c, int& x, int maxLength, bool& empty)
{
    int d, p;
    int backwards = rand() % 2;
    empty = false;

    while(!empty)
    {
        do
        {
            //find a rand row in the arr
            r = rand() % maxLength;
            //find a rand col in the arr
            c = rand() % maxLength;
        }
        while((word.size()+c > maxLength) || (word.size()+r > maxLength));

        d = r;

        empty = false;
        for(int j = c; j < c+word.size(); j++)
        {
            if(arr[j][d] == ' ')
            {
                empty = true;
                d++;
            }
            else
            {
                empty = false;
                break;
            }
        }
    }

    p = r;
    if(empty)
    {
        if(backwards == 0)
        {
            for(int y = c; y < c+word.size(); y++)
            {
                arr[y][p] = word[x];
                p++;
                x++;
            }
        }
        else if(backwards == 1)
        {
            x = word.size()-1;
            for(int y = c; y < c+word.size(); y++)
            {
                arr[y][p] = word[x];
                p++;
                x--;
            }
        }
    }
}
void fillRandomPlacement(char arr[][45], std::string words[100], int maxLength, int numOfWords)
{
    for(int i = 0; i < numOfWords; i++)
    {
        std::string word = words[i];
        bool empty = false;
        int x = 0, r, c;
        int counter = 0;
        int place;

        while(!empty)
        {
            place = rand() % 3;
            if(place == 0)
            {
                horizontal(arr, word, i, r, c, x, maxLength, empty);
            }
            else if(place == 1)
            {
                vertical(arr, word, i, r, c, x, maxLength, empty);
            }
            else if(place == 2)
            {
                diagonal(arr, word, i, r, c, x, maxLength, empty);
            }
            counter ++;
            if (counter > 300)
            {
                std::cout << "No space!\n";
                openMainMenu();
            }
        }
    }
}
void writeToFile(char arr[][45], int maxLength, std::string words[100], int numOfWords)
{
    std::ofstream fout;
    std::ifstream fin;
    std::string filename;
    std::cout << "Enter file name: \n";
    std::cin >> filename;

    fout.open(filename);
    if(fin.fail())
    {
        std::cout << "Could not open file.\n";
        exit(1);
    }

    int num = 0;
    for(int i = 0; i < maxLength; i++)
    {
        for(int j = 0; j < maxLength; j++)
        {
            fout << arr[i][j] << " ";
            num++;

            if(num > maxLength - 1)
            {
                fout << std::endl;
                num = 0;
            }
        }
    }
    fout << std::endl << std::endl;

    for(int i = 0; i < numOfWords; i++)
    {
        fout << words[i] << std::endl;
    }

    fout << std::endl;

    std::cout << "File saved!\n";

    fout.close();
}

void createPuzzle(char arr[][45], std::string words[100])
{
    std::ofstream fout;
    srand(time(0));
    int numOfWords, maxLength = 0;
    char choice;

    do
    {
        std::cout << "Enter number of words in puzzle (1-10): \n";
        std::cin >> numOfWords;
    }
    while(numOfWords > 10 || numOfWords < 1);

    for(int i = 0; i < numOfWords; i++)
    {
        std::cout << "Enter word " << i+1 << ": \n";
        std::cin >> words[i];
        if(words[i].size() > maxLength)
        {
            maxLength = words[i].size();
        }
    }

    if(maxLength < 10)
    {
        maxLength = 10;
    }

    clearPuzzle(arr, maxLength);
    fillRandomPlacement(arr, words, maxLength, numOfWords);
    fillPuzzle(arr, maxLength);
    display(arr, maxLength, words, numOfWords);

    std::cout << "Save puzzle? y/n\n";
    std::cin >> choice;

    if(tolower(choice) == 'y')
    {
        writeToFile(arr, maxLength, words, numOfWords);
    }
}
void openPuzzle(std::string filename)
{
    std::ifstream fin;
    std::string x;

    fin.open(filename);
    if(fin.fail())
    {
        std::cout << "Smt went wrong :(\n";
        exit(3);
    }

    while (getline(fin,x))
    {
        std::cout << x << std::endl;
    }
}
std::string makeBackwards(std::string x)
{
    std::string backwards = x;
    int length = x.size()-1;

    for(int i = 0; i <= length; i++)
    {
        backwards[i] = x[length-i];
    }

    return backwards;
}
int getMaxLength(std::string filename)
{
    int maxLength;
    std::ifstream fin;
    std::string nothing;

    fin.open(filename);
    if (fin.fail())
    {
        std::cout << "Something went wrong\n";
        exit(3);
    }

    getline(fin, nothing);
    maxLength = nothing.size() / 2;

    fin.close();

    return maxLength;
}

void getArray(char array[][45], std::string filename, int& maxLength, std::string solutions[45], int& solutionAmt)
{
    std::ifstream fin;
    std::string nothing;
    std::string rows;
    int c = 0, f = 0;

    maxLength = getMaxLength(filename);

    fin.open(filename);
    if (fin.fail())
    {
        std::cout << "Something went wrong\n";
        exit(3);
    }

    for (int i = 0; i < maxLength; i++) {
        getline(fin, nothing);
        rows += nothing;
    }

    for (int a = 0; a < maxLength; a++) {
        for (int b = 0; b < maxLength; b++) {
            if (rows[c] != ' ') {
                array[a][b] = rows[c];
                c++;
            } else {
                c++;
                b--;
            }
        }
    }

    while(getline(fin, nothing))
    {
        if(nothing != "")
        {
            solutions[f] = nothing;
            solutionAmt++;
            f++;
        }
        else;
    }
}

bool findRows(char array[][45], std::string& word, int&r, int&c, int maxLength)
{
    int index;
    std::string section, wordBack;
    wordBack = makeBackwards(word);

    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = 0; y < maxLength; y++)
        {
            section += array[i][y];
        }
        index = section.find(word);
        if(index != -1)
        {
            c = index;
            r = i;
            return true;
        }
        index = section.find(wordBack);
        if(index != -1)
        {
            word = wordBack;
            c = index;
            r = i;
            return true;
        }
    }
    return false;
}
bool findColumns(char array[][45], std::string& word, int&r, int&c, int maxLength)
{
    int index;
    std::string section, wordBack;
    wordBack = makeBackwards(word);

    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = 0; y < maxLength; y++)
        {
            section += array[y][i];
        }
        index = section.find(word);
        if(index != -1)
        {
            c = i;
            r = index;
            return true;
        }
        index = section.find(wordBack);
        if(index != -1)
        {
            word = wordBack;
            c = i;
            r = index;
            return true;
        }
    }

    return false;
}
bool findRightDiag(char array[][45], std::string& word, int&r, int&c, int maxLength)
{
    int index;
    std::string section, wordBack;
    wordBack = makeBackwards(word);

    int x = 0, count = 0;

    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = count; y < maxLength; y++)
        {
            section += array[y][x++];
            index = section.find(word);
            if(index != -1)
            {
                c = index;
                r = i;
                return true;
            }
            index = section.find(wordBack);
            if(index != -1)
            {
                c = index;
                r = i;
                word = wordBack;
                return true;
            }
        }
        count ++;
        x = 0;
    }

    x = 0, count = 0;
    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = count; y < maxLength; y++)
        {
            section += array[x++][y];
            index = section.find(word);
            if(index != -1)
            {
                c = i + 1;
                r = index - 2;
                return true;
            }
            index = section.find(wordBack);
            if(index != -1)
            {
                c = i;
                r = index;
                word = wordBack;
                return true;
            }
        }
        count ++;
        x = 0;
    }

    return false;
}
bool findLeftDiag(char array[][45], std::string& word, int&r, int&c, int maxLength)
{
    int index;
    std::string section, wordBack;
    wordBack = makeBackwards(word);

    int x = 9, count = 0;
    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = count; y < maxLength; y++)
        {
            section += array[x--][y];
            index = section.find(word);
            if(index != -1)
            {
                c = index;
                r = i;
                return true;
            }
            index = section.find(wordBack);
            if(index != -1)
            {
                c = index;
                r = i;
                word = wordBack;
                return true;
            }
        }
        count ++;
        x = 9;
    }

    x = 9;
    for(int i = 0; i < maxLength; i++)
    {
        section = "";
        for(int y = 0; y < maxLength - i; y++)
        {
            section += array[x][y];
            index = section.find(word);
            if(index != -1)
            {
                c = index;
                r = i;
                return true;
            }
            index = section.find(wordBack);
            if(index != -1)
            {
                c = index;
                r = i;
                word = wordBack;
                return true;
            }
            x--;
        }
        x = 9 - (i+1);
    }

    return false;
}

void fillArrayRow(char final[][45], std::string word, int r, int c)
{
    int length;
    length = word.size();
    int x = 0;
    for(int y = c; y < length+c; y++)
    {
        final[r][y] = word[x];
        x++;
    }
}
void fillArrayCol(char final[][45], std::string word, int r, int c)
{
    int length;
    length = word.size();
    int x = 0;
    for(int y = r; y < length+r; y++)
    {
        final[y][c] = word[x];
        x++;
    }
}
void fillArrayRightDiag(char final[][45], std::string word, int r, int c)
{
    int length;
    length = word.size();
    int x = 0;
    int m = r - 1;
    int e = c+1;

    for(int y = r; y < length+r; y++)
    {
        final[y][c] = word[x];
        c++;
        x++;
    }
}
void fillArrayLeftDiag(char final[][45], std::string word, int r, int c)
{
    int length;
    length = word.size();
    int x = 0;
    for(int y = r; y < length+r; y++)
    {
        final[y][c] = word[x];
        c--;
        x++;
    }
}

void solvePuzzle()
{
    const int size = 45;
    std::string filename;
    char array[size][size];
    char final[size][size];
    std::string solutions[size];
    int solutionAmt = 0;
    int maxLength = 100;
    int r, c;

    std::cout << "Enter file name: \n";
    std::cin >> filename;

    getArray(array, filename, maxLength, solutions, solutionAmt);
    clearPuzzle(final, maxLength);

    for(int i = 0; i < solutionAmt; i++)
    {
        if(findRows(array, solutions[i], r, c, maxLength))
        {
            fillArrayRow(final, solutions[i], r, c);
        }
        else if(findColumns(array, solutions[i], r, c, maxLength))
        {
            fillArrayCol(final, solutions[i], r, c);
        }
        else if(findRightDiag(array, solutions[i], r, c, maxLength))
        {
            fillArrayRightDiag(final, solutions[i], r, c);
        }
        else if(findLeftDiag(array, solutions[i], r, c, maxLength))
        {
            fillArrayLeftDiag(final, solutions[i], r, c);
        }
        else
        {
            std::cout << "Could not find word\n";
        }
    }

    display(final, maxLength, NULL, NULL);
}
