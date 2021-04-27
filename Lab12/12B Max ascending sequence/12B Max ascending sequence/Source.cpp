#include<iostream>
#include<vector>
#include<algorithm>

const int INF = 1e9 + 5;

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i(0); i < n; ++i) {
		std::cin >> a[i];
	}
	std::vector<int> dp(n + 1, INF);
	std::vector<int> dpIndexes(n + 1, -1);
	std::vector<int> aParents(n, -1);
	dp[0] = -INF;
	int maxPos = 0;
	for (int i(0); i < n; ++i) {
		int pos = std::upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
		maxPos = std::max(maxPos, pos);
		if (a[i] < dp[pos]) {
			dp[pos] = a[i];
			dpIndexes[pos] = i;
		}
		aParents[i] = dpIndexes[pos - 1];
	}
	std::vector<int> ans;
	int ansPos = dpIndexes[maxPos];
	while (ansPos != -1) {
		ans.push_back(a[ansPos]);
		ansPos = aParents[ansPos];
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << maxPos << '\n';
	for (int i(0); i < ans.size(); ++i) {
		std::cout << ans[i] << ' ';
	}

	return 0;
}