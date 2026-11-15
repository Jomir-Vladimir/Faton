#include "../../domain/token.hpp"


#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <filesystem>

void debugTokens(std::vector<Token> *tokens);

int fileCheck(std::string fileName); /* check a file get by the user */

bool tokenCheck(std::string *mainBuffer, Token *token); /* check a token created by tokenizato */

int tokenizator(std::string fileName, std::vector<Token> *tokens); /* split the file content into tokens */

int project_generator(std::vector <std::string> arguments); /* create project according to a ProjectConfig.txt file */
