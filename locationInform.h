#pragma once
#include <string>

using namespace std;

void location(string yoloFileName, string originalFile, string resultArray[3][100]);
float IOU(int roi[], float compare[]);