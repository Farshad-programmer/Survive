#pragma once
#include <string>
#include <iomanip>


inline bool IsInputDigit(const std::string str)
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
    const int boardWidth = 100;
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
                else if (i == boardHeight / 2 && j == boardWidth / 2) {
                    std::cout << std::setw(6) << "SURVIVE - Build v1.0.0";
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
