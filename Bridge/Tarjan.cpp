#include "bridge.h"

static int check[NUM_OF_POINT];
static int parent[NUM_OF_POINT];
static int low[NUM_OF_POINT];
static int dnf[NUM_OF_POINT];
static int num;

void dfsTar(vector<int> *point, int p)
{
	low[p] = dnf[p] = ++num;
	check[p] = 1;

	for (int i : point[p])
	{
		if (!check[i])
		{
			parent[i] = p;
			dfsTar(point, i);
		}
		if (i != parent[p] && low[i] < low[p])
			low[p] = low[i];
	}
}

void makeTar(vector<int> *point)
{
	memset(check, 0, sizeof(int)*N);
	num = 0;

	for (int i = 0; i < N; i++)
	{
		if (!check[i])
		{
			parent[i] = i;
			dfsTar(point, i);
		}
	}
}

vector<Pair> FBtar(vector<int> *point, const set<Pair> &edge)
{
	makeTar(point);
	vector<Pair> r;

	for (Pair e : edge)
		if (low[e.x] > dnf[e.y] || low[e.y] > dnf[e.x])
			r.push_back(e);
	
	return r;
}

vector<Pair> FBtar(vector<int> *point, const vector<Pair> &edge)
{
	makeTar(point);
	vector<Pair> r;

	for (Pair e : edge)
		if (low[e.x] > dnf[e.y] || low[e.y] > dnf[e.x])
			r.push_back(e);

	return r;
}