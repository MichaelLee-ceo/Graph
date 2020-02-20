#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct Node
{
	int val;
	int d;
	int low;
	int parent;
	int children;
	bool cut;
	vector<Node*> hands;
};

Node* createNode(int value);
void DFS_VISIT(vector<Node*>& graph, Node* currentNode, int& time);
void articulationPoint(vector<Node*> graph);

int main()
{
	int cases;
	int vertic;
	string v;

	while (cin >> cases)
	{
		if (cases == 0)
			break;

		cin.get();

		vector<Node*> Graph;
		for (int i = 0; i <= cases; i++)
			Graph.push_back(createNode(i));

		for (int t = 0; t < cases; t++)
		{
			getline(cin, v);
			if (v == "0")
				break;
			if (t == cases - 1)
				cin.get();

			vector<int> edge;
			stringstream ss;
			stringstream sn;
			string buffer;

			ss << v;
			while (getline(ss, buffer, ' '))
			{
				sn.str("");
				sn.clear();
				sn << buffer;
				sn >> vertic;
				edge.push_back(vertic);
			}
				
			for (int i = 1; i < edge.size(); i++)
			{
				Graph[edge[i]]->hands.push_back(Graph[edge[0]]);
				Graph[edge[0]]->hands.push_back(Graph[edge[i]]);
			}
		}

		articulationPoint(Graph);

	}

	system("pause");
	return 0;
}

Node* createNode(int value)
{
	Node* newNode = new Node;
	newNode->val = value;
	newNode->cut = false;
	newNode->parent = 0;
	newNode->children = 0;
	newNode->d = 0;

	return newNode;
}

void DFS_VISIT(vector<Node*>& graph, Node* u, int &time)
{
	time++;
	u->d = time;
	u->low = time;
	for (int i = 0; i < u->hands.size(); i++)
	{
		if (u->hands[i]->d == 0)
		{
			u->children++;
			u->hands[i]->parent = u->val;
			DFS_VISIT(graph, u->hands[i], time);

			u->low = min(u->low, u->hands[i]->low);
			if (u->parent != 0)
				if (u->hands[i]->low >= u->d)
					u->cut = true;
		}
		else if (u->hands[i]->val != u->parent)
			u->low = min(u->low, u->hands[i]->d);
	}

	if (u->parent == 0)
		if (u->children > 1)
			u->cut = true;
}

void articulationPoint(vector<Node*> graph)
{
	int time = 0;
	int cutPoint = 0;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->d == 0)
			DFS_VISIT(graph, graph[i], time);
		if (graph[i]->cut)
			cutPoint++;
	}
	cout << cutPoint << endl;
}