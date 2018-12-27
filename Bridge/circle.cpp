#include "bridge.h"
#include<map>

static int status[NUM_OF_POINT];
static element init[NUM_OF_POINT];
static vector<int> *edge;
static map<Pair, bool> check;
static vector<Pair> notb;

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

static void filter(const vector<Pair> &fedge)
{
	initialInit();
	
	for (Pair e : fedge)
	{
		int xp = findSetInit(e.x);
		int yp = findSetInit(e.y);
		if (xp != yp)
		{
			edge[e.x].push_back(e.y);
			edge[e.y].push_back(e.x);
			check[e] = true;

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
}

static bool dfs(int p, int d)
{
	status[p] = 1;
	for (int i : edge[p])
	{
		if (i == d)
		{
			check[Pair(p, i)] = false;
			return true;
		}
		if (!status[i])
			if (dfs(i, d))
			{
				check[Pair(p,i)] = false;
				return true;
			}
	}
	return false;
}

static void findCircle()
{
	for (Pair e : notb)
	{
		memset(status, 0, sizeof(int)*N);
		dfs(e.x, e.y);
	}
}

vector<Pair> circle(vector<Pair> &fedge)	// find a bridge by disjoint set
{
	vector<Pair> r;
	int n = fedge.size();
	edge = new vector<int>[N];
	check.clear();
	notb.clear();

	filter(fedge);
	findCircle();
	map<Pair, bool>::iterator it;
	for (it = check.begin(); it != check.end(); ++it)
		if (it->second)
			r.push_back(it->first);

	delete[] edge;
	return r;
}