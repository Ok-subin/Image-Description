#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "sentence.h"
#include "translate.h"
#include <algorithm>

using namespace std;

void makeSentence(string fileName, string resultArray[3][100], int imageCount)
{
	ofstream file(fileName);
	string result;
	string object, color, location;

	if (imageCount == 1)
	{
		result = "There is a ";

		object = resultArray[0][imageCount];
		color = resultArray[1][imageCount];
		location = resultArray[2][imageCount];

		result += (color + " " + object + " in the " + location + " in the image.");
	}

	else
	{
		result = "There are ";
		for (int i = 0; i < imageCount; i++)
		{
			if (i == imageCount - 1)
			{
				object = resultArray[0][i];
				color = resultArray[1][i];
				location = resultArray[2][i];

				result += ("a " + color + " " + object + " in the " + location + " in the image.");
			}

			else
			{
				object = resultArray[0][i];
				color = resultArray[1][i];
				location = resultArray[2][i];

				result += ("a " + color + " " + object + " in the " + location + " and ");
			}
		}

	}
	file << result;
	file << "\n";

	file << translate(result.c_str());
	file << "\n";
}