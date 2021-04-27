#include<iostream>
#include<vector>

#define int long long

const int MOD = 1e9;

int n;
std::vector<int> colors;

int realizeDp(std::vector<std::vector<int>>& dp, int i, int j) {
	if (i > j) {
		return 0;
	}
	if (dp[i][j] !=	-1) {
		return dp[i][j];
	}
	if (colors[i] != colors[j]) {
		dp[i][j] = ((realizeDp(dp, i, j - 1) + realizeDp(dp, i + 1, j)) - realizeDp(dp, i + 1, j - 1));
	} else {
		dp[i][j] = (realizeDp(dp, i, j - 1) + realizeDp(dp, i + 1, j) + 1);
	}
	while (dp[i][j] < 0) {
		dp[i][j] += MOD;
	}
	while (dp[i][j] >= MOD) {
		dp[i][j] -= MOD;
	}
	return dp[i][j];
}

signed main() {
	std::cin >> n;
	colors.resize(n);
	for (int i(0); i < n; ++i) {
		std::cin >> colors[i];
	}
	std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
	std::cout << realizeDp(dp, 0, n - 1);

	return 0;
}