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

int tokenCheck(std::string *mainBuffer, Token *token){
  bool openParathesis = false;                /* create the flag for detect open Parathesis */
  bool closeParathesis = false;               /* create the flag for detect close Parathesis */
  std::string *miniBuffer = new std::string;  /* create mini buffer for split the main buffer */
  for (char chr : *mainBuffer){               /* traversing the main buffer */
    switch(chr){                              /* check char from the main buffer */
    case ')': { if (!closeParathesis){
                  closeParathesis = true;       /* detecting closesing Parathesis */
                  token->setValue(*miniBuffer); /* write mini buffer as value in the token */
                  delete miniBuffer;            //< reset mini buffer
                  miniBuffer = new std::string;//< 
                }
                else {
                  return 4;
                }
                break;}

    case '(': { if (!openParathesis){
                  openParathesis = true;        /* detecting opening Parathesis */
                  token->setKey(*miniBuffer);   /* write mini buffer as key in the token */
                  delete miniBuffer;            //< reset mini buffer
                  miniBuffer = new std::string; //<
                }
                else {
                  return 3;
                }
                break;}
    case ' ': {}
    default : { if (!closeParathesis) {       /* check if closed Parathesis*/
                *miniBuffer += chr; }         /* adding the char on the mini buffer */
                else { return 6; } }
    }
  }
  delete miniBuffer;      /* delete mini buffer*/
  return openParathesis && closeParathesis ? 0 : 7;
}

int tokenizator(std::string fileName, std::vector<Token> *tokens) {
  std::fstream file(fileName);          /* open file */
  std::string buffer;                   /* create buffer*/
  for(uint16_t indexLine = 0; getline(file, buffer); indexLine++){         /* reading file */
    Token *token = new Token;           /* create raw token */
    switch (tokenCheck(&buffer, token)){   /* check token with tokenCheck function*/
      case 4:{
        delete token;                     /* delete raw token */
        return 4;
        break;}                         /*return error code*/

      case 3:{
        delete token;                     /* delete raw token */
        return 3;
        break;}                         /*return error code*/

      case 6:{
        delete token;                     /* delete raw token */
        return 6;
        break;}                         /*return error code*/
      
       
      case 0: {
        token->setIndexLine(indexLine);
        tokens->push_back(*token);        /* adding raw token on tokens list */
        delete token;                     /* reset raw token */
        break;}
    }
  }
  return 0; 
}

int project_generator(std::vector<std::string> arguments){
  std::vector<Token>tokens; /* creat tokens list */
  int rezult;
  if (arguments.size() == 1){
    switch(fileCheck(arguments.back())){     /* call fileCheck function for checking file */
    case 1: { return 1; break; }             /*return error code*/
    case 2: { return 2; break; }             /*return error code*/
    case 0: { rezult = tokenizator(arguments.back(), &tokens); break; }
              /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^^^^^^^
                      read error code by tokenizator                 print tokens list     return error code  */
    }
  }
  
  else {
    return 5;
  }
  if (rezult == 0){
    for (uint8_t index = 0; index < tokens.size(); index++){
    if (tokens[index].compareKey("dir")){
      std::filesystem::create_directory(tokens[index].returnValue());
    }
    if (tokens[index].compareKey("file")) {
      std::string buffer = "touch " + tokens[index].returnValue();
      const int count = buffer.size();
      char str[count];
      for (int i = 0; i < count; i++){
        str[i] = buffer[i];
      }
      std::system(str);
      }
    }
  }
  return rezult;
}
