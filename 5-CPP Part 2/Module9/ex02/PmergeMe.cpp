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
    time = static_cast<double>(end - start);
    showSequence("After:", vec);
    showTime("std::vector", time);

    std::list<int>  list(seq.begin(), seq.end());
    start = std::clock();
    mergeInsertSort(list.begin(), list.end());
    end = std::clock();
    time = static_cast<double>(end - start);
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
void    PmergeMe::mergeInsertSort(Iterator p, Iterator q) {
    const int K = 5;

    if (std::distance(p, q) > K) {
        Iterator mid = p + std::distance(p, q) / 2;
        mergeInsertSort(p, mid);
        mergeInsertSort(mid, q);
        merge(p, mid, q);
    } else {
        for (Iterator i = p; i != q; ++i) {
            typename Iterator::value_type tempVal = *(i + 1);
            Iterator j = i + 1;
            while (j != p && *(j - 1) > tempVal) {
                *j = *(j - 1);
                j--;
            }
            *j = tempVal;
        }
    }
}

template <typename Iterator>
void    PmergeMe::merge(Iterator p, Iterator q, Iterator r) {
    typedef typename Iterator::value_type value_type;

    std::vector<value_type> LA(p, q + 1);
    std::vector<value_type> RA(q + 1, r + 1);
    Iterator itA = p;
    typename std::vector<value_type>::iterator itLA = LA.begin();
    typename std::vector<value_type>::iterator itRA = RA.begin();

    while (itA != r + 1) {
        if (itRA == RA.end() || (itLA != LA.end() && *itRA > *itLA))
            *itA++ = *itLA++;
        else
            *itA++ = *itRA++;
    }
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
    << " elements with " << input << " : " << time << " us\n";
}
