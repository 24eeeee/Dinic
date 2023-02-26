#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <chrono>
#include <ctime>
#include <string>

long long N = 10;
const long long INF = LLONG_MAX;
long long s = 0, t = N - 1;

using Matrix = std::vector<std::vector<long long>>;
Matrix f(N, std::vector<long long>(N, 0));
std::vector<long long> d(N), ptr(N), q(N);

void print(Matrix& a) {
	for (auto& i : a) {
		for (auto j : i) {
			std::cout << j << ' ';
		}
		std::cout << std::endl;
	}
}

Matrix gen_matrix(long long min=0, long long max=1500, long long n=N) {
	Matrix ans(n, std::vector<long long>(n, 0));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long long> dist(min, max);
	for (long long i = 0; i < n-1; ++i) {
		for (long long j = 1; j < n; ++j) {
			if (i == j) { continue; }
			ans[i][j] = dist(gen);
		}
	}
	return ans;
}

bool bfs(const Matrix& c) {
	long long qh = 0, qt = 0;
	q[qt++] = s;
	d.assign(N, -1);
	d[s] = 0;
	while (qh < qt) {
		long long v = q[qh++];
		for (long long to = 0; to < N; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}

long long dfs(long long v, long long flow, const Matrix& c) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (long long& to = ptr[v]; to < N; ++to) {
		if (d[to] != d[v] + 1)  continue;
		long long pushed = dfs(to, std::min(flow, c[v][to] - f[v][to]), c);
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}

long long dinic(const Matrix& c) {
	long long flow = 0;
	for (;;) {
		if (!bfs(c))  break;
		ptr.assign(N, 0);
		while (long long pushed = dfs(s, INF, c))
			flow += pushed;
	}
	return flow;
}

int main() {
	std::string results;
	for (int i = 0; i < 1000; ++i) {
		Matrix Graph = gen_matrix();
		//print(Graph);
		auto start = std::chrono::system_clock::now();
		dinic(Graph);
		auto stop = std::chrono::system_clock::now();
		size_t res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		results += std::to_string(res) + " ";
		N += 1;
		d.resize(N);
		q.resize(N);
		ptr.resize(N);
		t = N - 1;
		f.assign(N, std::vector<long long>(N, 0));
	}
	system(("main.py " + results).c_str());
}