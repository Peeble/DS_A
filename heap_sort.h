// Anthony Galustyan
// CPSC353

#include <algorithm>
#include "insertion_sort.h"
#include "random.h"
//#include <random>

template <typename T>
class heap
{
public:
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
    {
        for (size_t k = n / 2; k >= 1; k--)
        {
            sink(arr, k, n, comp);
        }

        int k = n;
        while (k > 1)
        {
            exchange(arr, 0, k - 1);
            k--;
            sink(arr, 1, k, comp);
        }
    };

private:
    static void sink(T *arr, size_t k, size_t n, const comparator<T> &comp)
    {
        while (2 * k <= n)
        {
            size_t j = 2 * k;
            if (j < n && less(arr[j - 1], arr[j], comp))
            {
                ++j;
            }
            if (!less(arr[k - 1], arr[j-1], comp))
            {
                break;
            }
            exchange(arr, k - 1, j - 1);
            k = j;
        }
    };

    static bool lesser(T *arr, size_t i, size_t j, const comparator<T> &comp)
    {
        return ::less(arr[i - 1], arr[j - 1], comp);
    }
};


template <typename T>
class Max_pq_heap
{
public:
    static void MaxPQ(int initCapacity, const comparator<T> &comp = fwd_comparator<T>())
    {

    };

private:

};