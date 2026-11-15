#pragma once

#include <string>
#include <cstdint>

class Token {
private:
  uint16_t indexLine;
  std::string key;
  std::string value;
public:
  void setKey(std::string newKey){
    key = newKey;
  }
  void setValue(std::string newValue){
    value = newValue;
  }
  void setIndexLine(uint16_t newIndexLine){
    indexLine = newIndexLine;
  }
  bool compareKey(std::string otherKey){
    return key == otherKey;
  }
  bool compareValue(std::string otherValue){
    return value == otherValue;
  }
  std::string returnKey(){
    return key;
  }
  std::string returnValue(){
    return value;
  }
  uint16_t returnIndexLine(){
    return indexLine;
  }
};
