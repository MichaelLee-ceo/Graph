#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

bool visited[100];
int degree[100];
vector<char> neighbor[100];
list<int> ans;
void DFS(char ch);

int main()
{
	string a, b;
	int count = 0;
	int length = 0;


	while (cin >> a)
	{
		memset(visited, false, sizeof(visited));
		memset(degree, 0, sizeof(degree));
		for (int i = 0; i < 100; i++)
			neighbor[i].clear();
		ans.clear();

		while (cin >> b)
		{
			if (b == "#")
				break;

			length = (a.length() > b.length()) ? b.length() : a.length();
			for (int i = 0; i < length; i++)
			{
				if (degree[a[i]] == 0)
					degree[a[i]] = 1;
				if (degree[b[i]] == 0)
					degree[b[i]] = 1;
				if (b[i] != a[i])
				{
					neighbor[a[i]].push_back(b[i]);
					degree[b[i]] = 2;
					break;
				}
			}
			a = b;
		}

		for (int i = 'A'; i <= 'Z'; i++)
			if (degree[i] == 1)
				DFS(i);

		for (list<int>::iterator p1 = ans.begin(); p1 != ans.end(); ++p1)
			cout << char(*p1);
		cout << endl;
	}

	system("pause");
	return 0;
}

void DFS(char ch)
{
	visited[ch] = true;
	for (int i = 0; i < neighbor[ch].size(); i++)
	{
		if (visited[neighbor[ch][i]] == false)
			DFS(neighbor[ch][i]);
	}
	ans.push_front(ch);
}
