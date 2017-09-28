#ifndef DATA_SOURCE_PLACEHOLDER_H
#define DATA_SOURCE_PLACEHOLDER_H

#include "data_source.hpp"
#include "num_to_str.hpp"

class data_source_placeholder: public data_source{
public:
  data_source_placeholder(uint8_t num = 0):placeholer_number(num){
  }
  virtual size_t get_recomended_length(){
    return 2;
  }
  virtual const char* get_name(char* const output, size_t length = 2){
    output[0] = 'n';
    output[1] = unit_to_char(placeholer_number);
    output[2] = '\0';
    return output;
  }
  virtual const char* get_data(char* const output){
    output[0] = 'd';
    output[1] = unit_to_char(placeholer_number);
    output[2] = '\0';
    return output;
  }
  uint8_t placeholer_number;
};

#endif
