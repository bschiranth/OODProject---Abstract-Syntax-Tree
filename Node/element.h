#pragma once
//////////////////////////////////////////////////////////////////////////////
// element.h -defines a struct element that can be used wherever needed     //
// ver 1.0                                                                  //                                                                //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author:Chiranth Bangalore Sathyaprakash,Syracuse University				//
//					   SUID:258380492,csathyap@syr.edu				        //
//////////////////////////////////////////////////////////////////////////////
/*Package Operations :
== == == == == == == == == =
This file defines a struct element that can be used wherever needed 

Public Interface :
== == == == == == == == =
void show() - // displays output in the format (name,type,startline,endline)
*/

#include<string>
#include <vector>
#include <iostream>
#include <sstream>
struct element   // element is a struct
{
	std::string type;
	std::string name;
	size_t startLineCount = 0;
	size_t endLineCount = 0;
	std::string show() // displays output in the format (name,type,startline,endline)
	{
		std::ostringstream temp;		//temp is of type ostringstream
		temp << "(";
		temp << type;
		temp << ", ";
		temp << name;
		temp << ", ";
		temp << startLineCount;
		temp << ", ";
		temp << endLineCount;
		temp << ")";
		return temp.str();// converts the format above to a string object to be displayed
	}
	std::vector<element*> _children; //children is a vector of element pointers
};