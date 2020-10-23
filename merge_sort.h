// Anthony Galustyan
// Merge sort implementation (with cutoff)
// Bottom up reverse merge sort implementation
// CPSC353

#include <algorithm>
#include "insertion_sort.h"

template <typename T>
class merge_sort
{
public:
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
    {
        T *aux = new T[n];
        //std::cout << "BLOOP" << arr[5] << &aux[5];
        sort(arr, aux, 0, (n - 1), comp);
        assert(is_sorted(arr, n, comp));
    };

private:
    static const int CUTOFF = 7;
    static void sort(T *arr, T *aux, size_t low, size_t high, const comparator<T> &comp)
    {
        if (high <= low) { return;}
        if (high <= (low + CUTOFF))
        {
            insertion_sort<T> ins_sort;
            ins_sort.sort(arr, low, high, comp);
            return;
        }
        size_t mid = low + (high - low) / 2;
        //std::cout << mid << std::endl;
        sort(arr, aux, low, mid, comp);
        sort(arr, aux, mid + 1, high, comp);
        merge(arr, aux, low, mid, high, comp);
    };
    static void merge(T *arr, T *aux, size_t low, size_t mid, size_t high, const comparator<T> &comp)
    {
        assert(is_sorted(arr, low, mid, comp));
        assert(is_sorted(arr, (mid + 1), high, comp));

        for (size_t k = low; k <= high; k++)
        {
            aux[k] = arr[k];
        }

        size_t i = low;
        size_t j = mid + 1;
        for (size_t k = low; k <= high; k++)
        {
            if (i > mid)
                arr[k] = aux[j++];
            else if (j > high)
            {
                //std::cout << arr[k] << std::endl;
                arr[k] = aux[i++];
            }
            // comp?
            else if (less(aux[j], aux[i], comp))
                arr[k] = aux[j++];
            else
                arr[k] = aux[i++];
        }

        assert(is_sorted(arr, low, high, comp));
    };
};
template <typename T>
class merge_bu_sort
{
public:
    // merge_bu_sort() = delete;
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
    {
        T *aux = new T[n];
        for (size_t len = 1; len < n; len *= 2)
        {
            for (size_t lo = 0; lo < n - len; lo += len + len)
            {
                size_t mid = lo + len - 1;
                size_t hi = std::min<size_t>((lo + len + len - 1), (n - 1));
                merge(arr, aux, lo, mid, hi, comp);
            }
        }
    };

private:
    static void merge(T *arr, T *aux, size_t low, size_t mid, size_t high, const comparator<T> &comp)
    {
        for (size_t k = low; k <= high; k++)
        {
            aux[k] = arr[k];
        }

        int i = low, j = mid + 1;
        for (int k = low; k <= high; k++)
        {
            if (i > mid)
                arr[k] = aux[j++];
            else if (j > high)
                arr[k] = aux[i++];
            else if (less(aux[j], aux[i], comp))
                arr[k] = aux[j++];
            else
                arr[k] = aux[i++];
        }
    };
};