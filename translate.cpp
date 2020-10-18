#include "pch.h"
#include <iostream>
#include "translate.h"
#include <string>
#include <fstream>

using namespace std;

string translate(const char* engSentence)
{
	PyObject *pName, *pModule, *pFunc, *pValue, *pArg;

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	pName = PyUnicode_FromString("transToKorean");
	pModule = PyImport_Import(pName);
	pFunc = PyObject_GetAttrString(pModule, "translate");
	pArg = Py_BuildValue("(z)", (const char *)engSentence); 
	pValue = PyObject_CallObject(pFunc, pArg); 
	PyObject *objectsRepresentation = PyObject_Repr(pValue); 
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); 
	string result = PyBytes_AsString(str); 

	Py_Finalize();

	return result;
}