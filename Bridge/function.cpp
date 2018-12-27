#include "bridge.h"
static int check[NUM_OF_POINT];

void initialEdge(list<int>* &point, set<Pair> &uedge, list<Pair> &fedge, string filename)
{
	ifstream in(filename);
	in >> N;
	point = new list<int>[N];

	int n;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		in >> x >> y;
		if (x != y)
		{
			Pair tmp(x, y);
			uedge.insert(tmp);
			fedge.push_back(tmp);
			point[x].push_back(y);
			point[y].push_back(x);
		}
	}
	in.close();
}

void initialEdgeTar(vector<int>* &point, set<Pair> &uedge, string filename)
{
	ifstream in(filename);
	in >> N;
	point = new vector<int>[N];
	int n;
	in >> n;
	set<pair<int, int>>::iterator it;

	for (int i = 0; i < n; i++)
	{
		int x, y;
		in >> x >> y;

		pair<int, int> a;
		a.first = x < y ? x : y;
		a.second = x < y ? y : x;

		if (x != y)
		{
			point[x].push_back(y);
			point[y].push_back(x);

			Pair tmp(x, y);
			uedge.insert(tmp);
		}
	}
	in.close();
}

void initialEdgeTar(vector<int>* &point, vector<Pair> &uedge, string filename)
{
	ifstream in(filename);
	in >> N;
	point = new vector<int>[N];
	int n;
	in >> n;
	set<pair<int, int>>::iterator it;

	for (int i = 0; i < n; i++)
	{
		int x, y;
		in >> x >> y;

		pair<int, int> a;
		a.first = x < y ? x : y;
		a.second = x < y ? y : x;

		if (x != y)
		{
			point[x].push_back(y);
			point[y].push_back(x);

			Pair tmp(x, y);
			uedge.push_back(tmp);
		}
	}
	in.close();
}

void cccdfs(list<int> *point, int p) //dfs while count connected component
{
	check[p] = 1;
	for (int it : point[p])
	{
		if (!check[it])
			cccdfs(point, it);
	}
}

int countCC(list<int> *point) //count connected component
{
	int sum = 0;
	memset(check, 0, sizeof(int)*N);

	for (int i = 0; i < N; i++)
	{
		if (!check[i])
		{
			sum++;
			cccdfs(point, i);
		}
	}

	return sum;
}

bool EPdfs(list<int> *point, int p, int r)	//dfs while check if exist a path between head and tail
{
	check[p] = 1;
	for (int i : point[p])
	{
		if (i == r)
			return true;
		if (!check[i])
			if (EPdfs(point, i, r))
				return true;
	}
	return false;
}

bool existPath(list<int> *point, int head, int tail) //check if exist a path between head and tail
{
	memset(check, 0, sizeof(int)*N);
	return EPdfs(point, head, tail);
}

void erase(list<int> *point, int head, int tail)	//delete an edge
{
	point[head].erase(find(point[head].begin(), point[head].end(), tail));
	point[tail].erase(find(point[tail].begin(), point[tail].end(), head));
}

void insert(list<int> *point, int head, int tail)	//insert an edge
{
	point[head].push_back(tail);
	point[tail].push_back(head);
}