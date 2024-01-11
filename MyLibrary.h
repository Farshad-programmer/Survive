#pragma once
#include <string>
#include <iomanip>


inline bool IsInputDigit(const std::string str) // it is a functions that checks only the first value of string 
{
	for (char c : str)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}
	return true;
}

inline bool IsNonNumeric(const std::string str)// it is a functions that checks all string values 
{
    bool bCorrect = true;
    for (char c : str)
    {
        if (isdigit(c))
        {
            bCorrect = false;
        }
    }
    return bCorrect;
}


inline void CleanConsole(std::string message = "none")
{
	system("cls");
	if (message != "none")
	{
		std::cout << message << std::endl;
	}
}

inline void GameTitle()
{
    const int boardWidth = 80;
    const int boardHeight = 5;

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            if (i == 0 || i == boardHeight - 1) {
                std::cout << "-";
            }
            else {
                if (j == 0 || j == boardWidth - 1) {
                    std::cout << "|";
                }
                else if (i == boardHeight / 4 && j == boardWidth / 2.5) {
                    std::cout << std::setw(6) << "SURVIVE";
                    j += 6;
                }
                else if (i == boardHeight / 2.5 && j == boardWidth / 2.5)
                {
                    std::cout << std::setw(6) << "Ver 1.0";
                    j += 6;
                }
                else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}