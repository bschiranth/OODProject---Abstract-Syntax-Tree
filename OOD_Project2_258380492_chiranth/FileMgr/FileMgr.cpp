//////////////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns						//
//               on a specified path										//
// ver 2.0																    //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author:Chiranth Bangalore Sathyaprakash,Syracuse University				//
//						  SUID:258380492,csathyap@syr.edu				    //
//////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This file  finds files matching specified patterns on a specified path

Public Interface:
=================
FileMgr(const std::string& path, DataStore& ds) - construcotr
void addPattern(const std::string& patt) - adds the specified pattern
void search() - calls find
void find(const std::string& path) - find all files in the path

Required Files:
===============
element.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
/*
* ver 2.0 : 12 Mar 2016
* - fixes bug in directory recursion in find(path)
* - reduces scope of for loop in find for efficiency
* ver 1.0 : 19 Feb 2016
* - first release
*/
#include "FileMgr.h"
#include "DataStore.h"
#include <iostream>

#ifdef TEST_FILEMGR

int main()
{
	std::cout << "\n  Testing FileMgr";
	std::cout << "\n =================";

	DataStore ds;
	FileMgr fm("..", ds);
	//fm.addPattern("*.h");
	//fm.addPattern("*.cpp");
	//fm.addPattern("*.partial");
	fm.search();

	std::cout << "\n\n  contents of DataStore";
	std::cout << "\n -----------------------";
	for (auto fs : ds)
	{
		std::cout << "\n  " << fs;
	}
	std::cout << "\n\n";
	return 0;
}
#endif
