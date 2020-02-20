#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Node
{
	int d;
	int low;
	int val;
	int parent;
	vector<Node*> hands;
};

struct link
{
	int v1;
	int v2;

	link(int a, int b)
		: v1(a), v2(b)
	{
	}
	bool operator< (const link& rhs) const
	{
		if (rhs.v1 == v1)
			return v2 > rhs.v2;
		return v1 > rhs.v1;
	}
};


Node* createNode(int val);
void DFS_VISIT(vector<Node*>& graph, Node* u, int& time, priority_queue<link> & bridges);
void BRIDGE(vector<Node*>& graph);

int main()
{
	int numServer;
	int vertic;
	int edge;
	int v;
	
	while (cin >> numServer)
	{
		stringstream ss;
		stringstream sn;

		vector<Node*> Graph;
		for (int i = 0; i < numServer; i++)
			Graph.push_back(createNode(i));

		
		for (int s = 0; s < numServer; s++)
		{
			string buffer;
			cin >> vertic;
			cin >> buffer;
			
			buffer.erase(buffer.begin());
			buffer.erase(--buffer.end());

			ss.str("");
			ss.clear();
			ss << buffer;
			ss >> edge;

			for (int i = 0; i < edge; i++)
			{
				cin >> v;
				Graph[vertic]->hands.push_back(Graph[v]);
				Graph[v]->hands.push_back(Graph[vertic]);
			}
		}
		BRIDGE(Graph);
	}

	system("pause");
	return 0;
}

Node* createNode(int val)
{
	Node* newNode = new Node;
	newNode->d = 0;
	newNode->parent = 0;
	newNode->val = val;

	return newNode;
}

void DFS_VISIT(vector<Node*> &graph, Node* u, int& time, priority_queue<link> &bridges)
{
	time++;
	u->d = time;
	u->low = time;
	for (int i = 0; i < u->hands.size(); i++)
	{
		if (u->hands[i]->d == 0)
		{
			u->hands[i]->parent = u->val;
			DFS_VISIT(graph, u->hands[i], time, bridges);

			u->low = min(u->low, u->hands[i]->low);
			if (u->hands[i]->low > u->d)
			{
				link newLink(min(u->val, u->hands[i]->val), max(u->val, u->hands[i]->val));
				bridges.push(newLink);
			}
		}
		else if (u->hands[i]->val != u->parent)
			u->low = min(u->low, u->hands[i]->d);
	}
}

void BRIDGE(vector<Node*>& graph)
{
	int time = 0;
	priority_queue<link> bridges;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->d == 0)
			DFS_VISIT(graph, graph[i], time, bridges);
	}

	cout << bridges.size() << " critical links" << endl;
	while (!bridges.empty())
	{
		cout << bridges.top().v1 << " - " << bridges.top().v2 << endl;
		bridges.pop();
	}
	cout << endl;
}