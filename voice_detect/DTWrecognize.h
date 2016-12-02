#pragma once

class CDTWrecognize
{
public:
	CDTWrecognize(void);
	virtual ~CDTWrecognize(void);


	/**
	 * ����mfcc����֮���dtw����
	 * @param input
	 * @param pattern
	 * @return
	 */
	static double dtw(const std::vector<std::vector<double>> &input, const std::vector<std::vector<double>> &pattern);

	static std::vector<std::vector<double>> calc_cost(std::vector<std::vector<double>> dis, int n, int m);
	
	static double distance(const vector<double> &lhs, const vector<double> &rhs);

};
