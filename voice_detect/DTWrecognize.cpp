#include "StdAfx.h"
#include "DTWrecognize.h"

CDTWrecognize::CDTWrecognize(void)
{
}

CDTWrecognize::~CDTWrecognize(void)
{
}

double CDTWrecognize::dtw(const vector<vector<double>> &input, const vector<vector<double>> &pattern)
{
	int n = input.size();
	int m = pattern.size();
	vector<vector<double>> distance_matrix;//距离矩阵
	distance_matrix.resize(n);
	int i=0, j=0;
	for (i = 0;i < n; ++i) {
		distance_matrix[i].resize(m);

		for (j = 0; j < m; ++j) {
			distance_matrix[i][j] = -1;
		}
	}

	//计算每帧距离
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			//if ((j + 1 <= 2 * (i + 1) - 1) && (j + 1 >= 2 * (i + 1) + (m - 2 * n))) {
			distance_matrix[i][j] = distance(input[i], pattern[j]);
			//}
		}
	}

	vector<vector<double>> cost_matrix;
	cost_matrix = calc_cost(distance_matrix, n, m);

	return cost_matrix[cost_matrix.size() - 1][cost_matrix[0].size() - 1];
}

vector<vector<double>> CDTWrecognize::calc_cost(vector<vector<double>> dis, int n, int m)
{
	int start_i = 0,
		start_j = 0,
		stop_i = n,
		stop_j = m;
	double minDis = DBL_MAX;

	int di = n / 20;
	int dj = m / 20;
	int i = 0, j = 0;

	for (i = 0; i < di; i++){
		for (int j = 0; j < dj; j++){
			if (dis[i][j] < minDis) {
				minDis = dis[i][j];
				start_i = i;
				start_j = j;
			}
		}
	}
	minDis = DBL_MAX;
	for (i = n - 1; i >= n - di; i--){
		for (int j = m - 1; j >= m - dj; j--){
			if (dis[i][j] < minDis){
				minDis = dis[i][j];
				stop_i = i;
				stop_j = j;
			}
		}
	}

	vector<vector<double>> cost;
	cost.resize(stop_i - start_i + 1);
	for (i = 0;i < stop_i - start_i + 1; ++i) {
		cost[i].resize(stop_j - start_j + 1);

		for (j = 0; j < stop_j - start_j + 1; ++j) {
			cost[i][j] = -1;
		}
	}

	cost[0][0] = dis[start_i][start_j];
	//计算第一行
	for (int i = start_i + 1; i <= stop_i; ++i) {
		//if (dis[i][0] < 0) {
		//break;
		//}
		//else {
		cost[i - start_i][0] = dis[i][0] + cost[i - start_i - 1][0];
		//}
	}
	//计算第一列
	for (int j = start_j + 1; j <= stop_j; ++j) {
		//if (dis[0][j] < 0) {
		//break;
		//}
		//else {
		cost[0][j - start_j] = dis[0][j] + cost[0][j - start_j - 1];
		//}
	}
	//计算其他
	for (j = start_j + 1; j <= stop_j; ++j) {
		for (i = start_i + 1; i <= stop_i; ++i) {
			cost[i - start_i][j - start_j] = dis[i][j] +
				min(cost[i - start_i - 1][j - start_j - 1],
				min(cost[i - start_i- 1][j - start_j], cost[i - start_i][j - start_j - 1]));
		}
	}

	return cost;
}

double CDTWrecognize::distance(const vector<double> &lhs, const vector<double> &rhs)
{
	double result = 0;
	unsigned int i = 0;
	for (i = 0; i < lhs.size(); ++i) {
		result += pow((lhs[i] - rhs[i]), 2);
	}
	return result;
}

