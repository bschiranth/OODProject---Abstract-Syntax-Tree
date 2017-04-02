//////////////////////////////////////////////////////////////////////////////
//  ConfigureParser.cpp - builds and configures parsers					    //
//  ver 2.2																	//																	
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
This module builds and configures parsers.  It builds the parser
parts and configures them with application specific rules and actions.

Public Interface:
=================
ConfigParseToConsole conConfig;
conConfig.Build();- all the parts get assembled
conConfig.Attach(someFileName); - attach toker to a file stream or stringstream
treeWalk - calls the display tree function

Build Process:
==============
Required files
- ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
Build commands (either one)
- devenv Project1HelpS06.sln
- cl /EHsc /DTEST_PARSER ConfigureParser.cpp parser.cpp \
ActionsAndRules.cpp \
semiexpression.cpp tokenizer.cpp /link setargv.obj

Maintenance History:
====================
ver 2.2 : 14 Mar 16
- Added treeWalk function
ver 2.1 : 19 Feb 16
- Added PrintFunction action to FunctionDefinition rule
ver 2.0 : 01 Jun 11
- Major revisions to begin building a strong code analyzer
ver 1.1 : 01 Feb 06
- cosmetic changes to ConfigureParser.cpp
ver 1.0 : 12 Jan 06
- first release

*/
#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"

using namespace Scanner;

//----< destructor releases all parts >------------------------------

ConfigParseToConsole::~ConfigParseToConsole()
{
  // when Builder goes out of scope, everything must be deallocated

  delete pHandlePush;
  delete pBeginningOfScope;
  delete pHandlePop;
  delete pEndOfScope;
  delete pPrintFunction;
  delete pPushFunction;
  delete pFunctionDefinition;
  delete pDeclaration;
  delete pShowDeclaration;
  delete pExecutable;
  delete pShowExecutable;
  delete pRepo;
  delete pParser;
  delete pSemi;
  delete pToker;
  /////////////////////////////////////////////////////////
  delete pLoops;
  delete pShowLoops;
  delete pClassStruct;
  delete pPushClassStruct;
  delete pShowClassOrStruct;
  delete   pLambda;
  delete pPushLambda;
 delete pShowLambda;
  pIn->close();
  delete pIn;
}
//----< attach toker to a file stream or stringstream >------------

bool ConfigParseToConsole::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;
  pIn = new std::ifstream(name);
  if (!pIn->good())
    return false;
  return pToker->attach(pIn);
}
//----< Here's where all the parts get assembled >----------------

Parser* ConfigParseToConsole::Build()
{try {// add Parser's main parts
    pToker = new Toker;pToker->returnComments(false);
    pSemi = new SemiExp(pToker);pParser = new Parser(pSemi);
    pRepo = new Repository(pToker);pRepo->configRoot();
 // configure to manage scope these must come first - they return true on match so rule checking continues
	pBeginningOfScope = new BeginningOfScope(); pHandlePush = new HandlePush(pRepo);
    pBeginningOfScope->addAction(pHandlePush); pParser->addRule(pBeginningOfScope);
    pEndOfScope = new EndOfScope(); pHandlePop = new HandlePop(pRepo);
    pEndOfScope->addAction(pHandlePop); pParser->addRule(pEndOfScope);
    // configure to detect and act on function definitions these will stop further rule checking by returning false
    pFunctionDefinition = new FunctionDefinition; 
	pPushFunction = new PushFunction(pRepo);  // no action
    //pPrintFunction = new PrintFunction(pRepo); 
	pFunctionDefinition->addAction(pPushFunction);
    //pFunctionDefinition->addAction(pPrintFunction);
	pParser->addRule(pFunctionDefinition);
    // configure to detect and act on declarations and Executables
    pDeclaration = new Declaration; /*pShowDeclaration = new ShowDeclaration;
    pDeclaration->addAction(pShowDeclaration);*/ /*pParser->addRule(pDeclaration);*/
    pExecutable = new Executable; /*pShowExecutable = new ShowExecutable;
    pExecutable->addAction(pShowExecutable);*/pParser->addRule(pExecutable);
	// configure to detect and act on conditions
	pLoops = new loops;pShowLoops = new showLoops(pRepo);
	pLoops->addAction(pShowLoops);pParser->addRule(pLoops);
	// configure to detect and act on struct and class
	 pClassStruct = new  ClassStruct; pPushClassStruct =  new pushClassStruct(pRepo);
	  /*pShowClassOrStruct = new showClassOrStruct(pRepo); */
	  pClassStruct->addAction(pPushClassStruct);
	 /* pClassStruct->addAction(pShowClassOrStruct);*/pParser->addRule(pClassStruct);
	///////////////////////////////////////////////////////////////////
	 pLambda = new lambda;pPushLambda=new PushLambda(pRepo);
	/* pShowLambda = new showLambda(pRepo);*/pLambda->addAction(pPushLambda);
	 /*pLambda->addAction(pShowLambda);*/ pParser->addRule(pLambda);
    return pParser; }
  catch(std::exception& ex) {std::cout << "\n\n  " << ex.what() << "\n\n"; return 0; }
}

Parser* ConfigParseToConsole::BuildShow() {
	pParser->addRule(pDeclaration);
	pPrintFunction = new PrintFunction(pRepo);
	pFunctionDefinition->addAction(pPrintFunction);
	pShowDeclaration = new ShowDeclaration;
	pDeclaration->addAction(pShowDeclaration);
	pShowExecutable = new ShowExecutable;
	pExecutable->addAction(pShowExecutable);
	pShowClassOrStruct = new showClassOrStruct(pRepo);
	pClassStruct->addAction(pShowClassOrStruct);
	pShowLambda = new showLambda(pRepo);
	pLambda->addAction(pShowLambda);
	return pParser;
}

//------< walks the tree and displays through rootnode >------------------
void ConfigParseToConsole::treeWalk()
{
	pRepo->absTree->showTree(pRepo->absTree->getRootNode());
	std::cout<<"\n\n\tFile Complexity is = \t" 
		<<pRepo->absTree->findComplexity(pRepo->absTree->getRootNode())<<std::endl;
	std::cout << "\n\n";pRepo->absTree->funcComplex(pRepo->absTree->getRootNode());
}

#ifdef TEST_CONFIGUREPARSER

#include <queue>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ConfigureParser module\n "
            << std::string(32,'=') << std::endl;

  // collecting tokens from files, named on the command line

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');

    ConfigParseToConsole configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";
    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }
    std::cout << "\n\n";
  }
}

#endif
