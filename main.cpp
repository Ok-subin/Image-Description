#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdio.h>
#include "imageCut.h"
#include "colorInform.h"
#include "locationInform.h"
#include <fstream>
#include "sentence.h"

using namespace std;

int main()
{
	string yoloFileName = "After executing Yolo, the address of the file where bounding box location is stored.";
	string imgFileName = "Original Image Address";
	string resultFileName = "Address of the file to store final information.";
	string saveFileName = "Address to save cropped object image.";
	string sentenceFile = "Address to save final image description sentence.";


	int imageCount;
	string resultArray[3][100];
	MeanShift MSProc(8, 22);

	imageCount = cutImage(yoloFileName, imgFileName, saveFileName, resultArray);

	for (int i = 0; i < imageCount; i++)
	{
		string bbFile =  "Address for loading object images.";
		string saveSegmentImage = "Address to Save the segmentated image.";
		string saveColorImage = "Address to Save the the color's image that occupies the most area.";

		MSProc.mainExe(bbFile, saveSegmentImage, saveColorImage, resultArray, i);
	}

	location(yoloFileName, imgFileName, resultArray);
	ofstream file(resultFileName);
	string resultName, resultColor, resultLocation;
		
	for (int i = 0; i < imageCount; i++)
	{
		resultName = "object : " + resultArray[0][i] + "\n";
		resultColor = "color : " + resultArray[1][i] + "\n";
		resultLocation = "location : " + resultArray[2][i] + "\n";

		file << resultName;
		file << resultColor;
		file << resultLocation;
		file << "\n";
	}

	makeSentence(sentenceFile, resultArray, imageCount);

	return 0;
}