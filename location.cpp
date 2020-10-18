#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <algorithm>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#pragma warning(disable:4996)

using namespace std;
using namespace cv;


float IOU(int roi[], float compare[])
{
	float x1, y1, x2, y2;
	float width, height, area_overlap, area_a, area_b, area_combined;
	float interArea, boxAArea, boxBArea;
	float intersection_x_length, intersection_y_length;
	float iou, epsilon = 1e-5;

	x1 = max(float(roi[0]), compare[0]);
	y1 = max(float(roi[1]), compare[1]);
	x2 = min(float(roi[2]), compare[2]);
	y2 = min(float(roi[3]), compare[3]);

	interArea = max(float(0), x2 - x1 + 1) * max(float(0), y2 - y1 + 1);

	boxAArea = (roi[2] - roi[0] + 1) * (roi[3] - roi[1] + 1);
	boxBArea = (compare[2] - compare[0] + 1) * (compare[3] - compare[1] + 1);

	iou = interArea / float(boxAArea + boxBArea - interArea);

	cout << "inter :  " << interArea <<  "  ,  A :  " << boxAArea << "  ,   B : " << boxBArea << "  ,  base : " << float(boxAArea + boxBArea - interArea) << endl;

	width = (x2 - x1);
	height = (y2 - y1);

	if (width < 0 || height < 0)
		return 0.0;

	/*
	area_overlap = width * height;
	area_a = (roi[2] - roi[0])*(roi[3] - roi[1]);
	area_b = (compare[2] - compare[0])*(compare[3] - compare[1]);
	area_combined = area_a + area_b - area_overlap;

	iou = area_overlap / (area_combined + epsilon); */

	return iou;
}

int main() 
{
	ifstream file("C:/Users/Ok Subin/Desktop/imageCut/bird/Yolo_result.txt");
	string lines;
	int left, top, right, bottom, count = 1, i, totalImage = 0;
	int index[4];
	string name[2];
	char lineChar[100];

	while (getline(file, lines))
	{
		if (count % 2 == 1)	// 이름, %만 있는 줄
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
		}

		else // 위치 정보 (left, top, right, bottom,)
		{
			Mat originalImg = imread("C:/Users/Ok Subin/Desktop/imageCut/bird/13.jpg");
			float width = originalImg.cols, height = originalImg.rows;

			strcpy(lineChar, lines.c_str());
			char* line = strtok(lineChar, ": ");
			i = 0;
			while (line != NULL)
			{
				index[i] = atoi(line);
				i++;

				line = strtok(NULL, " ");
			}

			// 5개의 영역으로 나누기 - area1...4 + center
			float area1[4] = { 0, 0, width/2, height/2 };						// left top
			float area2[4] = {width/2, 0, width, height/2};					// right top
			float area3[4] = {0, height/2, width/2, height};					// left bottom
			float area4[4] = {width/2, height/2, width, height};				// right bottom
			float center[4] = {width/4, height/4, (width/4)*3, (height/4)*3};	// center
			float iou[5];

			iou[0] = IOU(index, area1);
			iou[1] = IOU(index, area2);
			iou[2] = IOU(index, area3);
			iou[3] = IOU(index, area4);
			iou[4] = IOU(index, center);

			cout << "width : " << width << "  ,  height : " << height << endl;

			for (int x = 0; x < 4; x++)
			{
				cout << area1[x] << "  ,  " << area2[x] << "  ,  " << area3[x] << "  ,  " << area4[x] << "  ,  " << center[x] << endl;
			}

			for (int x = 0; x < 4; x++)
			{
				cout << index[x] << endl;
			}

			for (int x = 0; x < 5; x++)
			{
				cout << iou[x] << endl;
			}

			float maxValue = 0.0;
			int maxIndex;
			for (int x = 0; x < 5; x++)
			{
				if (iou[x] > maxValue)
				{
					maxValue = iou[x];
					maxIndex = x;
				}
			}

			switch (maxIndex)
			{
			case 0:
				cout << name[0] << " = left top" << endl;
				break;
			case 1:
				cout << name[0] << " = right top" << endl;
				break;
			case 2:
				cout << name[0] << " = left bottom" << endl;
				break;
			case 3:
				cout << name[0] << " = right bottom" << endl;
				break;
			case 4:
				cout << name[0] << " = center" << endl;
			default:
				break;
			}

			cout << "\n\n" << endl;
			count++;
		}
	}
}