#include<fstream>
#include<vector>
#include<queue>

std::ifstream fin("pathbge1.in");
std::ofstream fout("pathbge1.out");

class Graph {
public:
    void addEdge(int v, int u) {
        edges[v].push_back(u);
        edges[u].push_back(v);
    }

    std::vector<int>& getDistances(int startVertex) {
        bfs(startVertex);
        return dist;
    }

    explicit Graph(int n) {
        dist.resize(n);
        edges.resize(n);
        vertexSize = n;
    }

    Graph() {}
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> dist;
    int vertexSize;

    void bfs(int startVertex) {
        for (int i(0); i < vertexSize; ++i) {
            dist[i] = -1;
        }
        std::queue<int> q;
        q.push(startVertex);
        dist[startVertex] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i(0); i < edges[v].size(); ++i) {
                int u = edges[v][i];
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
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
    fout << graph.getDistances(0);

	return 0;
}