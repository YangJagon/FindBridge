#include "bridge.h"

namespace Low {
	using namespace std;

	element all[NUM_OF_POINT];

	static void initialSet()
	{
		for (int i = 0; i < N; i++)
		{
			all[i].rank = 0;
			all[i].p = i;
		}
	}

	static int findSet(int x)	//find identifier
	{
		if (x != all[x].p)
			all[x].p = findSet(all[x].p);
		return all[x].p;
	}

	static void makeSet(const list<Pair> &edge)	//make set
	{
		for (Pair e : edge)
		{
			int xp = findSet(e.x);
			int yp = findSet(e.y);
			if (xp != yp)
			{
				if (all[xp].rank < all[yp].rank)
					all[xp].p = yp;
				else {
					all[yp].p = xp;
					if (all[xp].rank == all[yp].rank)
						all[xp].rank++;
				}
			}
		}
	}

	static bool makeSet(int x, int y, const list<Pair> &edge)	//check while making set
	{
		for (Pair e : edge)
		{
			int xp = findSet(e.x);
			int yp = findSet(e.y);
			if (xp != yp)
			{
				if (all[xp].rank < all[yp].rank)
					all[xp].p = yp;
				else {
					all[yp].p = xp;
					if (all[xp].rank == all[yp].rank)
						all[xp].rank++;
				}
				if (findSet(x) == findSet(y))	//check the result
					return true;
			}
		}
		return false;
	}

	static bool checkSet(int x, int y, const list<Pair> &edge)
	{
		initialSet();
		/*makeSet(edge);
		return (findSet(x) == findSet(y));*/
		return makeSet(x, y, edge);
	}

	vector<Pair> FBset(list<Pair> &edge)	// find a bridge by disjoint set
	{
		vector<Pair> r;
		int n = edge.size();

		for (int i = 0; i < n; i++)
		{
			Pair mid = edge.front();
			edge.pop_front();
			if (!checkSet(mid.x, mid.y, edge))
				r.push_back(mid);
			edge.push_back(mid);
		}

		return r;
	}
}
