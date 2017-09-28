#ifndef COUNTER_H
#define COUNTER_H

template<typename T, T floor, T celing>
class counter{ // base class
public:
  counter(const T& other):
    value(other)
  {}
  operator T(){
    return value;
  }
  counter<T, floor, celing>& operator++()
  {
      ++value;
      normalise();
      return *this;
  }
  counter<T, floor, celing> operator++(int)
  {
      counter<T, floor, celing> tmp(*this);
      operator++(); // pre-increment
      return tmp;   // return old value
  }
  counter<T, floor, celing>& operator--()
  {
      --value;
      normalise();
      return *this;
  }
  counter<T, floor, celing> operator--(int)
  {
      counter<T, floor, celing> tmp(*this);
      operator--(); // pre-increment
      return tmp;   // return old value
  }
  virtual void normalise(){};
protected:
  T value;
};

template<typename T, T floor, T celing>
class counter_rollover: public counter<T, floor, celing>{
public:
  counter_rollover(const T& other = floor):
    counter<T, floor, celing>::counter(other)
  {}
  virtual void normalise(){
    while(counter<T, floor, celing>::value > celing) counter<T, floor, celing>::value -= (celing - floor + 1);
    while(counter<T, floor, celing>::value < floor) counter<T, floor, celing>::value += (celing - floor + 1);
  }
};

template<typename T, T floor, T celing>
class counter_stop: public counter<T, floor, celing>{
public:
  counter_stop(const T& other):
    counter<T, floor, celing>::counter(other)
  {}
  virtual void normalise(){
    while(counter<T, floor, celing>::value > celing) counter<T, floor, celing>::value--;
    while(counter<T, floor, celing>::value < floor) counter<T, floor, celing>::value++;
  }
  bool at_lower_limit(){return counter<T, floor, celing>::value==floor;}
  bool at_upper_limit(){return counter<T, floor, celing>::value==celing;}
};

#endif
