#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("cond.in");
std::ofstream fout("cond.out");

class Graph {
public:
	std::vector<int>& topSort() {
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		for (int i(0); i < edges.size(); ++i) {
			if (vertexColors[i] == Color::WHITE) {
				dfsTopSort(i);
			}
		}
		std::reverse(topSortResult.begin(), topSortResult.end());
		return topSortResult;
	}

	std::pair<int, std::vector<int>&> condensation() {
		topSort();
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		int componentsCnt = 0;
		for (int i(0); i < topSortResult.size(); ++i) {
			if (vertexColors[topSortResult[i]] == Color::WHITE) {
				dfsCondensation(topSortResult[i], ++componentsCnt);
			}
		}
		return { componentsCnt, vertexComponentNumbs };
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
		backEdges[u].push_back(v);
	}

	explicit Graph(int vertexesSize) : Graph() {
		edges.resize(vertexesSize);
		vertexColors.resize(vertexesSize);
		backEdges.resize(vertexesSize);
		vertexComponentNumbs.resize(vertexesSize);
	}

	Graph() {}

private:
	enum class Color {
		BLACK,
		GRAY,
		WHITE,
	};

	std::vector<std::vector<int>> edges;
	std::vector<std::vector<int>> backEdges;
	std::vector<Color> vertexColors;
	std::vector<int> vertexComponentNumbs;
	std::vector<int> topSortResult;

	void dfsTopSort(int v) {
		vertexColors[v] = Color::BLACK;
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexColors[u] == Color::WHITE) {
				dfsTopSort(u);
			}
		}
		topSortResult.push_back(v);
	}

	void dfsCondensation(int v, int componentNumb) {
		vertexColors[v] = Color::BLACK;
		vertexComponentNumbs[v] = componentNumb;
		for (int i(0); i < backEdges[v].size(); ++i) {
			int u = backEdges[v][i];
			if (vertexColors[u] == Color::WHITE) {
				dfsCondensation(u, componentNumb);
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

template <typename T>
std::ostream& operator<<(std::ostream& cout, std::pair<int, std::vector<T>&> arr) {
	cout << arr.first << '\n';
	cout << arr.second;
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
	fout << graph.condensation();

	return 0;
}