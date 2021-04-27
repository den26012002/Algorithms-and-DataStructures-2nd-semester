#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("hamiltonian.in");
std::ofstream fout("hamiltonian.out");

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

	bool checkHamiltonianPath() {
		topSort();
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		dfsHamiltonianPath(topSortResult[0]);
		return hasHamiltonianPath;
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
	}

	explicit Graph(int vertexesSize) : Graph() {
		edges.resize(vertexesSize);
		vertexColors.resize(vertexesSize);
	}

	Graph() {
		hasHamiltonianPath = false;
	}

private:
	enum class Color {
		BLACK,
		GRAY,
		WHITE,
	};

	std::vector<std::vector<int>> edges;
	std::vector<Color> vertexColors;
	std::vector<int> topSortResult;
	bool hasHamiltonianPath;

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

	void dfsHamiltonianPath(int v, int depth = 1) {
		//vertexColors[v] = Color::BLACK;
		if (depth == vertexColors.size()) {
			hasHamiltonianPath = true;
		}
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexColors[u] == Color::WHITE && u == topSortResult[depth]) {
				dfsHamiltonianPath(u, depth + 1);
			}
			if (hasHamiltonianPath) {
				return;
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

std::vector<int>& increment(std::vector<int>& arr) {
	for (int i(0); i < arr.size(); ++i) {
		++arr[i];
	}
	return arr;
}

int main() {
	fin.sync_with_stdio(false);
	fin.tie(0);
	fout.sync_with_stdio(false);
	fout.tie(0);
	int n, m;
	fin >> n >> m;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		graph.addEdge(v - 1, u - 1);
	}
	fout << (graph.checkHamiltonianPath() ? "YES" : "NO");

	return 0;
}