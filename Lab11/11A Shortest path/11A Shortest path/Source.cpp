#include<fstream>
#include<vector>

std::ifstream fin("pathmgep.in");
std::ofstream fout("pathmgep.out");

const long long INF = 1e14 + 5;

class Graph {
public:
	explicit Graph(int n = 0) {
		vertexSize = n;
		graphMatrix.resize(n);
		for (int i(0); i < n; ++i) {
			graphMatrix[i].resize(n);
		}
	}

	long long findDistance(int v, int u) const {
		long long ans = findDistsDijkstra(v)[u];
		if (ans == INF) {
			ans = -1;
		}
		return ans;
	}

private:
	int vertexSize;
	std::vector<std::vector<long long>> graphMatrix;

	std::vector<long long> findDistsDijkstra(int start) const {
		std::vector<long long> dists(vertexSize, INF);
		std::vector<bool> isVisited(vertexSize, false);
		dists[start] = 0;
		for (int i(0); i < vertexSize; ++i) {
			int v = 0;
			long long minDist = INF;
			for (int j(0); j < vertexSize; ++j) {
				if (!isVisited[j] && dists[j] < minDist) {
					v = j;
					minDist = dists[j];
				}
			}
			if (minDist == INF) {
				break;
			}
			isVisited[v] = true;
			for (int j(0); j < vertexSize; ++j) {
				if (graphMatrix[v][j] != -1 && minDist + graphMatrix[v][j] < dists[j]) {
					dists[j] = minDist + graphMatrix[v][j];
				}
			}
		}
		return dists;
	}

	friend std::istream& operator>>(std::istream&, Graph&);
};

std::istream& operator>>(std::istream& cin, Graph& graph) {
	for (int i(0); i < graph.vertexSize; ++i) {
		for (int j(0); j < graph.graphMatrix[i].size(); ++j) {
			cin >> graph.graphMatrix[i][j];
		}
	}
	return cin;
}

int main() {
	int n, s, f;
	fin >> n >> s >> f;
	Graph graph(n);
	fin >> graph;
	fout << graph.findDistance(s - 1, f - 1);

	return 0;
}