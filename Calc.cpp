#include "Calc.h"
//-------------------------------------------------------------------------------------------------------------------
int Calc::factorization(size_t value, Map & map, std::string *error)
{
	if (value < MIN_INPUT_VALUE || value > MAX_INPUT_VALUE)
	{
		if (error != nullptr)
		{
			error->clear();
			error->append("Value is invalid");
		}
		return EXECUTE_ERROR;
	}

	// We have simple value
	if (simpleNumbers.count(value))
		add(value,1,map);
	else
	{
		for (auto s : simpleNumbers)
		{
			if (value == 1) break;

			if (value % s == 0)
			{
				int cnt = 1;
				value /= s;

				while (value % s == 0)
				{
					cnt++;
					value /= s;
				}

				add(s, cnt, map);
			}
		}
	}

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int Calc::factorizationR(uint64_t value, Map & map, std::string *error)
{
	// We have simple value
	if (simpleNumbers.count(static_cast<size_t>(value)))
		add(static_cast<size_t>(value), 1, map);
	else
	{
		for (auto s : simpleNumbers)
		{
			if (value == 1) break;

			if (value % s == 0)
			{
				int cnt = 1;
				value /= s;

				while (value % s == 0)
				{
					cnt++;
					value /= s;
				}

				add(s, cnt, map);
			}
		}
	}

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int Calc::smallMult(size_t max, const Map & map, uint64_t & result, std::string *error)
{
	if (max < MIN_INPUT_VALUE || max > MAX_INPUT_VALUE)
	{
		if (error != nullptr)
		{
			error->clear();
			error->append("max is invalid");
		}
		return EXECUTE_ERROR;
	}

	Map curr;
	std::string err;
	if (factorization(max, curr,&err) == -1)
	{
		if (error != nullptr)
		{
			error->clear();
			error->append("In function smallMult " + err);
		}
		return EXECUTE_ERROR;
	}

	for (auto m : map)
	{
		if (!curr.count(m.first)) curr[m.first] = m.second;
		else
		{
			if (curr[m.first] < m.second)
			{
				curr[m.first] = m.second;
			}
			/*if (m.second == curr[m.first])
				curr.erase(m.first);
				else if (m.second > curr[m.first])
				curr[m.first] = m.second - curr[m.first];
				else
				curr[m.first] -= m.second;*/
		}

		/*result *= static_cast<uint64_t>(pow(m.first, curr[m.first]));*/
	}

	result = 1;
	for (auto c : curr)
		result *= static_cast<uint64_t>(pow(c.first, c.second));

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------
int Calc::add(size_t key, int value, Map & map)
{
	if (!map.count(key) || map[key] < value)
		map[key] = value;

	return EXECUTE_SUCCESSFULLY;
}
//-------------------------------------------------------------------------------------------------------------------


