#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{}

PmergeMe::~PmergeMe(void)
{}

PmergeMe::PmergeMe(PmergeMe const &other)
{
    (void)(other);
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	(void)(other);
    return *this;
}

void	PmergeMe::sort(int ac, char **av)
{
    parser(ac, av);
    showSequence("Before:", seq);

    std::clock_t    start, end;
    double          time;

    std::vector<int>    vec(seq);
    start = std::clock();
    mergeInsertSort(vec.begin(), vec.end());
    end = std::clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    showSequence("After:", vec);
    showTime("std::vector", time);

    std::list<int>  list(seq.begin(), seq.end());
    start = std::clock();
    mergeInsertSort(list.begin(), list.end());
    end = std::clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    showTime("std::list", time);
}

void	PmergeMe::parser(int ac, char **av)
{
    if (ac < 2)
        throw std::runtime_error("Error\n");

    seq.clear();
    for (int i = 1; i < ac; i++)
    {
        try
        {
            int num = std::stoi(av[i]);
            if (num > 0)
                seq.push_back(num);
            else
                throw std::runtime_error("Error\n");
        }
        catch(const std::exception& e)
        {
            throw std::runtime_error("Error\n");
        }
    }
    if (seq.empty())
        throw std::runtime_error("Error\n");
}

template <typename Iterator>
void    PmergeMe::mergeInsertSort(Iterator begin, Iterator end)
{
	if (begin == end || std::next(begin) == end)
		return;

	Iterator mid = std::next(begin, std::distance(begin, end) / 2);
	mergeInsertSort(begin, mid);
	mergeInsertSort(mid, end);

	merge(begin, mid, end);
}

template <typename Iterator>
void    PmergeMe::merge(Iterator begin, Iterator mid, Iterator end)
{
	std::vector<typename Iterator::value_type> sorted;
	sorted.reserve(std::distance(begin, end));

	Iterator left = begin;
	Iterator right = mid;

	while (left != mid && right != end)
	{
		if (*right < *left)
		{
			sorted.push_back(*right);
			++right;
		}
		else
		{
			sorted.push_back(*left);
			++left;
		}
	}

	sorted.insert(sorted.end(), left, mid);
	sorted.insert(sorted.end(), right, end);

	std::copy(sorted.begin(), sorted.end(), begin);
}

void	PmergeMe::showSequence(const std::string &input, const std::vector<int> &seq)
{
    std::cout << input;
    for (std::vector<int>::const_iterator it = seq.begin(); it != seq.end(); it++)
        std::cout << " " << *it;
    std::cout << "\n";
}

void	PmergeMe::showTime(const std::string &input, double time)
{
    std::cout << "Time to process a range of " << seq.size() 
    << " elements with " << input << " : " << time << " s\n";
}
