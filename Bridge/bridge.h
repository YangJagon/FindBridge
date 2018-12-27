#ifndef BRIDGE_HEAD
#define BRIDGE_HEAD
#include<iostream>
#include<list>
#include<fstream>
#include<set>
#include<vector>
using namespace std;

class Pair {
public:
	int x, y;
	Pair();
	Pair(int a, int b);
	bool operator < (const Pair &other) const;
};
struct element {
	int rank;
	int p;
};

extern int N;
const int NUM_OF_POINT = 200000;

void initialEdge(list<int>* &point, set<Pair> &uedge, list<Pair> &fedge, string filename);
void initialEdgeTar(vector<int>* &point, set<Pair> &uedge, string filename);
void initialEdgeTar(vector<int>* &point, vector<Pair> &uedge, string filename);

void cccdfs(list<int> *point, int p);
int countCC(list<int> *point);
void erase(list<int> *point, int head, int tail);
void insert(list<int> *point, int head, int tail);
bool existPath(list<int> *point, int head, int tail);

vector<Pair> FBworst(list<int> *point, const set<Pair> &edge);
vector<Pair> FBdfs(list<int> *point, const set<Pair> &edge);
vector<Pair> FBtar(vector<int> *point, const set<Pair> &edge);
vector<Pair> FBtar(vector<int> *point, const vector<Pair> &edge);

namespace super {
	vector<Pair> FBset(vector<Pair> &edge);
}

namespace Low {
	vector<Pair> FBset(list<Pair> &edge);
}
vector<Pair> circle(vector<Pair> &fedge);
#endif