#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <opencv2/opencv.hpp>
#include "imageCut.h"
#include "getKorean.h"

#pragma warning(disable:4996)

using namespace std;
using namespace cv;

int cutImage(string yoloFileName, string imgFileName, string saveFileName, string resultArray[3][100])
{
	ifstream file(yoloFileName);
	string lines;
	int  count = 1, i, totalImage = 1;
	int index[4];
	string name[2];
	char lineChar[100];

	while (getline(file, lines))
	{
		if (count % 2 == 1)
		{
			strcpy(lineChar, lines.c_str());
			char* line = strtok(lineChar, ": ");
			i = 0;
			while (line != NULL)
			{
				name[i] = line;
				i++;

				line = strtok(NULL, " ");
			}
			count++;
			resultArray[0][totalImage-1] = name[0];
		}

		else
		{	
			Mat originalImg = imread(imgFileName);
			string filename = saveFileName;

			strcpy(lineChar, lines.c_str());
			char* line = strtok(lineChar, ": ");
			i = 0;
			while (line != NULL)
			{
				index[i] = atoi(line);
				i++;

				line = strtok(NULL, " ");
			}

			index[2] = index[2] - index[0];
			index[3] = index[3] - index[1];

			filename += to_string(totalImage);
			filename += ".jpg";

			Rect rect(index[0], index[1], index[2], index[3]); //x, y, w, h
			Mat newImage = originalImg(rect);

			imwrite(filename, newImage);
			count++;

			for (int j = 0; j < 4; j++)
			{
				index[j] = 0;
			}

			for (int j = 0; j < 2; j++)
			{
				name[j] = "";
			}
			totalImage++;
		}
	}
	return totalImage -1;

}