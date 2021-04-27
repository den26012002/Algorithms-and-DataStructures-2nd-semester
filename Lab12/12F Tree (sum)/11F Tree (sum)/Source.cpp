#include<fstream>
#include<algorithm>
#include<vector>

std::ifstream fin("selectw.in");
std::ofstream fout("selectw.out");

class Tree {
public:
	Tree(int vertexSize) :
		graph(vertexSize),
		dp(vertexSize, { -1, -1 }),
		vertexWeights(vertexSize)
	{}

	void addEdge(int parent, int child, int childWeight) {
		if (parent != -1) {
			graph[parent].push_back(child);
		}
		vertexWeights[child] = childWeight;
	}

	int getMaxAllowableSetSize(int root) {
		findMaxAllowableSetsSizes(root);
		return std::max(dp[root].first, dp[root].second);
	}

private:
	std::vector<std::vector<int>> graph;
	std::vector<int> vertexWeights;
	std::vector<std::pair<int, int>> dp; //first - doesn't include, second - include

	void findMaxAllowableSetsSizes(int root) {
		if (dp[root] != std::pair<int, int>{ -1, -1 }) {
			return;
		}
		dp[root] = { 0, vertexWeights[root] };
		for (int i(0); i < graph[root].size(); ++i) {
			int child = graph[root][i];
			findMaxAllowableSetsSizes(child);
			dp[root].first += std::max(dp[child].first, dp[child].second);
			dp[root].second += dp[child].first;
		}
	}
};

int main() {
	int n;
	fin >> n;
	Tree tree(n);
	int root;
	for (int i(0); i < n; ++i) {
		int parent, weight;
		fin >> parent >> weight;
		if (parent == 0) {
			root = i;
		}
		tree.addEdge(parent - 1, i, weight);
	}
	fout << tree.getMaxAllowableSetSize(root) << std::endl;

	return 0;
}