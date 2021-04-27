#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("bipartite.in");
std::ofstream fout("bipartite.out");

class Graph {
public:
	bool checkBipartite() {
		for (int i(0); i < vertexVisitColors.size(); ++i) {
			vertexVisitColors[i] = Color::WHITE;
			vertexComponentColors[i] = Color::GRAY;
		}
		for (int i(0); i < edges.size(); ++i) {
			if (vertexVisitColors[i] == Color::WHITE) {
				vertexComponentColors[i] = Color::WHITE;
				dfs(i);
			}
		}
		return isBipartite;
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
		edges[u].push_back(v);
	}

	explicit Graph(int vertexesSize) : Graph() {
		edges.resize(vertexesSize);
		vertexVisitColors.resize(vertexesSize);
		vertexComponentColors.resize(vertexesSize);
	}

	Graph() {
		isBipartite = true;
	}

private:
	enum class Color {
		BLACK,
		GRAY,
		WHITE,
	};

	std::vector<std::vector<int>> edges;
	std::vector<Color> vertexVisitColors;
	std::vector<Color> vertexComponentColors;
	bool isBipartite;

	void dfs(int v) {
		vertexVisitColors[v] = Color::BLACK;
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexVisitColors[u] == Color::BLACK) {
				if (vertexComponentColors[u] == vertexComponentColors[v]) {
					isBipartite = false;
				}
			}
			if (vertexVisitColors[u] == Color::WHITE) {
				if (vertexComponentColors[v] == Color::WHITE) {
					vertexComponentColors[u] = Color::BLACK;
				}
				else {
					vertexComponentColors[u] = Color::WHITE;
				}
				dfs(u);
			}
		}
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& cout, const std::vector<T>& arr) {
	for (int i(0); i < arr.size(); ++i) {
		cout << arr[i] << ' ';
	}
	return cout;
}

int main() {
	int n, m;
	fin >> n >> m;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		graph.addEdge(v - 1, u - 1);
	}
	fout << (graph.checkBipartite() ? "YES" : "NO");

	return 0;
}