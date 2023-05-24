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
    std::sort(vec.begin(), vec.end());
    end = std::clock();
    time = static_cast<double>(end - start) / 1000000;
    showSequence("After:", vec);
    showTime("std::vector", time);

    std::list<int>  list(seq.begin(), seq.end());
    start = std::clock();
    list.sort();
    end = std::clock();
    time = static_cast<double>(end - start) / 1000000;
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
