// CPPCommentRemover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// STL support:
#include <string> 
#include <iostream> 
#include <sstream> 
#include <fstream> 

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect parameters count. Usage:" << '\n';
		cout << "CPPCommentRemover.exe InputFile.cpp OutputFile.cpp" << '\n';
		return 1;
	}

	string sInFileName(argv[1]);
	ifstream inFile(sInFileName, ios::in);

	stringstream ssIn;
	if (inFile.is_open())
	{
		ssIn << inFile.rdbuf();
		inFile.close();
	}

	string sInputFile = ssIn.str();
	string sOutString;

	bool bIsOldStyleComment = false;
	bool bIsNewStyleComment = false;
	bool bAddPrevious = false;
	char chrPrevious = '\0';

	for (char chr : sInputFile)
	{
		if (chr == '/')
		{
			if (chrPrevious == '/')
				bIsNewStyleComment = true;
			else if (chrPrevious == '*')
				bIsOldStyleComment = false;
			else if (!bIsOldStyleComment && !bIsNewStyleComment)
				bAddPrevious = true;
	
			chrPrevious = chr;
			continue;
		}
		else
		{
			if (chr == '*' && chrPrevious == '/')
				bIsOldStyleComment = true;

			if (bAddPrevious)
			{
				bAddPrevious = false;
				if (!bIsOldStyleComment && !bIsNewStyleComment)
					sOutString.push_back('/');
			}
		}

		if ((chr == 0x0d) || (chr == 0x0a)) // CR and LF special symbols
			bIsNewStyleComment = false;

		if (!bIsOldStyleComment && !bIsNewStyleComment)
			sOutString.push_back(chr);

		chrPrevious = chr;
	}

	string sOutFileName(argv[2]);
	ofstream fileOut(sOutFileName, ios::out);
	if (fileOut.is_open())
	{
		fileOut << sOutString;
		fileOut.close();
	}

    return 0;
}

