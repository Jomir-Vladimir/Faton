#include "project_generator.hpp"
#include "token.hpp"
#include <vector>

void printTokens(std::vector<Token> *tokens){
  for (short index = 0; index < tokens->size(); index++){
    (*tokens)[index].printKey();
    (*tokens)[index].printValue();
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

bool tokenCheck(std::string *buffer, Token *token){
  bool openParathesis = false;
  bool closeParathesis = false;
  std::string *miniBuffer = new std::string;
  for (char chr : *buffer){
    switch(chr){
    case ')': { closeParathesis = true;
                token->setValue(*miniBuffer);
                delete miniBuffer;
                miniBuffer = new std::string;
                break;}

    case '(': { openParathesis = true;
                token->setKey(*miniBuffer);
                delete miniBuffer;
                miniBuffer = new std::string;
                break;}
    case ' ': {}
    default : { if (!closeParathesis) { *miniBuffer += chr; } else { return false; } }

    delete miniBuffer;
    }
  }
  return openParathesis && closeParathesis;
}

int tokenizator(std::string fileName, std::vector<Token> *tokens) {
  std::fstream file(fileName);
  std::string buffer;
  while(getline(file, buffer)){
    Token *token = new Token;
    if (!tokenCheck(&buffer, token)){
      delete token;
      return 3;
    }
    else {
      tokens->push_back(*token); 
      delete token;
    }
  }
  return 0;
}

int generator(std::vector<std::string> arguments){
  std::vector<Token>tokens;
  if (arguments.size() == 1){
    switch(fileCheck(arguments.back())){
    case 1: { return 1; break; }
    case 2: { return 2; break; }
    case 0: { int rezult = tokenizator(arguments.back(), &tokens); printTokens(&tokens); return rezult; break; }
    }
  }
  
  else {
    return 5;
  }
}
