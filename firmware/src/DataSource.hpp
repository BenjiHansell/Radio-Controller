#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <stddef.h>

// base class for any class containing data which might be written to the display
class DataSource{
public:
  virtual size_t get_recomended_length(){return 2;}
  virtual const char* get_name(char* const output, size_t length){
    for(decltype(length) i = 0; i < length; i++) output[i] = '?';
    output[length] = '\0';
    return output;
  }
  virtual const char* get_name(char* const output){
    return get_name(output, get_recomended_length());
  }
  virtual void get_data(char* const output, size_t length){
    for(decltype(length) i = 0; i < length; i++) output[i] = '!';
    output[length] = '\0';
  }
  virtual const char* get_data(char* const output){
    get_data(output, get_recomended_length());
    return output;
  }
  virtual bool has_changed(){ // returns true if the value has changes since the most recent call to get_data() (to reduce number of calls to lcd.write())
    return 1; // returns true by default (in case daughter class doesn't implement method)
  }
};

#endif
