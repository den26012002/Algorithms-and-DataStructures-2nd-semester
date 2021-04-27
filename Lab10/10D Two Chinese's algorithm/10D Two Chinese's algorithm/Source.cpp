#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>

std::ifstream fin("chinese.in");
std::ofstream fout("chinese.out");

const long long INF = 1e9 + 5;

class Graph {
public:
    explicit Graph(int _vertexesSize) :
        vertexesSize(_vertexesSize), 
        vertexesEdges(_vertexesSize), 
        vertexesBackEdges(_vertexesSize),
        vertexColors(_vertexesSize),
        vertexComponentNumbs(_vertexesSize)
    {}

    Graph() {}

    void addEdge(int v, int u, int weight = 1) {
        allEdges.push_back({ v, u, weight });
        vertexesEdges[v].push_back({ v, u, weight });
        vertexesBackEdges[u].push_back({ u, v, weight });
    }

    std::vector<int>& topSort() {
        for (int i(0); i < vertexColors.size(); ++i) {
            vertexColors[i] = Color::WHITE;
        }
        for (int i(0); i < vertexesSize; ++i) {
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

    std::pair<bool, long long> getMSTSize(int root = 0) {
        if (!isAllVertexesReachable(root)) {
            return { false, -1 };
        }
        return { true, findMSTSize(root) };
    }

    void clear() {
        allEdges.clear();
        vertexesEdges.clear();
        vertexesBackEdges.clear();
        vertexColors.clear();
        vertexComponentNumbs.clear();
        topSortResult.clear();
    }

private:
    enum class Color {
        BLACK,
        GRAY,
        WHITE,
    };

    struct Edge {
        int from, to;
        int weight;
        bool operator<(const Edge& other) {
            return weight < other.weight;
        }
    };

    int vertexesSize;
    std::vector<Edge> allEdges;
    std::vector<std::vector<Edge>> vertexesEdges;
    std::vector<std::vector<Edge>> vertexesBackEdges;
    std::vector<Color> vertexColors;
    std::vector<int> vertexComponentNumbs;
    std::vector<int> topSortResult;

    void dfsTopSort(int v) {
        vertexColors[v] = Color::BLACK;
        for (int i(0); i < vertexesEdges[v].size(); ++i) {
            int u = vertexesEdges[v][i].to;
            if (vertexColors[u] == Color::WHITE) {
                dfsTopSort(u);
            }
        }
        topSortResult.push_back(v);
    }

    void dfsCondensation(int v, int componentNumb) {
        vertexColors[v] = Color::BLACK;
        vertexComponentNumbs[v] = componentNumb;
        for (int i(0); i < vertexesBackEdges[v].size(); ++i) {
            int u = vertexesBackEdges[v][i].to;
            if (vertexColors[u] == Color::WHITE) {
                dfsCondensation(u, componentNumb);
            }
        }
    }

    bool isAllVertexesReachable(int start) {
        int cntNotVisited = vertexesSize;
        std::vector<bool> visited(vertexesSize);
        std::queue<int> q;
        q.push(start);
        visited[start] = true;
        --cntNotVisited;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i(0); i < vertexesEdges[v].size(); ++i) {
                int u = vertexesEdges[v][i].to;
                if (!visited[u]) {
                    q.push(u);
                    visited[u] = true;
                    --cntNotVisited;
                }
            }
        }
        return (cntNotVisited == 0);
    }

    long long findMSTSize(int root) {
        long long ans = 0;
        std::vector<int> minEdgeWeights(vertexesSize, INF);
        for (const Edge& e : allEdges) {
            minEdgeWeights[e.to] = std::min(minEdgeWeights[e.to], e.weight);
        }
        for (int i(0); i < vertexesSize; ++i) {
            if (i != root) {
                ans += minEdgeWeights[i];
            }
        }
        Graph zeroEdgesGraph(vertexesSize);
        for (const Edge& e : allEdges) {
            if (e.weight == minEdgeWeights[e.to]) {
                zeroEdgesGraph.addEdge(e.from, e.to, e.weight - minEdgeWeights[e.to]);
            }
        }
        if (zeroEdgesGraph.isAllVertexesReachable(root)) {
            return ans;
        }
        int newComponentsNumb = zeroEdgesGraph.condensation().first;
        Graph newGraph(newComponentsNumb);
        for (const Edge& e : allEdges) {
            if (zeroEdgesGraph.vertexComponentNumbs[e.from] != zeroEdgesGraph.vertexComponentNumbs[e.to]) {
                newGraph.addEdge(zeroEdgesGraph.vertexComponentNumbs[e.from] - 1, 
                                    zeroEdgesGraph.vertexComponentNumbs[e.to] - 1, 
                                    e.weight - minEdgeWeights[e.to]);
            }
        }
        clear();
        int newRoot = zeroEdgesGraph.vertexComponentNumbs[root] - 1;
        zeroEdgesGraph.clear();
        ans += newGraph.findMSTSize(newRoot);
        return ans;
    }
};

int main() {
    int n, m;
    fin >> n >> m;
    Graph graph(n);
    for (int i(0); i < m; ++i) {
        long long v, u, w;
        fin >> v >> u >> w;
        graph.addEdge(v - 1, u - 1, w);
    }
    auto ans = graph.getMSTSize();
    fout << (ans.first ? "YES" : "NO");
    if (ans.first) {
        fout << '\n';
        fout << ans.second;
    }


	return 0;
}