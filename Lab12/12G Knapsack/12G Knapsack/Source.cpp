#include<fstream>
#include<vector>
#include<algorithm>

std::ifstream fin("knapsack.in");
std::ofstream fout("knapsack.out");

int main() {
	int s, n;
	fin >> s >> n;
	std::vector<int> weights(n + 1, 0);
	for (int i(1); i <= n; ++i) {
		fin >> weights[i];
	}
	std::vector<std::vector<int>> knapsack(n + 1, std::vector<int>(s + 1));
	for (int i(0); i < std::max(s, n); ++i) {
		knapsack[std::min(i, n)][0] = 0;
		knapsack[0][std::min(i, s)] = 0;
	}
	for (int i(1); i <= n; ++i) {
		for (int j(1); j <= s; ++j) {
			knapsack[i][j] = knapsack[i - 1][j];
			if (j - weights[i] >= 0) {
				knapsack[i][j] = std::max(knapsack[i][j], knapsack[i - 1][j - weights[i]] + weights[i]);
			}
		}
	}
	fout << knapsack[n][s];

	return 0;
}