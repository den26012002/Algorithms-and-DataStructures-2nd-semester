#include<fstream>
#include<string>
#include<vector>

#define int long long

std::ifstream fin("search2.in");
std::ofstream fout("search2.out");

const int MOD = 1e9 + 7;
const int MULT = 307;

signed main() {
	std::string p, t;
	fin >> p >> t;
	int multPowP = 1;
	for (int i(0); i < p.size(); ++i) {
		multPowP *= MULT;
		multPowP %= MOD;
	}
	int pHash = 0;
	int tHash = 0;
	t = 'a' + t;
	for (int i(0); i < p.size(); ++i) {
		pHash *= MULT;
		pHash += p[i];
		pHash %= MOD;
		tHash *= MULT;
		tHash += t[i];
		tHash %= MOD;
	}
	std::vector<int> ansPoses;
	for (int i(p.size()); i < t.size(); ++i) {
		tHash *= MULT;
		tHash -= (t[i - p.size()]) * multPowP;
		while (tHash < 0) {
			tHash += MOD;
		}
		tHash += t[i];
		tHash %= MOD;
		if (pHash == tHash) {
			ansPoses.push_back(i - p.size() + 1);
		}
	}
	fout << ansPoses.size() << '\n';
	for (int i(0); i < ansPoses.size(); ++i) {
		fout << ansPoses[i] << ' ';
	}


	return 0;
}