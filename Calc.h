#ifndef __CALC_H__
#define __CALC_H__
//-------------------------------------------------------------------------------------------------------------------
// Class for calculate factorization and searching smallest multiple of value
//-------------------------------------------------------------------------------------------------------------------
#include "Define.h"
//-------------------------------------------------------------------------------------------------------------------
class Calc
{
public:
	// Factorization 
	static int factorization(size_t value, Map & map, std::string *error = nullptr);
	static int factorizationR(uint64_t value, Map & map, std::string *error = nullptr);

	// Smallest multiple
	static int smallMult(size_t max, const Map & map, uint64_t & result,std::string *error = nullptr);

private:
	// Add to map, if value > map.second or if map doesn't have this key
	static int add(const size_t key,const int value, Map & map);
};

//-------------------------------------------------------------------------------------------------------------------
#endif	//__CALC_H__

