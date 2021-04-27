#include<fstream>
#include<vector>
#include<set>

std::ifstream fin("pathbgep.in");
std::ofstream fout("pathbgep.out");

const long long INF = 1e14 + 5;

class Graph {
public:
    explicit Graph(int n = 0) :
        vertexSize(n),
        vertexesEdges(n)
    {}

    void addEdge(int v, int u, int w) {
        vertexesEdges[v].push_back({ u, w });
        vertexesEdges[u].push_back({ v, w });
    }

    std::vector<long long> getDistances(int v = 0) const {
        return findDistsDijkstra(v);
    }

private:
    struct VertexEdge {
        int to;
        long long weight;
    };

    int vertexSize;
    std::vector<std::vector<VertexEdge>> vertexesEdges;

    std::vector<long long> findDistsDijkstra(int start) const {
        std::vector<long long> dists(vertexSize, INF);
        std::vector<bool> isVisited(vertexSize, false);
        std::set<std::pair<long long, int>> q;
        dists[start] = 0;
        q.insert({ 0, start });
        while (!q.empty()) {
            int v = (*q.begin()).second;
            long long minDist = (*q.begin()).first;
            q.erase(q.begin());
            isVisited[v] = true;
            for (int j(0); j < vertexesEdges[v].size(); ++j) {
                int u = vertexesEdges[v][j].to;
                int w = vertexesEdges[v][j].weight;
                if (isVisited[u]) {
                    continue;
                }
                if (minDist + w < dists[u]) {
                    q.erase({ dists[u], u });
                    dists[u] = minDist + w;
                    q.insert({ dists[u], u });
                }
            }
        }
        return dists;
    }
};

template<typename Type>
std::ostream& operator<<(std::ostream& cout, const std::vector<Type>& arr) {
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
        int v, u, w;
        fin >> v >> u >> w;
        graph.addEdge(v - 1, u - 1, w);
    }
    fout << graph.getDistances();

    return 0;
}