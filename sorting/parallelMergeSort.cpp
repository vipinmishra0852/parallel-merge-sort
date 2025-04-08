#include "parallelMergeSort.hpp"
#include <thread>
#include <vector>
#include <algorithm>
#include <stdexcept>

ParallelMergeSort::ParallelMergeSort(std::vector<int> *nums)
    : nums(nums) {}

ParallelMergeSort::~ParallelMergeSort() = default;

void ParallelMergeSort::recursiveSort(int left, int right)
{
    const int THRESHOLD = 5000;

    if (left >= right)
        return;

    if (right - left < THRESHOLD)
    {
        std::sort(nums->begin() + left, nums->begin() + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;

    std::thread thread_1([this, left, mid]
                         { recursiveSort(left, mid); });

    std::thread thread_2([this, mid, right]
                         { recursiveSort(mid + 1, right); });

    thread_1.join();
    thread_2.join();

    std::vector<int> result;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if ((*nums)[i] <= (*nums)[j])
        {
            result.push_back((*nums)[i++]);
        }
        else
        {
            result.push_back((*nums)[j++]);
        }
    }

    while (i <= mid)
        result.push_back((*nums)[i++]);
    while (j <= right)
        result.push_back((*nums)[j++]);

    for (int k = 0; k < result.size(); ++k)
    {
        (*nums)[left + k] = result[k];
    }
}

void ParallelMergeSort::sort()
{
    if (nums->empty())
    {
        throw std::invalid_argument("Cannot sort an empty array");
    }

    std::thread sorter([this]
                       { recursiveSort(0, nums->size() - 1); });

    sorter.join();
}
