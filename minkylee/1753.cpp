#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;


struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;  // 두 번째 요소가 작은 것이 우선순위가 높도록
    }
};

#define MAX 200000000

int V, E, start;
vector<pair<int, int > >*v;
int *g;
priority_queue<pair<int, int>, vector<pair<int, int> >, Compare> q;
bool *visited; 

void allocatevec(void)
{
	v = new vector<pair<int, int> >[V + 1];
	g = new int[V+1];
	visited = new bool[V+1];
}

void init(void)
{
	for (int i = 1; i <= V; i++)
		g[i] = MAX;
	g[start] = 0;
}

void print(void)
{
	for (int i = 1; i <= V; i++)
	{
		if (g[i] == MAX)
			cout << "INF\n";
		else
			cout << g[i] << '\n';
	}
}

void djikstra(int start)
{
	q.push(make_pair(start, 0));

	while (!q.empty())
	{
		int currentIndex = q.top().first;
		int weight = q.top().second;
		q.pop();
		for (int i = 0; i < v[currentIndex].size(); i++)
		{
			int nextIndex = v[currentIndex][i].first;
			int distance = weight + v[currentIndex][i].second;

			if (distance < g[nextIndex])
			{
				g[nextIndex] = distance;
				q.push(make_pair(nextIndex, distance));
			}
		}
	}
}

int main(void)
{
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	
	cin >> V >> E;
	cin >> start;
	allocatevec();
	init();

	for (int i = 0; i < E; i++)
	{
		int x, y, weight;
		cin >> x >> y >> weight;
		v[x].push_back(make_pair(y, weight));
	}
	djikstra(start);
	print();
}

