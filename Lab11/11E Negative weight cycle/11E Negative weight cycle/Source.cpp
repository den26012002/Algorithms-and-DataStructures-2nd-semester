#include<fstream>
#include<vector>
#include<algorithm>

std::ifstream fin("negcycle.in");
std::ofstream fout("negcycle.out");

const int INF = 1e9;

class Graph {
public:
	explicit Graph(int _vertexSize = 0) :
		vertexSize(_vertexSize)
	{}

	void addEdge(int from, int to, int weight) {
		edges.push_back({ from, to, weight });
	}

	std::vector<int> getNegCycle() {
		return findNegCycle(0);
	}

private:
	struct Edge {
		int from, to;
		int weight;
	};

	struct Vertex {
		int dist;
		int parent;
	};

	int vertexSize;
	std::vector<Edge> edges;

	std::vector<int> findNegCycle(int startVertex) {
		std::vector<Vertex> vertexes(vertexSize, { INF, -1 });
		vertexes[startVertex];
		for (int i(0); i < vertexSize - 1; ++i) {
			for (int j(0); j < edges.size(); ++j) {
				Edge e = edges[j];
				if (vertexes[e.from].dist + e.weight < vertexes[e.to].dist) {
					vertexes[e.to].dist = vertexes[e.from].dist + e.weight;
					vertexes[e.to].parent = e.from;
				}
			}
		}
		std::vector<int> cycle;
		for (int i(0); i < edges.size(); ++i) {
			Edge e = edges[i];
			if (vertexes[e.from].dist + e.weight < vertexes[e.to].dist) {
				vertexes[e.to].parent = e.from;
				int v = e.from;
				bool wasRepeat = false;
				while (!wasRepeat) {
					cycle.push_back(v);
					for (int j(0); j < cycle.size() - 1; ++j) {
						if (cycle[j] == v) {
							for (int k(0); k < j; ++k) {
								cycle[k] = -1;
							}
							wasRepeat = true;
						}
					}
					v = vertexes[v].parent;
				}
				std::reverse(cycle.begin(), cycle.end());
				break;
			}
		}
		return cycle;
	}
};

template<typename Type>
std::vector<Type>& inc(std::vector<Type>& arr) {
	for (int i(0); i < arr.size(); ++i) {
		++arr[i];
	}
	return arr;
}

template<typename Type>
std::ostream& operator<<(std::ostream& cout, const std::vector<Type>& arr) {
	for (int i(0); i < arr.size(); ++i) {
		if (arr[i] > 0) {
			cout << arr[i] << ' ';
		}
	}
	return cout;
}

int main() {
	int n;
	fin >> n;
	Graph graph(n);
	for (int i(0); i < n; ++i) {
		for (int j(0); j < n; ++j) {
			int weight;
			fin >> weight;
			if (weight != INF) {
				graph.addEdge(i, j, weight);
			}
		}
	}
	std::vector<int> ans = graph.getNegCycle();
	int size = ans.size();
	for (int i(0); i < ans.size(); ++i) {
		if (ans[i] == -1) {
			--size;
		}
	}
	if (ans.size() != 0) {
		fout << "YES\n";
		fout << size << '\n';
		fout << inc(ans);
	}
	else {
		fout << "NO";
	}

	return 0;
}