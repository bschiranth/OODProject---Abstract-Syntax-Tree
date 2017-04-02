///////////////////////////////////////////////////////////////////////
// MetricExec.cpp - Test										     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Platform:      Dell Inspiron 15, Windows 10                       //
// Application: Lexical Scanner, CSE687 - Object Oriented Design     //
// Original Author:Jim Fawcett, Syracuse University, CST 4-187       //
//                 jfawcett@twcny.rr.com                             //
// Author:Chiranth Bangalore Sathyaprakash,Syracuse University	     //
//				   SUID:258380492,csathyap@syr.edu				     //
///////////////////////////////////////////////////////////////////////

/*
Maintenance History:
====================
ver 1 : 10 Feb 16
- added a functions to test all the requirements
*/
/*
* Package Operations:
* -------------------
* This is a test executive package that shows all the requirements
*
* Build Process:
* --------------
* Required Files:
*   SemiExpression.h, metricAnalysis.h
*
* Build Command: devenv Project1.sln /rebuild debug
*
*/


#include<iostream>
#include<fstream>
#include<string>
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "../MetricsAnalysis/metricAnalysis.h"

using namespace Scanner;
class MetricsExecutive
{
public:

	void TestR1()
	{
		std::cout << "\n\n//=================Demonstrating Requirement 1 ================>\n\n";
		std::cout << "Visual Studio 2015 and its C++ Windows Console Projects, "
			<< "as provided in the ECS computer labs has been used\n";
		std::cout << "\n================================================================>\n";
		std::cout << "\n\n\n";
	}

	void TestR2()
	{
		std::cout << "\n\n//====================Demonstrating Requirement 2================>\n\n";
		std::cout << "C++ standard library's streams for "
			<< "all I/O and new and delete for all heap-based memory management have been used\n";
		std::cout << "\n=================================================================>\n";
		std::cout << "\n\n\n";
	}


	void TestR4()
	{
		std::cout << "\n\n========Demonstrating Requirement 4================>\n\n";
		std::cout << "\n\nParser package with a Parser class that is a container"
			<< "for Rules and that provides the interfaces IRule and IAction "
			<< "for rules contained in the Parser and actions contained in each rule.,\n";
		std::cout << "\n================================================================>\n";
	}

	void TestR3andR5and6()
	{
		std::cout << "\n========Demonstrating Requirement 3,5and6=================>\n";
		std::cout << "Showing Rules and Action package and showing tree";
		std::string fileSpec = FileSystem::Path::getFullFileSpec("./MetricExec/MetricExec.cpp");
		std::string msg = "Processing file ->" + fileSpec;
		

		ConfigParseToConsole configure;
		Parser* pParser = configure.Build();
		pParser = configure.BuildShow();
		try {
			if (pParser) {
				if (!configure.Attach("./MetricExec/MetricExec.cpp"))
				{
					std::cout << "\n  could not open file " << fileSpec << std::endl;
					
				}
			}
			else {
				std::cout << "\n\n  Parser not built\n\n";
			
			}
			// now that parser is built, use it

			while (pParser->next())
				pParser->parse();
			std::cout << "\n";

		}
		catch (std::exception& ex) { std::cout << "\n\n    " << ex.what() << "\n\n"; }
		configure.treeWalk();//call the treewalk 
		std::cout << "\n =================";
		
	}

	void TestR7()
	{
		std::cout << "\n========Demonstrating Requirement 7 =================>\n";
		std::cout << "\n\nA FileMgr package that supports finding files and/or directories "
			<< " in a directory tree rooted at a specified path has been provided, \n"
			<<"\nShowing all files below:\n__________________________________________________\n\n";
		DataStore ds;
		FileMgr fm("..", ds);
		fm.search();
		std::cout << "\n\n  contents of DataStore";
		std::cout << "\n -----------------------";
		for (auto fs : ds)
		{
			std::cout << "\n  " << fs;
		}
		std::cout << "\n===================================================================>\n";
	}


	void TestR10()
	{
		std::cout << "\n\n========Demonstrating Requirement 10================>\n\n";
		std::cout << "This package contains an automated unit test suite which is the metrics executive package that\n"
			<< "enables collecting metrics for all the packages with names that match\n"
			<< "a specified pattern in a directory tree rooted at a specified path and\n"
			<< "exercises all of the packages provided in your submission and \n"
			<< "demonstrates that you met all requirements\n";
	}

	void TestR8andR9(std::string s1,std::string s2)
	{
		std::cout << "\n\n========Demosntrating Requirement 8 and 9================>\n\n";
		std::cout << "\n\nA MetricsAnalysis package for evaluating and displaying \n "
			<< "the size and complexity of all global functions, static member functions,\n"
			<< "and non-static member functions in each of a set of specified packages.\n"
			<< "in a directory tree rooted at a specified path has been provided, \n";
		std::cout << "\n SHowing .cpp files below\n______________________________________________________________\n";
		std::cout << "\n =================";
		DataStore ds;
		FileMgr fm(s1, ds);
		//fm.addPattern("*.h");
		fm.addPattern(s2);
		//fm.addPattern("*.partial");
		fm.search();
		std::cout << "\n\n  contents of DataStore";std::cout << "\n -----------------------";
		for (auto fs : ds) std::cout << "\n  " << fs;
		for (auto fs : ds){
			std::string fileSpec = FileSystem::Path::getFullFileSpec(fs);
			std::string msg = "Processing file ->" + fileSpec;
			ConfigParseToConsole configure;
			Parser* pParser = configure.Build();
			try {
				if (pParser) {
					if (!configure.Attach(fs)){std::cout << "\n  could not open file " << fileSpec << std::endl;}
				}
				else {std::cout << "\n\n  Parser not built\n\n";}
				while (pParser->next())
					pParser->parse();
				std::cout << "\n";
			}
			catch (std::exception& ex) { std::cout << "\n\n    " << ex.what() << "\n\n"; }
			configure.treeWalk();//call the treewalk 
			std::cout << "\n =================";
		}
		std::cout << "\n\n";std::cout << "\n===============================================================>\n";
	}
};

void main(int argc, char* argv[])
{
	MetricsExecutive me;
	me.TestR1();
	me.TestR2();
	me.TestR4();
	me.TestR7();
	me.TestR3andR5and6();
	me.TestR8andR9(argv[1],argv[2]);
	me.TestR10();

}

