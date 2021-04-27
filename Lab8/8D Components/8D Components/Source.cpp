#include<fstream>
#include<vector>
#include<queue>

std::ifstream fin("components.in");
std::ofstream fout("components.out");

const int MAX_N = 1e5 + 5;

class Graph {
public:
	void addEdge(int v, int u) {
		edges[v].push_back(u);
		edges[u].push_back(v);
	}

	int splitToConnectedComponents() {
		for (int i(0); i < vertexSize; ++i) {
			vertexColors[i] = -1;
		}
		int cntColors = 0;
		for (int i(0); i < vertexSize; ++i) {

			if (vertexColors[i] == -1) {
				bfs(i, ++cntColors);
			}
		}
		return cntColors;
	}

	std::vector<int>& getVertexColors() {
		return vertexColors;
	}

	explicit Graph(int n) {
		vertexColors.resize(n);
		edges.resize(n);
		vertexSize = n;
	}

	Graph() {}
private:
	std::vector<std::vector<int>> edges;
	std::vector<int> vertexColors;
	int vertexSize;

	void bfs(int startVertex, int color = 0) {
		std::queue<int> q;
		q.push(startVertex);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			vertexColors[v] = color;
			for (int i(0); i < edges[v].size(); ++i) {
				int u = edges[v][i];
				if (vertexColors[u] == -1) {
					q.push(u);
				}
			}
		}
	}
};

std::ostream& operator<<(std::ostream& cout, std::vector<int> arr) {
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
	fout << graph.splitToConnectedComponents() << '\n';
	fout << graph.getVertexColors();


	return 0;
}