// Anthony Galustyan
// Quick sort implementation (with cutoff)
// CPSC353

#include <algorithm>
#include "insertion_sort.h"
#include "random.h"
//#include <random>

template <typename T>
class quick_sort
{
public:
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
    {
        //std_random<T>::shuffle(arr, n);
        sort(arr, 0, (int)n - 1, comp);
        assert(is_sorted(arr, n, comp));
    };

private:
    static const int CUTOFF = 7;
    static void sort(T *arr, int low, int high, const comparator<T> &comp)
    {
        if (high <= low)
        {
            return;
        }

        if (high <= (low + CUTOFF))
        {
            insertion_sort<T> ins_sort;
            ins_sort.sort(arr, low, high, comp);
            return;
        }
        size_t j = partition(arr, low, high, comp);
        sort(arr, low, (j - 1), comp);
        sort(arr, (j + 1), high, comp);
        assert(is_sorted(arr, low, high, comp));
    };

    static size_t partition(T *arr, size_t low, size_t high, const comparator<T> &comp)
    {
        size_t i = low;
        size_t j = high + 1;
        T v = arr[low];
        while (true)
        {
            while (less(arr[++i], v, comp))
            {
                if (i == high)
                {
                    break;
                }
            }

            while (less(v, arr[--j]))
            {
                if (j == low)
                {
                    break;
                }
            }

            if (i >= j)
            {
                break;
            }

            exchange(arr, i, j);
        }

        exchange(arr, low, j);

        return j;
    };
};

template <typename T>
class quick_sort_3way
{
public:
    static void sort(T *arr, size_t n, const comparator<T> &comp = fwd_comparator<T>())
    {
        std_random<T>::shuffle(arr, n);
        //print("Test0: ", arr, n);
        sort(arr, 0, (int)n - 1, comp);
        assert(is_sorted(arr, n, comp));
    };

private:
    static const int CUTOFF = 7;
    static void sort(T *arr, int low, int high, const comparator<T> &comp)
    {
        if (high <= low)
        {
            return;
        }

        if (high <= (low + CUTOFF))
        {
            insertion_sort<T> ins_sort;
            ins_sort.sort(arr, low, high, comp);
            return;
        }
       // print("Test1: ", arr, low, high);
        //std::cout << "|" << std::endl;
        size_t lt = low;
        size_t gt = high;
        T v = arr[low];
        size_t i = low + 1; // low + 1 ?
        while (i <= gt)
        {
            //int cmp = compare(arr[i], v, comp);
            //if (cmp < 0)
            if(less(arr[i], v, comp))
            {
                exchange(arr, lt++, i++);
            }
            //else if (cmp > 0)
            else if(less(v, arr[i], comp))
            {
                exchange(arr, i, gt--);
            }
            /*
            if (gt != 0) 
            {
                --gt;
            }*/
            else
                i++;
        }
        sort(arr, low, lt - 1, comp);
        //sort(arr, low, (lt == 0 ? 0 : lt - 1), comp);
        sort(arr, gt + 1, high, comp);
        assert(is_sorted(arr, low, high, comp));
    };
};