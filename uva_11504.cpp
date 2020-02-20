#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> neighbor[100001];
vector<int> nc;
int d[100001];
int visited[100001];
int low[100001];
int degree[100001];
int nodes;
int t;
int total;
set<int> dp;
stack<int> component;

void DFS();
void StrongConnect(int u);

int main()
{
	int cases;
	int v1, v2;
	
	int lines;
	cin >> cases;

	for (int c = 0; c < cases; c++)
	{
		cin >> nodes >> lines;
		
		memset(d, 0, sizeof(d));
		memset(visited, 0, sizeof(visited));
		memset(low, 0, sizeof(low));
		memset(degree, 0, sizeof(degree));
		for (int i = 0; i < 100001; i++)
			neighbor[i].clear();
		nc.clear();

		for (int i = 0; i < lines; i++)
		{
			cin >> v1 >> v2;
			visited[v1] = 1;
			visited[v2] = 1;
			neighbor[v1].push_back(v2);
		}

		DFS();
	}

	system("pause");
	return 0;
}

void DFS()
{
	t = 0;
	total = 0;
	for (int i = 1; i <= nodes; i++)
	{
		if (visited[i] == 1)
			StrongConnect(i);
		else if (visited[i] == 0)
			total++;
	}

	for (int i = 0; i < nc.size(); i++)
	{
		if (degree[nc[i]] == 0)
			total++;
	}
	cout << total << endl;
}

void StrongConnect(int u)
{
	t++;
	d[u] = t;
	low[u] = t;
	visited[u] = 2;
	dp.insert(u);
	component.push(u);

	for (int i = 0; i < neighbor[u].size(); i++)
	{
		if (visited[neighbor[u][i]] != 2)
		{
			StrongConnect(neighbor[u][i]);
			low[u] = min(low[u], low[neighbor[u][i]]);
		}
		else if (dp.find(neighbor[u][i]) != dp.end())
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
			dp.erase(dp.find(buffer));

			for (int i = 0; i < neighbor[buffer].size(); i++)
			{
				if (low[neighbor[buffer][i]] != low[buffer])
					degree[low[neighbor[buffer][i]]]++;
			}
		} while (buffer != u);
	}
}