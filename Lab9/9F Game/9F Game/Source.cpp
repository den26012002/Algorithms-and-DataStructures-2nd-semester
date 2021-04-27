#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("game.in");
std::ofstream fout("game.out");

class Graph {
public:
	bool isFirstWinHere(int v) {
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		for (int i(0); i < isWinIfStartsHere.size(); ++i) {
			isWinIfStartsHere[i] = false;
		}
		dfs(v);
		return isWinIfStartsHere[v];
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
	}

	explicit Graph(int vertexesSize) {
		edges.resize(vertexesSize);
		vertexColors.resize(vertexesSize);
		isWinIfStartsHere.resize(vertexesSize);
	}

	Graph() {}

private:
	enum class Color {
		BLACK,
		GRAY,
		WHITE,
	};

	std::vector<std::vector<int>> edges;
	std::vector<Color> vertexColors;
	std::vector<bool> isWinIfStartsHere;

	void dfs(int v) {
		vertexColors[v] = Color::BLACK;
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexColors[u] == Color::WHITE) {
				dfs(u);
			}
			if (!isWinIfStartsHere[u]) {
				isWinIfStartsHere[v] = true;
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
	int n, m, s;
	fin >> n >> m >> s;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		graph.addEdge(v - 1, u - 1);
	}
	fout << (graph.isFirstWinHere(s - 1) ? "First player wins" : "Second player wins");

	return 0;
}