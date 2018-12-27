#include "bridge.h"

namespace super {
	static element all[NUM_OF_POINT];
	static element init[NUM_OF_POINT];

	static void initialInit()
	{
		for (int i = 0; i < N; i++)
		{
			init[i].rank = 0;
			init[i].p = i;
		}
	}

	static int findSetInit(int x)	//find identifier
	{
		if (x != init[x].p)
			init[x].p = findSetInit(init[x].p);
		return init[x].p;
	}

	static void makeInitSet(const vector<Pair> &edge)	//make set
	{
		for (Pair e : edge)
		{
			int xp = findSetInit(e.x);
			int yp = findSetInit(e.y);
			if (xp != yp)
			{
				if (init[xp].rank < init[yp].rank)
					init[xp].p = yp;
				else {
					init[yp].p = xp;
					if (init[xp].rank == init[yp].rank)
						init[xp].rank++;
				}
			}
		}
	}

	static void filter(const vector<Pair> &edge, list<Pair> &possible)
	{
		initialInit();
		vector<Pair> notb;

		for (Pair e : edge)
		{
			int xp = findSetInit(e.x);
			int yp = findSetInit(e.y);
			if (xp != yp)
			{
				possible.push_back(e);
				if (init[xp].rank < init[yp].rank)
					init[xp].p = yp;
				else {
					init[yp].p = xp;
					if (init[xp].rank == init[yp].rank)
						init[xp].rank++;
				}
			}
			else
				notb.push_back(e);
		}

		initialInit();
		makeInitSet(notb);
	}

	/******************************************************************************************************/

	static void initialAll()
	{
		for (int i = 0; i < N; i++)
		{
			all[i].rank = init[i].rank;
			all[i].p = init[i].p;
		}
	}

	static int findSet(int x)	//find identifier
	{
		if (x != all[x].p)
			all[x].p = findSet(all[x].p);
		return all[x].p;
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
		if (findSetInit(x) == findSetInit(y))
			return true;
		initialAll();
		return makeSet(x, y, edge);
	}

	vector<Pair> FBset(vector<Pair> &edge)	// find a bridge by disjoint set
	{
		vector<Pair> r;
		list<Pair> possible;

		filter(edge, possible);

		int n = possible.size();
		for (int i = 0; i < n; i++)
		{
			Pair mid = possible.front();
			possible.pop_front();
			if (!checkSet(mid.x, mid.y, possible))
				r.push_back(mid);
			possible.push_back(mid);
		}

		return r;
	}
}
