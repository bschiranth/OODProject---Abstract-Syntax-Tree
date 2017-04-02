#ifndef SCOPESTACK_H
#define SCOPESTACK_H
//////////////////////////////////////////////////////////////////////////////
// ScopeStack.h - implements template stack holding specified element type  //
// ver 2.1                                                                 //
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
#include <list>

// element is a application specific type.  It must provide a function:
// std::string show() that returns a string display of its parts. see
// test stub for an example.

template<typename element> 
class ScopeStack { //template								
public:
  typename typedef std::list<element>::iterator iterator;	
  void push(const element& item);	
  element pop();
  element top(); // returns last element in the list
  size_t size();
  iterator begin();
  iterator end();
private:
  std::list<element> stack;   // stack is a list of struct element
};

template<typename element>
typename inline size_t ScopeStack<element>::size() { return stack.size(); }  //function belongs to ScopeStack template class and returns size of list(stack)

template<typename element>
typename inline ScopeStack<element>::iterator ScopeStack<element>::begin() { return stack.begin(); }//returns iterator pointig to first element in the list

template<typename element>
typename inline ScopeStack<element>::iterator ScopeStack<element>::end() { return stack.end(); } //returns iterator pointig to last element in the list

template<typename element>
void ScopeStack<element>::push(const element& item)
{
  stack.push_back(item); // adds item after the last element in the list
}

template<typename element>
element ScopeStack<element>::pop() 
{ 
  element item = stack.back(); //last element in the list
  stack.pop_back(); //delete last element in the list
  return item; 
}

template<typename element>
element ScopeStack<element>::top()
{
  return stack.back(); //returns reference to last element in the list
}

//<-----------------show by reference----->
template<typename element>
void showStack(ScopeStack<element>& stack, bool indent = true)//takes in reference to Scopestack template class
{
  if (stack.size() == 0)
  {
    std::cout << "\n  ScopeStack is empty";
    return;
  }
  ScopeStack<element>::iterator iter = stack.begin();// iter is now pointing to first element in the list
  while (iter != stack.end()) // till iter reaches end of list
  {
    std::string strIndent = std::string(2 * stack.size(), ' '); // fills the string with 2*list size with blank spaces
    if (!indent)
      strIndent = "";
    element temp = *iter; // copy iterator to temp
    std::cout << "\n  " << strIndent << temp->show();
    ++iter; //
  }
}

//--------< show by pointer >--------//
template<typename element>
void showStack(ScopeStack<element*>& stack, bool indent = true)
{
  if (stack.size() == 0)
  {
    std::cout << "\n  ScopeStack is empty";
    return;
  }
  ScopeStack<element*>::iterator iter = stack.begin();
  while (iter != stack.end())
  {
    std::string strIndent = std::string(2 * stack.size(), ' ');
    if (!indent)
      strIndent = "";
    std::cout << "\n  " << strIndent << ((*iter)->show());
    ++iter;
  }
}
#endif
