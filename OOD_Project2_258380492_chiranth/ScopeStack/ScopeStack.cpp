///////////////////////////////////////////////////////////////////////////////
// ScopeStack.cpp - implements template stack holding specified element type //
// ver 2.1                                                                   //
// Language:			C++, Visual Studio 2015                              //
// Platform:			 Dell Inspiron 15, Windows 10                        //
// Application:			 Code Parser with Abstract Syntax Tree (AST)         //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University          //
//						 (315) 443-3948, jfawcett@twcny.rr.com               //
// Author:Chiranth Bangalore Sathyaprakash,Syracuse University				 //
//						SUID:258380492,csathyap@syr.edu				         //
//////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This package contains one class: ScopeStack<element>.  The element type
is an application specific type designed to hold whatever information you
need to stack.

Public Interface:
=================
ScopeStack<element> stack;
// define some element type
element elem;
stack.push(elem);
element popped = stack.pop();

Required Files:
===============
ScopeStack.h, ScopeStack.cpp

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
ver 2.1 : 02 Jun 11
- changed ScopeStack type to single template argument intended to be
an application specific type (usually a struct that holds whatever
is needed)
ver 2.0 : 02 Feb 11
- fixed bug in pop() method found by Drumil Bhattad
ver 1.0 : 31 Jan 11
- first release
*/

//----< test stub >------------------------------------------------------

#ifdef TEST_SCOPESTACK

#include "ScopeStack.h"
#include "../Node/element.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>



void TreeWalk(element* pItem)
{

  static size_t indentLevel = 0;
  std::cout << "\n  " << std::string(2*indentLevel, ' ') << pItem->show();
  auto iter = pItem->_children.begin();
  ++indentLevel;
  while (iter != pItem->_children.end())// till iter is not pointing to last element
  {
    TreeWalk(*iter);
    ++iter;
  }
  --indentLevel;
}
/*
int main()
{
  std::cout << "\n  Testing Scope Stack";
  std::cout << "\n =====================\n";

  std::cout << "\n  pushing items onto ScopeStack instance after adding startLineCount";
  std::cout << "\n --------------------------------------------------------------------";

  ScopeStack<element*> testStack; // object of Scopestack
  element* pItem = new element; // create a pointer to new struct element

  pItem->type = "function"; //type and name are string
  pItem->name = "fun1";
  pItem->startLineCount = 33;
  testStack.push(pItem); // pushes element to list

  pItem = new element;
  pItem->type = "if";
  pItem->name = "";
  pItem->startLineCount = 38;
  (testStack.top()->_children).push_back(pItem);// teststack.top() - is a pointer to stryct element and we are
  //accessing its children which is a vector and we are pushing back the new struct elem to the vector
  testStack.push(pItem);//pushes the element to the list stack

  pItem = new element;
  pItem->type = "for";
  pItem->name = "";
  pItem->startLineCount = 40;
  (testStack.top()->_children).push_back(pItem);
  testStack.push(pItem);


  showStack<element>(testStack, false);
  std::cout << std::endl;

  std::cout << "\n  Popping two items off ScopeStack after adding endLineCount";
  std::cout << "\n ------------------------------------------------------------";

  testStack.top()->endLineCount = 50;
  std::cout << "\n  " << testStack.pop()->show();
  testStack.top()->endLineCount = 55;
  std::cout << "\n  " << testStack.pop()->show();
  std::cout << "\n";

  std::cout << "\n  Pushing another item onto ScopeStack after adding startLineElement";
  std::cout << "\n --------------------------------------------------------------------";
  pItem = new element;
  pItem->type = "while";
  pItem->name = "";
  pItem->startLineCount = 60;
  (testStack.top()->_children).push_back(pItem);
  testStack.push(pItem);

  std::cout << "\n  Stack now contains:";
  std::cout << "\n ---------------------";
  showStack<element>(testStack, false);
  std::cout << "\n";

  std::cout << "\n  Popping last elements off stack after adding endLineCount";
  std::cout << "\n -----------------------------------------------------------";
  testStack.top()->endLineCount = 70;
  element* pTop = testStack.pop();
  std::cout << "\n  " << pTop->show();
  testStack.top()->endLineCount = 75;
  pTop = testStack.pop();
  std::cout << "\n  " << pTop->show();
  std::cout << "\n";

  std::cout << "\n  Walking simulated AST tree:";
  std::cout << "\n -----------------------------";
  TreeWalk(pTop);
  std::cout << "\n\n";
}
*/
#endif
