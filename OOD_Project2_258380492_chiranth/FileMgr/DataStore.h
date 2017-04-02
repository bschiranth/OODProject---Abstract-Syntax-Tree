#ifndef DATASTORE_H
#define DATASTORE_H

//////////////////////////////////////////////////////////////////////////////
// DataStore.h - Store results of file search                               //
// ver 1.1                                                                  //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author:Chiranth Bangalore Sathyaprakash,Syracuse University				//
//						SUID:258380492,csathyap@syr.edu				        //
//////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This file provides data store operations

Public Interface:
=================
void save(const std::string& filespec) 
void save(const std::string& filename, const std::string& path) 
iterator begin() 
iterator end()

Required Files:
===============
element.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 03/14/15
- first release
*/

#include <vector>

class DataStore
{
public:
	using iterator = std::vector<std::string>::iterator;
	void save(const std::string& filespec) { store.push_back(filespec); }
	void save(const std::string& filename, const std::string& path) {}
	iterator begin() { return store.begin(); }
	iterator end() { return store.end(); }
private:
	std::vector<std::string> store;
};
#endif
