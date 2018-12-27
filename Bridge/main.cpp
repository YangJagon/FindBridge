#include "bridge.h"
#include<Windows.h>

int N;
list<int> *point;
vector<int> *tarp;
list<Pair> ledge;
set<Pair> sedge;
vector<Pair> vedge;

int main()
{
	double dqfreq, run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	_LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqfreq = (double)f.QuadPart;

	initialEdge(point, sedge, ledge, "2w.txt");
	initialEdgeTar(tarp, vedge, "2w.txt");

	QueryPerformanceCounter(&time_start);
	//vector<Pair> r = FBworst(point, sedge);
	//vector<Pair> r = FBdfs(point, sedge);
	//vector<Pair> r = Low::FBset(ledge);
	//vector<Pair> r = circle(vedge);
	vector<Pair> r = super::FBset(vedge);
	//vector<Pair> r = FBtar(tarp, vedge);
	QueryPerformanceCounter(&time_over);
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqfreq;
	cout << "low set Time: " << run_time  << " ms " << r.size() << endl;

	for (Pair p : r)
		cout << p.x << " " << p.y << endl;

	delete[] point;
}