#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

struct Node
{
	int val;
	int d;
	int low;
	int parent;
	vector<Node*> hands;
};

Node* createNode(int value);
void DFS(vector<Node*>& graph);
void StrongConnect(vector<Node*>& graph, Node* u, int& time, stack<int>& s, set<int>& dp, int& count);

int main()
{
	int nodes;
	int lines;
	int v1, v2;
	int option;

	while (cin >> nodes >> lines)
	{
		if (nodes == 0 && lines == 0)
			break;

		vector<Node*> Graph;
		for (int i = 0; i <= nodes; i++)
			Graph.push_back(createNode(i));

		for (int i = 0; i < lines; i++)
		{
			cin >> v1 >> v2 >> option;
			
			Graph[v1]->hands.push_back(Graph[v2]);
			if (option == 2)
				Graph[v2]->hands.push_back(Graph[v1]);
		}

		DFS(Graph);
	}

	system("pause");
	return 0;
}

Node* createNode(int value)
{
	Node* newNode = new Node;
	newNode->val = value;
	newNode->d = 0;
	newNode->parent = -1;

	return newNode;
}

void DFS(vector<Node*>& graph)
{
	int time = 0;
	int count = 0;
	stack<int> component;
	set<int> dp;

	for (int i = 1; i < graph.size(); i++)
	{
		if (graph[i]->d == 0)
			StrongConnect(graph, graph[i], time, component, dp, count);
	}

	cout << "ans" << ' ';
	if (count == 1)
		cout << 1 << endl;
	else
		cout << 0 << endl;
}

void StrongConnect(vector<Node*>& graph, Node* u, int& time, stack<int>& s, set<int>& dp, int &count)
{
	time++;
	u->d = time;
	u->low = time;
	s.push(u->val);
	dp.insert(u->val);

	for (int i = 0; i < u->hands.size(); i++)
	{
		if (u->hands[i]->d == 0)
		{
			u->hands[i]->parent = u->val;
			StrongConnect(graph, u->hands[i], time, s, dp, count);
			u->low = min(u->low, u->hands[i]->low);
		}
		else if (dp.find(u->hands[i]->val) != dp.end())
			u->low = min(u->low, u->hands[i]->d);
	}

	if (u->d == u->low)
	{
		int buffer;
		do
		{
			buffer = s.top();
			s.pop();
			dp.erase(dp.find(buffer));
		} while (buffer != u->val);
		count++;
	}
}