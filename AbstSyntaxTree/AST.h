#ifndef AST_H
#define AST_H
//////////////////////////////////////////////////////////////////////////////
// AST.h - Has helper functions for tree operations                         //
// ver 1.1                                                                  //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author:				 Chiranth Bangalore Sathyaprakash,Syracuse University				    //
//						SUID:258380492,csathyap@syr.edu				        //
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
#include <list>
#include "../Node/element.h"

class AST {						
public:
	void showTree(element*);
	int findComplexity(element*);
	int showCycloComplex(element*,int);
	element* getRootNode() { return rootNode; }
	void setRootNode(element* node) { rootNode = node; }
	void funcComplex(element*);
	size_t getComplexity(element*);
private:
	element* rootNode;
	static int complexity;
	std::list<element*> stack;   
	int complexCount=1;
};


#endif
