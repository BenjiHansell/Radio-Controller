#pragma once

#include <stdint.h>
#include <EEPROM.h>

extern uint16_t total_memory_stored;
extern const uint16_t total_memory_size;

template<typename T>
struct add_lvalue_reference
{
   using type = T&;
};

template<class T>
class Memorable
{
public:
	Memorable();
	operator T(){ return x;}
	//operator const T&(){ return x;}
	Memorable<T>& operator=(const T& _x) { x = _x; write(); return *this;}
	void write();
	void read();
	~Memorable();
	//decltype(T[0]) & operator[](size_t idx) { return x[idx]; }
  //const T& operator[](size_t idx) const { return x[idx]; }
	T x;
private:
	uint16_t memory_location;
};

template<class T>
Memorable<T>::Memorable() :
	memory_location(total_memory_stored)
{
	total_memory_stored += sizeof(T);
	read();
}

template<class T>
Memorable<T>::~Memorable()
{
}

template<class T>
void Memorable<T>::read() {
	EEPROM.get(memory_location, x);
}

template<class T>
void Memorable<T>::write() {
	EEPROM.put(memory_location, x);
}
