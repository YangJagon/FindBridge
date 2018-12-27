#include "bridge.h"

Pair::Pair()
{
	x = y = 0;
}

Pair::Pair(int a, int b)
{
	x = a < b ? a : b;
	y = a < b ? b : a;
}

bool Pair::operator<(const Pair &other) const
{
	if (x < other.x)
		return true;
	else if (x == other.x && y < other.y)
		return true;
	return false;
}