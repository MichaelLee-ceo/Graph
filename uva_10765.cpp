#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
	int d;
	int low;
	int parent;
	int val;
	int numChild;
	int color;
	bool cut;
	vector<Node*> hands;
};

struct cutPoint
{
	int val;
	int num;

	bool operator< (const cutPoint& rhs)    const
	{
		if (num == rhs.num)
			return val > rhs.val;
		return num < rhs.num;
	}
};

Node* createNode(int value);
void ARIRCULATIONPOINT(vector<Node*>& graph, int pg);
void DFS_VISIT(vector<Node*>& graph, Node* node, int& time);
void DFS(vector<Node*>& graph, Node* u);
void reset(vector<Node*>& graph);

int main()
{
	int nodes;
	int target;
	int v1, v2;
	while (cin >> nodes >> target)
	{
		if (nodes == 0 && target == 0)
			break;

		vector<Node*> Graph;
		for (int i = 0; i < nodes; i++)
			Graph.push_back(createNode(i));

		while (cin >> v1 >> v2)
		{
			if (v1 == -1 && v2 == -1)
				break;

			Graph[v1]->hands.push_back(Graph[v2]);
			Graph[v2]->hands.push_back(Graph[v1]);
		}

		ARIRCULATIONPOINT(Graph, target);
	}

	system("pause");
	return 0;
}

Node* createNode(int value)
{
	Node* newNode = new Node;
	newNode->d = 0;
	newNode->parent = -1;
	newNode->cut = false;
	newNode->val = value;
	newNode->numChild = 0;
	newNode->color = 0;

	return newNode;
}

void DFS_VISIT(vector<Node*> &graph, Node* u, int &time)
{
	time++;
	u->d = time;
	u->low = time;
	for (int i = 0; i < u->hands.size(); i++)
	{
		if (u->hands[i]->d == 0)
		{
			u->numChild++;
			u->hands[i]->parent = u->val;
			DFS_VISIT(graph, u->hands[i], time);

			u->low = min(u->low, u->hands[i]->low);
			if (u->parent != -1)
				if (u->hands[i]->low >= u->d)
					u->cut = true;
		}
		else if (u->hands[i]->val != u->parent)
			u->low = min(u->low, u->hands[i]->d);
	}
	if (u->parent == -1)
		if (u->numChild > 1)
			u->cut = true;
}

void ARIRCULATIONPOINT(vector<Node*>& graph, int pg)
{
	int time = 0;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->d == 0)
			DFS_VISIT(graph, graph[i], time);
	}

	priority_queue<cutPoint> ans;
	cutPoint newCut;
	int count;
	for (int i = 0; i < graph.size(); i++)
	{
		count = 0;
		if (graph[i]->cut)
		{
			reset(graph);
			graph[i]->color = 1;
			for (int j = 0; j < graph.size(); j++)
			{
				if (graph[j]->color == 0)
				{
					count++;
					DFS(graph, graph[j]);
				}
			}
			newCut.val= graph[i]->val;
			newCut.num = count;
		}
		else
		{
			newCut.val = graph[i]->val;
			newCut.num = 1;
		}
		ans.push(newCut);
	}

	for (int i = 0; i < pg; i++)
	{
		cout << ans.top().val << ' ' << ans.top().num << endl;
		ans.pop();
	}
	cout << endl;
}

void DFS (vector<Node*>& graph, Node* u)
{
	u->color = 1;
	for (int i = 0; i < u->hands.size(); i++)
	{
		if (u->hands[i]->color == 0)
			DFS(graph, u->hands[i]);
	}
}

void reset(vector<Node*>& graph)
{
	for (int i = 0; i < graph.size(); i++)
		graph[i]->color = 0;
}