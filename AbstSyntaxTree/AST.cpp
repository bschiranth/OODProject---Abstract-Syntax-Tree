//////////////////////////////////////////////////////////////////////////////
// AST.cpp - Has helper functions for tree operations                       //
// ver 1.1                                                                  //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author: Chiranth Bangalore Sathyaprakash,Syracuse University				    //
//						  SUID:258380492,csathyap@syr.edu				    //
//////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This package contains one class:AST.
It provides a facility for building an abstract syntax tree that provides an interface
for adding scope nodes to the tree and an methods to analyze the contents of the tree.

Public Interface:
=================
void showTree(element*)-Walks the tree and  displays it
int findComplexity(element*)- resets the complexity function
int showCycloComplex(element*,int)- Shows the function complexity
element* getRootNode() - gets the rootnode
void setRootNode(element* node) - sets the root node
void funcComplex(element*)-Displays details of each function
size_t getComplexity(element*)-returns the functin complexity

Required Files:
===============
element.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
ver 1.1 : 03/16/15
- added methods to find complexity
ver 1.0 : 03/13/15
- first release
*/
#include "AST.h"

int AST::complexity = 0;

//---------<  Walks the tree and  displays it >-----------------
void AST::showTree(element *pItem)
{
		static size_t indentLevel = 0;
		static int complex = 1;
		std::cout << "\n  " << std::string(2 * indentLevel, ' ') << pItem->show();
		//std::cout << "\n complexity is: " << complex;
		auto iter = pItem->_children.begin();
		++indentLevel;
		++complex;
		while (iter != pItem->_children.end())
		{
			showTree(*iter);
			++iter;
		}
		--indentLevel;
}


/////////////////////////////////////////////////////////////////////

//----------< Shows the function complexity >--------
int AST::showCycloComplex(element* pItem, int cnt) 
{
	complexity=cnt;
	++complexity;
	auto iter = pItem->_children.begin();
	while (iter != pItem->_children.end())
	{
		showCycloComplex(*iter, complexity);
		++iter;
	}
	return complexity;
}
////////////////////////////////////////////////////////////////////
//---------< resets the complexity function  >------------
int AST::findComplexity(element* node)
{
	return showCycloComplex(node, 0);
}
////////////////////////////////////////////////////////////////////////

//---------<  returns the functin complexity >------------
size_t AST::getComplexity(element* node)
{
	size_t count = 0;
	if (node->_children.size() == 0)
		return 1;
	else {
		for (size_t i = 0; i < node->_children.size(); i++)
			count = 1 + count + getComplexity(node->_children[i]);
		return count;
	}
}

//---------< Displays details of each function  >------------
void AST::funcComplex(element* node)
{
	if (complexCount == 1) {
		std::cout << std::endl << "\nFunction complexities list" << std::endl;
		std::cout << "__________________________________________________________" << std::endl;
		std::cout << " type\t\t\t " << " " << "\t\tname" << " \t\t\t " << "no of lines";
		std::cout << " \t\t\t" << "complexity" << std::endl; complexCount++;
		std::cout << std::endl << std::endl;
	}
	std::string line1;
	std::string line2;

	if (node->type == "function") {//
		line1 = "\t\t\t\t";
		if (node->name.size()>7 && node->name.size() <= 12)line2 = "\t\t\t\t";
		else if (node->name.size() >= 13)line2 = "\t\t\t\t";
		else line2 = "\t\t\t\t";
		std::cout << node->type << line1 
			<< node->name << line2 << (node->endLineCount - node->startLineCount + 1);
		std::cout << " \t\t\t\t " << getComplexity(node) << std::endl;
		auto iter = node->_children.begin();
		while (iter != node->_children.end())
		{
			funcComplex(*iter);
			++iter;
		}
	}
	else {
		auto iter = node->_children.begin();
		while (iter != node->_children.end())
		{
			funcComplex(*iter);
			++iter;
		}
	}
}