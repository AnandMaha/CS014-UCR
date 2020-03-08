#include <iostream> /* cout */
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */
#include <algorithm> /* sort */
using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

int PartitionMidPoint(int numbers[], int i, int k) {
   int l;
   int h;
   int midpoint;
   int pivot;
   int temp;
   bool done;

   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];

   done = false;
   l = i;
   h = k;

   while (!done) {

      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }

      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }

      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;

         ++l;
         --h;
      }
   }

   return h;
}

int PartitionMedianOfThree(int numbers[], int i, int k) {
   int l;
   int h;
   int medianIdx;
   int pivot;
   int temp;
   bool done;

   /* Pick median as pivot */
   int toSort[] = {numbers[i], numbers[(i+k)/2], numbers[k]};
   sort(toSort, toSort+3);
   if(toSort[1] == numbers[i])
    medianIdx = i;
   else if(toSort[1] == numbers[k])
    medianIdx = k;
   else
    medianIdx = (i+k)/2;
   pivot = numbers[medianIdx];

   done = false;
   l = i;
   h = k;

   while (!done) {

      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }

      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }

      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;

         ++l;
         --h;
      }
   }

   return h;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
   int j;

   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }

   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = PartitionMidPoint(numbers, i, k);

   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    int j;

   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }

   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = PartitionMedianOfThree(numbers, i, k);

   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_medianOfThree(numbers, i, j);
   Quicksort_medianOfThree(numbers, j + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
   int i;
   int j;
   int temp;      // Temporary variable for swap

   for (i = 1; i < numbersSize; ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && numbers[j] < numbers[j - 1]) {

         // Swap numbers[j] and numbers[j - 1]
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
      }
   }
}

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main()
{
    int arr1[NUMBERS_SIZE], arr2[NUMBERS_SIZE], arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);

    clock_t start1 = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t end1 = clock();
    int timeTaken1 = (end1 - start1) / CLOCKS_PER_MS;
    cout << timeTaken1 << endl;

    clock_t start2 = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    clock_t end2 = clock();
    int timeTaken2 = (end2 - start2) / CLOCKS_PER_MS;
    cout << timeTaken2 << endl;

    clock_t start3 = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    clock_t end3 = clock();
    int timeTaken3 = (end3 - start3) / CLOCKS_PER_MS;
    cout << timeTaken3 << endl;
    return 0;
}
