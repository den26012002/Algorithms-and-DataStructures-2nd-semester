#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>

std::ifstream fin("path.in");
std::ofstream fout("path.out");

const long long INF =  8 * 1e18;

class Graph {
public:
	struct Edge {
		int from, to;
		long long weight;
	};

	struct Vertex {
		long long dist;
		//std::vector<bool> canBeReachedFrom;
		std::unordered_set<int> reachableVertexes;
	};

public:
	Graph(int _vertexSize = 0) :
		vertexSize(_vertexSize),
		vertexes(_vertexSize, { INF/*, std::vector<bool>(vertexSize, false)*/}),
		vertexEdges(_vertexSize)
	{}

	void addEdge(int v, int u, long long weight) {
		edges.push_back({ v, u, weight });
		vertexEdges[v].push_back({ v, u, weight });
	}

	std::vector<Vertex>& getDists(int vertex = 0) {
		for (int i(0); i < 2; ++i) {
			visited = std::vector<bool>(vertexSize, false);
			checkReachability(vertex);
		}
		visited = std::vector<bool>(vertexSize, false);
		findDists(vertex);
		return vertexes;
	}

private:
	int vertexSize;
	std::vector<Edge> edges;
	std::vector<Vertex> vertexes;
	std::vector<std::vector<Edge>> vertexEdges;
	std::vector<bool> visited;

	void checkReachability(int vertex) {
		visited[vertex] = true;
		for (int i(0); i < vertexEdges[vertex].size(); ++i) {
			int u = vertexEdges[vertex][i].to;
			if (!visited[u]) {
				checkReachability(u);
			}
		}
		for (int i(0); i < vertexEdges[vertex].size(); ++i) {
			int u = vertexEdges[vertex][i].to;
			for (auto j : vertexes[u].reachableVertexes) {
				vertexes[vertex].reachableVertexes.insert(j);
			}
			vertexes[vertex].reachableVertexes.insert(u);
		}
	}

	void findDists(int vertex) {
		visited[vertex] = true;
		vertexes[vertex].dist = 0;
		for (int i(0); i < vertexSize - 1; ++i) {
			for (int j(0); j < edges.size(); ++j) {
				Edge e = edges[j];
				if (visited[e.from] && vertexes[e.from].dist + e.weight < vertexes[e.to].dist) {
					vertexes[e.to].dist = std::max(-INF, vertexes[e.from].dist + e.weight);
					visited[e.to] = true;
				}
			}
		}
		for (int k(0); k < 2; ++k) {
			for (int i(0); i < edges.size(); ++i) {
				Edge e = edges[i];
				if (visited[e.from] && vertexes[e.from].dist + e.weight < vertexes[e.to].dist) {
					vertexes[e.to].dist = -INF;
					vertexes[e.from].dist = -INF;
					for (auto i : vertexes[e.to].reachableVertexes) {
						vertexes[i].dist = -INF;
					}
				}
			}
		}
	}
};

int main() {
	int n, m, s;
	fin >> n >> m >> s;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		long long w;
		fin >> v >> u >> w;
		graph.addEdge(v - 1, u - 1, w);
	}
	auto& ans = graph.getDists(s - 1);
	for (int i(0); i < n; ++i) {
		if (ans[i].dist == INF) {
			fout << '*';
		} else if (ans[i].dist == -INF) {
			fout << '-';
		} else {
			fout << ans[i].dist;
		}
		fout << '\n';
	}	

	return 0;
}