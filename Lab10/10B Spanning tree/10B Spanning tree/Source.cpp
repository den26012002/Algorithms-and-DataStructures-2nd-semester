#include<fstream>
#include<vector>
#include<algorithm>
#include<math.h>

const long long INF = 1e9 + 5;

std::ifstream fin("spantree.in");
std::ofstream fout("spantree.out");

struct Point {
    long long x, y;
};

class Graph {
public:
    void addVertex(long long x, long long y) {
        vertexes.push_back({ x, y });
    }

    long double getMSTWeight() {
        long double ans = 0;

        std::vector<long long> priorities(vertexes.size());
        std::vector<bool> visited(vertexes.size());
        for (int i(0); i < vertexes.size(); ++i) {
            priorities[i] = INF;
            visited[i] = false;
        }
        priorities[0] = 0;

        for (int i(0); i < vertexes.size(); ++i) {
            int vNumb = -1;
            int minPriority = INF;
            for (int i(0); i < priorities.size(); ++i) {
                if (!visited[i] && priorities[i] < minPriority) {
                    minPriority = priorities[i];
                    vNumb = i;
                }
            }
            ans += std::sqrt(minPriority);
            visited[vNumb] = true;
            for (int i(0); i < vertexes.size(); ++i) {
                if (visited[i]) {
                    continue;
                }
                const Point& v = vertexes[vNumb];
                const Point& u = vertexes[i];
                long long priority = (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);
                priorities[i] = std::min(priorities[i], priority);
            }
        }
        return ans;
    }

private:
    std::vector<Point> vertexes;
};

int main() {
    int n;
    fin >> n;
    Graph graph;
    for (int i(0); i < n; ++i) {
        long long x, y;
        fin >> x >> y;
        graph.addVertex(x, y);
    }
    fout << std::fixed;
    fout.precision(3);
    fout << /*std::scientific <<*/ graph.getMSTWeight();


	return 0;
}