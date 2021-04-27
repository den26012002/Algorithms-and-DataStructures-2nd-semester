#include<fstream>
#include<vector>

std::ifstream fin("pathsg.in");
std::ofstream fout("pathsg.out");

const int INF = 1e9 + 5;

class Graph {
public:
    explicit Graph(int n = 0) :
        vertexSize(n),
        graphMatrix(n, std::vector<int>(n, INF))
    {}

    void addEdge(int v, int u, int w) {
        graphMatrix[v][u] = w;
    }

    std::vector<std::vector<int>>& getAllDistances() {
        findAllDistances();
        return allDistances;
    }

private:
    int vertexSize;
    std::vector<std::vector<int>> graphMatrix;
    std::vector<std::vector<int>> allDistances;
  
    void findAllDistances() {
        allDistances = graphMatrix;
        for (int i(0); i < vertexSize; ++i) {
            allDistances[i][i] = 0;
        }
        for (int k(0); k < vertexSize; ++k) {
            for (int v(0); v < vertexSize; ++v) {
                for (int u(0); u < vertexSize; ++u) {
                    allDistances[v][u] = std::min(allDistances[v][u], allDistances[v][k] + allDistances[k][u]);
                }
            }
        }
    }
};

std::ostream& operator<<(std::ostream& cout, const std::vector<std::vector<int>>& arr) {
    for (int i(0); i < arr.size(); ++i) {
        for (int j(0); j < arr[i].size(); ++j) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    return cout;
}

signed main() {
    int n, m;
    fin >> n >> m;
    Graph graph(n);
    for (int i(0); i < m; ++i) {
        int v, u, w;
        fin >> v >> u >> w;
        graph.addEdge(v - 1, u - 1, w);
    }
    fout << graph.getAllDistances();

    return 0;
}