#include "project_generator.hpp"

void debugTokens(std::vector<Token> *tokens){
  for (uint16_t index = 0; index < tokens->size(); index++){
    std::cout << "Token: " <<
                 "line: " << (*tokens)[index].returnIndexLine() << "; "
                 "key: "<< (*tokens)[index].returnKey() << "; "
                 "value:"<<(*tokens)[index].returnValue() << ";\n";
    
  }
}

int fileCheck(std::string fileName) {
  if (std::filesystem::exists(fileName)) { 
    if(fileName == "ProjectConfig.txt") {
      return 0;
    }
    else {
      return 1;
    }
  }
  return 2;
}

bool tokenCheck(std::string *mainBuffer, Token *token){
  bool openParathesis = false;                /* create the flag for detect open Parathesis */
  bool closeParathesis = false;               /* create the flag for detect close Parathesis */
  std::string *miniBuffer = new std::string;  /* create mini buffer for split the main buffer */
  for (char chr : *mainBuffer){               /* traversing the main buffer */
    switch(chr){                              /* check char from the main buffer */
    case ')': { closeParathesis = true;       /* detecting closesing Parathesis */
                token->setValue(*miniBuffer); /* write mini buffer as value in the token */
                delete miniBuffer;            //< reset mini buffer
                miniBuffer = new std::string; //< 
                break;}

    case '(': { openParathesis = true;        /* detecting opening Parathesis */
                token->setKey(*miniBuffer);   /* write mini buffer as key in the token */
                delete miniBuffer;            //< reset mini buffer
                miniBuffer = new std::string; //<
                break;}
    case ' ': {}
    default : { if (!closeParathesis) {       /* check if closed Parathesis*/
                *miniBuffer += chr; }         /* adding the char on the mini buffer */
                else { return false; } }
    }
  }
  delete miniBuffer;      /* delete mini buffer*/
  return openParathesis && closeParathesis;
}

int tokenizator(std::string fileName, std::vector<Token> *tokens) {
  std::fstream file(fileName);          /* open file */
  std::string buffer;                   /* create buffer*/
  for(uint16_t indexLine = 0; getline(file, buffer); indexLine++){         /* reading file */
    Token *token = new Token;           /* create raw token */
    if (!tokenCheck(&buffer, token)){   /* check token with tokenCheck function*/
      delete token;                     /* delete raw token */
      return 3;                         /*return error code*/
    }
    else {
      token->setIndexLine(indexLine);
      tokens->push_back(*token);        /* adding raw token on tokens list */
      delete token;                     /* delete raw token */
    }
  }
  return 0; 
}

int project_generator(std::vector<std::string> arguments){
  std::vector<Token>tokens;                  /* creat tokens list */
  if (arguments.size() == 1){
    switch(fileCheck(arguments.back())){     /* call fileCheck function for checking file */
    case 1: { return 1; break; }             /*return error code*/
    case 2: { return 2; break; }             /*return error code*/
    case 0: { int rezult = tokenizator(arguments.back(), &tokens); debugTokens(&tokens); return rezult; break; }
              /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^^^^^^^
                      read error code by tokenizator                 print tokens list     return error code  */
    }
  }
  
  else {
    return 5;
  }
}
