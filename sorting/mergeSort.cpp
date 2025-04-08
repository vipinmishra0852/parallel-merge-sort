#include "mergeSort.hpp"
#include <stdexcept>

MergeSort::MergeSort(std::vector<int> *nums)
{
    this->nums = nums;
}

MergeSort::~MergeSort() = default;

void MergeSort::recursiveSort(int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    recursiveSort(left, mid);
    recursiveSort(mid + 1, right);

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

void MergeSort::sort()
{
    if (nums->empty())
    {
        throw std::invalid_argument("Cannot sort an empty array");
    }
    recursiveSort(0, nums->size() - 1);
}
