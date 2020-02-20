#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

struct Node
{
	string name;
	int d;
	int low;
	vector<Node*> hands;
};

Node* createNode(string v);
void DFS(vector<Node*>& graph);
void StrongConnect(vector<Node*> graph, Node* u, int& time, stack<string>& s, set<string>& check);
int find(vector<Node*> graph, string n);

int main()
{
	int count = 0;
	int people;
	int calls;
	string v1, v2;

	while (cin >> people >> calls)
	{
		if (people == 0 && calls == 0)
			break;

		vector<Node*> Graph;
		set<string> dp;
		set<string>::iterator it;
		int index = 0;

		for (int c = 0; c < calls; c++)
		{
			cin >> v1 >> v2;
			if (dp.find(v1) == dp.end())
			{
				Graph.push_back(createNode(v1));
				dp.insert(v1);
			}
			if (dp.find(v2) == dp.end())
			{
				Graph.push_back(createNode(v2));
				dp.insert(v2);
			}

			Graph[find(Graph, v1)]->hands.push_back(Graph[find(Graph, v2)]);
		}
		if (count > 1)
			cout << endl;
		cout << "Calling circles for data set " << ++count << ":" << endl;
		DFS(Graph);
	}

	system("pause");
	return 0;
}

Node* createNode(string n)
{
	Node* newNode = new Node;
	newNode->name = n;
	newNode->d = 0;

	return newNode;
}

int find(vector<Node*> graph, string n)
{
	for (int i = 0; i < graph.size(); i++)
		if (graph[i]->name == n)
			return i;
}

void DFS(vector<Node*>& graph)
{
	stack<string> component;
	set<string> duplicate;
	int time = 0;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->d == 0)
			StrongConnect(graph, graph[i], time, component, duplicate);
	}
}

void StrongConnect(vector<Node*> graph, Node* u, int& time, stack<string>& s, set<string> &check)
{
	time++;
	u->d = time;
	u->low = time;
	s.push(u->name);
	check.insert(u->name);

	set<string>::iterator it;
	for (int i = 0; i < u->hands.size(); i++)
	{
		it = check.find(u->hands[i]->name);
		if (u->hands[i]->d == 0)
		{
			StrongConnect(graph, u->hands[i], time, s, check);
			u->low = min(u->low, u->hands[i]->low);
		}
		else if (it != check.end())
			u->low = min(u->low, u->hands[i]->d);
	}

	if (u->d == u->low)
	{
		string buffer;
		vector<string> ans;
		
		do
		{
			buffer = s.top();
			s.pop();
			check.erase(check.find(buffer));
			ans.push_back(buffer);
		} while (buffer != u->name);

		for (int i = 0; i < ans.size(); i++)
		{
			if (i == 0)
				cout << ans[i];
			else
				cout << ", " << ans[i];
		}
		cout << endl;
	}
}