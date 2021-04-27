#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("topsort.in");
std::ofstream fout("topsort.out");

class Graph {
public:
	std::vector<int>& topSort() {
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		for (int i(0); i < edges.size(); ++i) {
			if (vertexColors[i] == Color::WHITE) {
				dfs(i);
			}
		}
		if (!isAbleToTopSort) {
			topSortResult.clear();
			topSortResult.push_back(-2);
		}
		std::reverse(topSortResult.begin(), topSortResult.end());
		return topSortResult;
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
	}

	explicit Graph(int vertexesSize) {
		edges.resize(vertexesSize);
		vertexColors.resize(vertexesSize);
		isAbleToTopSort = true;
	}

	Graph() {
		isAbleToTopSort = true;
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
	bool isAbleToTopSort;

	void dfs(int v) {
		vertexColors[v] = Color::GRAY;
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexColors[u] == Color::GRAY) {
				isAbleToTopSort = false;
			}
			if (vertexColors[u] == Color::WHITE) {
				dfs(u);
			}
		}
		topSortResult.push_back(v);
		vertexColors[v] = Color::BLACK;
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
	int n, m;
	fin >> n >> m;
	Graph graph(n);
	for (int i(0); i < m; ++i) {
		int v, u;
		fin >> v >> u;
		graph.addEdge(v - 1, u - 1);
	}
	fout << increment(graph.topSort());

	return 0;
}