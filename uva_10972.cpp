#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

int d[1001];
int low[1001];
int visited[1001];
int inEdge[1001];
int parent[1001];
int nodes;
int edges;
int single;
int leaves;
int t;
vector<int> neighbor[1001];
vector<int> nc;
stack<int> component;

void DFS();
void BridgeConnect(int u);
ofstream o("ans.txt");

int main()
{
	int v1, v2;

	while (cin >> nodes >> edges)
	{
		memset(d, 0, sizeof(d));
		memset(low, 0, sizeof(low));
		memset(visited, false, sizeof(visited));
		memset(parent, 0, sizeof(parent));
		memset(inEdge, 0, sizeof(inEdge));
		for (int i = 0; i < 1001; i++)
			neighbor[i].clear();
		nc.clear();

		for (int i = 0; i < edges; i++)
		{
			cin >> v1 >> v2;
			visited[v1] = 1;
			visited[v2] = 1;
			neighbor[v1].push_back(v2);
			neighbor[v2].push_back(v1);
		}

		DFS();
	}

	system("pause");
	return 0;
}

void DFS()
{
	t = 0;
	leaves = 0;
	single = 0;
	
	for (int i = 1; i <= nodes; i++)
	{
		if (visited[i] == 1)
			BridgeConnect(i);
		else if (visited[i] == 0)
			single++;
	}

	for (int i = 1; i <= nodes; i++)
	{
		for (int j = 0; j < neighbor[i].size(); j++)
		{
			if (low[neighbor[i][j]] != low[i])
				inEdge[low[neighbor[i][j]]]++;
		}
	}

	for (int i = 0; i < nc.size(); i++)
	{
		if (inEdge[nc[i]] == 1)
			leaves++;
		else if (inEdge[nc[i]] == 0)
			single++;
	}
	
	//cout << single << ' ' << leaves << endl;
	
	if (nc.size() == 1 || nodes == 1)
		cout << 0 << endl;
	else
		cout << (single * 2 + leaves + 1) / 2 << endl;
}

void BridgeConnect(int u)
{
	t++;
	d[u] = t;
	low[u] = t;
	visited[u] = 2;
	component.push(u);

	for (int i = 0; i < neighbor[u].size(); i++)
	{
		if (visited[neighbor[u][i]] == 1)
		{
			parent[neighbor[u][i]] = u;
			BridgeConnect(neighbor[u][i]);
			low[u] = min(low[u], low[neighbor[u][i]]);
		}
		else if (neighbor[u][i] != parent[u])
			low[u] = min(low[u], d[neighbor[u][i]]);
	}

	if (low[u] == d[u])
	{
		nc.push_back(low[u]);
		int buffer;

		do
		{
			buffer = component.top();
			component.pop();
		} while (buffer != u);
	}
}