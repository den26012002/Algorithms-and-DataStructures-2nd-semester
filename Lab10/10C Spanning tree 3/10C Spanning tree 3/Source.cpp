#include<fstream>
#include<vector>
#include<algorithm>

#define int long long

std::ifstream fin("spantree3.in");
std::ofstream fout("spantree3.out");

class DisjointSets {
public:
	void makeSet(int x) {
		if (size < x) {
			size = x;
			parents.resize(x);
			ranks.resize(x);
		}
		parents[x] = x;
		ranks[x] = 1;
	}

	int findSet(int x) {
		if (parents[x] == x) {
			return x;
		} else {
			return parents[x] = findSet(parents[x]);
		}
	}

	void unionSets(int x, int y) {
		x = findSet(x);
		y = findSet(y);
		if (ranks[x] < ranks[y]) {
			parents[x] = y;
			ranks[y] += ranks[x];
		}
		else {
			parents[y] = x;
			ranks[x] += ranks[y];
		}
	}

	explicit DisjointSets(int _size) : size(_size) {
		parents.resize(_size);
		ranks.resize(_size);
		for (int i(0); i < _size; ++i) {
			parents[i] = i;
			ranks[i] = 1;
		}
	}

	DisjointSets() : size(0) {}

private:
	std::vector<int> parents;
	std::vector<int> ranks;
	int size;
};


class Graph {
public:
	explicit Graph(int _vertexesSize) : vertexesSize(_vertexesSize) {}

	Graph() {}

	void addEdge(int v, int u, int weight = 1) {
		edges.push_back({ v, u, weight });
	}

	int getMSTSize() {
		std::sort(edges.begin(), edges.end());
		int ans = 0;
		DisjointSets vertexesSets(vertexesSize);
		for (int i(0); i < edges.size(); ++i) {
			Edge e = edges[i];
			if (vertexesSets.findSet(e.v) != vertexesSets.findSet(e.u)) {
				ans += e.weight;
				vertexesSets.unionSets(e.v, e.u);
			}
		}
		return ans;
	}

private:
	struct Edge {
		int v, u;
		int weight;
		bool operator<(const Edge& other) {
			return weight < other.weight;
		}
	};

	int vertexesSize;
	std::vector<Edge> edges;
};

signed main() {
	int n, m;
	fin >> n >> m;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int b, e, w;
		fin >> b >> e >> w;
		graph.addEdge(b - 1, e - 1, w);
	}
	fout << graph.getMSTSize();
	

	return 0;
}