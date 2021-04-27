#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("cycle.in");
std::ofstream fout("cycle.out");

class Graph {
public:
	std::vector<int>& findCycle() {
		for (int i(0); i < vertexColors.size(); ++i) {
			vertexColors[i] = Color::WHITE;
		}
		for (int i(0); i < edges.size(); ++i) {
			if (vertexColors[i] == Color::WHITE) {
				dfs(i);
			}
		}
		std::reverse(cycle.begin(), cycle.end());
		return cycle;
	}

	void addEdge(int v, int u) {
		edges[v].push_back(u);
	}

	explicit Graph(int vertexesSize) {
		edges.resize(vertexesSize);
		vertexColors.resize(vertexesSize);
		hasCycle = false;
		isFinishedCycle = false;
	}

	Graph() {
		hasCycle = false;
		isFinishedCycle = false;
	}

private:
	enum class Color {
		BLACK,
		GRAY,
		WHITE,
	};

	std::vector<std::vector<int>> edges;
	std::vector<Color> vertexColors;
	std::vector<int> cycle;
	bool hasCycle;
	bool isFinishedCycle;

	void dfs(int v) {
		vertexColors[v] = Color::GRAY;
		for (int i(0); i < edges[v].size(); ++i) {
			int u = edges[v][i];
			if (vertexColors[u] == Color::GRAY && !isFinishedCycle) {
				hasCycle = true;
				cycle.push_back(u);
				cycle.push_back(v);
				return;
			}
			if (vertexColors[u] == Color::WHITE) {
				dfs(u);
				if (hasCycle && !isFinishedCycle) {
					if (v != cycle[0]) {
						cycle.push_back(v);
					}
					else {
						isFinishedCycle = true;
					}
					vertexColors[v] = Color::BLACK;
					return;
				}
			}
		}
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
	std::vector<int>& cycle = graph.findCycle();
	if (cycle.size() == 0) {
		fout << "NO";
	}
	else {
		fout << "YES\n";
		fout << increment(cycle);
	}


	return 0;
}