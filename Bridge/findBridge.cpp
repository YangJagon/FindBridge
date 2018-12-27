#include "bridge.h"

vector<Pair> FBworst(list<int>* point, const set<Pair> &edge) //the worst way to find bridge--count the connect component
{
	int sum = countCC(point);
	vector<Pair> r;

	for (Pair it : edge)
	{
		erase(point, it.x, it.y);
		int tmp = countCC(point);
		insert(point, it.x, it.y);

		if (tmp > sum)
			r.push_back(Pair(it.x, it.y));
	}

	return r;
}

vector<Pair> FBdfs(list<int>* point, const set<Pair> &edge)	//find a bridge by dfs -- check if there is a another way from head to tail
{
	vector<Pair> r;

	for (Pair it : edge)
	{
		erase(point, it.x, it.y);
		if(!existPath(point, it.x, it.y))
			r.push_back(Pair(it.x, it.y));
		insert(point, it.x, it.y);
	}

	return r;
}