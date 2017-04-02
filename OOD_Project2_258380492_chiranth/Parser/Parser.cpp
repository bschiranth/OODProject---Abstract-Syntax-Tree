//////////////////////////////////////////////////////////////////////////////
//  Parser.cpp - Analyzes C++ language constructs                           //
//  ver 1.4																    //
// Language:			C++, Visual Studio 2015                             //
// Platform:			 Dell Inspiron 15, Windows 10                       //
// Application:			 Code Parser with Abstract Syntax Tree (AST)        //
// Orignial Author:		Jim Fawcett, CST 4-187, Syracuse University         //
//						 (315) 443-3948, jfawcett@twcny.rr.com              //
// Author:				 Chiranth BS,Syracuse University				    //
//						SUID:258380492,csathyap@syr.edu				        //
//////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a Parser class.  Its instances collect
semi-expressions from a file for analysis.  Analysis consists of
applying a set of rules to the semi-expression, and for each rule
that matches, a set of actions is invoked.

Public Interface:
=================
Toker t(someFile);              // create tokenizer instance
SemiExp se(&t);                 // create a SemiExp attached to tokenizer
Parser parser(se);              // now we have a parser
Rule1 r1;                       // create instance of a derived Rule class
Action1 a1;                     // create a derived action
r1.addAction(&a1);              // register action with the rule
parser.addRule(&r1);            // register rule with parser
while(se.getSemiExp())          // get semi-expression
parser.parse();               //   and parse it

Build Process:
==============
Required files
- Parser.h, Parser.cpp, SemiExpression.h, SemiExpression.cpp,
tokenizer.h, tokenizer.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
ConfigureParser.h, ConfigureParser.cpp
Build commands (either one)
- devenv Parser.sln
- cl /EHsc /DTEST_PARSER parser.cpp semiexpression.cpp tokenizer.cpp \
ActionsAndRules.cpp ConfigureParser.cpp /link setargv.obj

Maintenance History:
====================
ver 1.4 : 15 Feb 16
- removed all folding rules code
- changed solution folder layout which caused changes in many of the
include paths
- small modifications to one of the derived actions
- now preface (new) Toker and SemiExp with Scanner namespace
ver 1.3 : 02 Jun 11
- added use of folding rules in get();
ver 1.2 : 17 Jan 09
- modified to accept pointer to interface ITokCollection instead of
SemiExpression
ver 1.1 : 17 Sep 07
- cosmetic modifications to comments on this page
ver 1.0 : 12 Jan 06
- first release

*/
#include <iostream>
#include <string>
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
#include "Parser.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"

using namespace Scanner;
using namespace Utilities;

//----< register parsing rule >--------------------------------

void Parser::addRule(IRule* pRule)
{
  rules.push_back(pRule); // push the rule pointer to the vector
}
//----< get next ITokCollection >------------------------------

bool Parser::next() 
{ 
  // default operation of doFold(pTokColl) is to simply return
  // - code analysis provides specific rules for handling
  //   for statements and operator expressions which are
  //   bound in ConfigureParser.cpp

  bool succeeded = pTokColl->get();
  if(!succeeded)
    return false;
  return true;
}

//----< parse the SemiExp by applying all rules to it >--------

bool Parser::parse()
{
  bool succeeded = false;
  for(size_t i=0; i<rules.size(); ++i)
  {
    if(rules[i]->doTest(pTokColl))
      succeeded = true;
  }
  return succeeded;
}
//----< register action with a rule >--------------------------

void IRule::addAction(IAction *pAction)
{
  actions.push_back(pAction);
}
//----< invoke all actions associated with a rule >------------

void IRule::doActions(ITokCollection*& pTokColl)
{
  if(actions.size() > 0)
    for(size_t i=0; i<actions.size(); ++i)
      actions[i]->doAction(pTokColl);
}

//----< test stub >--------------------------------------------

#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"

#ifdef TEST_PARSER

#include <queue>
#include <string>
#define Util StringHelper

int main(int argc, char* argv[])
{
  Util::Title("Testing Parser Class", '=');
  putline();
  // collecting tokens from files, named on the command line
  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::string fileSpec = FileSystem::Path::getFullFileSpec(argv[i]);
    std::string msg = "Processing file ->" + fileSpec;
    Util::title(msg);
    putline();

    ConfigParseToConsole configure;
    Parser* pParser = configure.Build();
    try{
      if(pParser){
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << fileSpec << std::endl;
          continue;
        }
      }
      else{
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n";
	  
    }
    catch(std::exception& ex) {std::cout << "\n\n    " << ex.what() << "\n\n";}
	configure.treeWalk();//call the treewalk }
  std::cout << "\n";
}

#endif
