#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <vector>
#include <list>

class PmergeMe
{
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

	void	sort(int ac, char **av);

private:
	std::vector<int> seq;

	void	parser(int ac, char **av);
	void	showSequence(const std::string &input, const std::vector<int> &seq);
	void	showTime(const std::string &input, double time);

	template <typename Iterator>
    void mergeInsertSort(Iterator p, Iterator q);

    template <typename Iterator>
    void merge(Iterator p, Iterator q, Iterator r);
};
