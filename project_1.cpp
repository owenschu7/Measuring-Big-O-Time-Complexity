#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <chrono>

using namespace std;

enum class SortMethod {
  BUBBLE_SORT,
  INSERT_SORT,
  SELECT_SORT,
  QUICK_SORT,
  QUICK_SORT_BEST
};

map<SortMethod, string> sortMethodMap = {
  {SortMethod::BUBBLE_SORT, "Bubble"},
  {SortMethod::INSERT_SORT, "Insert"},
  {SortMethod::SELECT_SORT, "Select"},
  {SortMethod::QUICK_SORT, "Quick"},
  {SortMethod::QUICK_SORT_BEST, "Quick"},
};

// struct for holding a test, including its condition and outputs
// MIN
// MEAN
// STANDARD DEVIATION
// MAX
struct TEST_DATA {
  SortMethod method = SortMethod::BUBBLE_SORT;
  vector<int> vec;
  int vectors = 10;
  int vectors_length = 100;
  double min = 1.0;
  double max = 1.0;
  double std_dev = 1.0;
  double mean = 1.0;
  bool wasSuccessful = 0;
};


bool isSorted(vector<int> vec);
void bubbleSort(vector<int> &vec);
void insertionSort(vector<int> &vec);
void selectionSort(vector<int> &vec);
void quickSort(vector<int> &vec);
void quickSortBest(vector<int> &vec);
void print(TEST_DATA test);
vector<int> randomVector(int size, int low, int high);
void runTest(TEST_DATA &test);
void runTest(TEST_DATA &test, ofstream &file);
double calcRunTime(SortMethod m, vector<int> &vec);
double findMin(const vector<double>& vec);
double findMax(const vector<double>& vec);
double findMean(const vector<double>& vec);
double findStd_dev(const vector<double> vec);
vector<int> generateBestCaseVector(int size);
vector<int> generateWorstCaseVector(int size);
void runTestsToFile(SortMethod method, ofstream &best_file, ofstream &average_file, ofstream &worst_file, int size);

int main()
{
  srand(time(NULL));

  //part 2.1
  vector<int> exampleVec = {3,2,1};
  TEST_DATA exampleTest = {SortMethod::BUBBLE_SORT, exampleVec, 10, 100}; // NOTE: leave the other values alone (min, max, mean, etc), 
                                                                          // they will be changed after the test is complete
                                                                          // (depending on the function you call)
  //runTest(exampleTest); // run the test
  print(exampleTest);   // print the test to the terminal

  // part 2.2
  ofstream best_case_file("best.csv");
  ofstream average_case_file("average.csv");
  ofstream worst_case_file("worst.csv");

  //each call creates, and runs 3 tests with given vector length (best, avg, worst case), writes them to their file
  runTestsToFile(SortMethod::BUBBLE_SORT, best_case_file, average_case_file, worst_case_file, 10);
  runTestsToFile(SortMethod::BUBBLE_SORT, best_case_file, average_case_file, worst_case_file, 100);
  runTestsToFile(SortMethod::BUBBLE_SORT, best_case_file, average_case_file, worst_case_file, 1000);
  runTestsToFile(SortMethod::BUBBLE_SORT, best_case_file, average_case_file, worst_case_file, 5000);
  runTestsToFile(SortMethod::BUBBLE_SORT, best_case_file, average_case_file, worst_case_file, 10000);

  runTestsToFile(SortMethod::INSERT_SORT, best_case_file, average_case_file, worst_case_file, 10);
  runTestsToFile(SortMethod::INSERT_SORT, best_case_file, average_case_file, worst_case_file, 100);
  runTestsToFile(SortMethod::INSERT_SORT, best_case_file, average_case_file, worst_case_file, 1000);
  runTestsToFile(SortMethod::INSERT_SORT, best_case_file, average_case_file, worst_case_file, 5000);
  runTestsToFile(SortMethod::INSERT_SORT, best_case_file, average_case_file, worst_case_file, 10000);

  runTestsToFile(SortMethod::SELECT_SORT, best_case_file, average_case_file, worst_case_file, 10);
  runTestsToFile(SortMethod::SELECT_SORT, best_case_file, average_case_file, worst_case_file, 100);
  runTestsToFile(SortMethod::SELECT_SORT, best_case_file, average_case_file, worst_case_file, 1000);
  runTestsToFile(SortMethod::SELECT_SORT, best_case_file, average_case_file, worst_case_file, 5000);
  runTestsToFile(SortMethod::SELECT_SORT, best_case_file, average_case_file, worst_case_file, 10000);

  runTestsToFile(SortMethod::QUICK_SORT, best_case_file, average_case_file, worst_case_file, 10);
  runTestsToFile(SortMethod::QUICK_SORT, best_case_file, average_case_file, worst_case_file, 100);
  runTestsToFile(SortMethod::QUICK_SORT, best_case_file, average_case_file, worst_case_file, 1000);
  runTestsToFile(SortMethod::QUICK_SORT, best_case_file, average_case_file, worst_case_file, 5000);
  runTestsToFile(SortMethod::QUICK_SORT, best_case_file, average_case_file, worst_case_file, 10000);

  return 0;
}


//checks if a vector is sorted
bool isSorted(vector<int> vec)
{
  int i = 1;
  while(i < vec.size())
  {
    if (vec[i] < vec[i - 1])
    {
      return false;
    }
    i++;
  }
  return true;
}


void bubbleSort(vector<int> &vec)
{
  bool sorted = false;
  int temp;
  while (!sorted)
  {
    sorted = true;
    for (int i = 1; i < vec.size(); i++)
    {
      if (vec[i - 1] > vec[i])
      {
        temp = vec[i-1];
        vec[i-1] = vec[i];
        vec[i] = temp;
        sorted = false;
      }
    }
  }
}


void insertionSort(vector<int> &vec)
{
  int i = 1;
  int j;
  int temp;
  while (i < vec.size())
  {
    j = i;
    while(j > 0 && vec[j] < vec[j-1])
    {
      temp = vec[j - 1];
      vec[j - 1] = vec[j];
      vec[j] = temp;
      j = j - 1;
    }
    i = i + 1;
  }
}


void selectionSort(vector<int> &vec)
{
  int uMin;
  int temp;
  for (int i = 0; i < vec.size() - 1; i++)
  {
    uMin = i;
    for (int j = i + 1; j < vec.size(); j++)
    {
      if (vec[j] < vec[uMin])
      {
        uMin = j;
      }
    }
    temp = vec[i];
    vec[i] = vec[uMin];
    vec[uMin] = temp;
  }
}


// (recursive)
void quickSort(vector<int> &vec)
{
  if (vec.size() <= 1)
  {
    return;
  }
  int Lpivot = vec[0];
  vector<int> A = {};
  vector<int> B = {};
  for (int e = 1; e < vec.size(); e++)
  {
    if (vec[e] <= Lpivot)
    {
      A.push_back(vec[e]);
    } else {
      B.push_back(vec[e]);
    }
  }
  quickSort(A);
  quickSort(B);
  vec.clear();
  vec.insert(vec.end(), A.begin(), A.end());
  vec.push_back(Lpivot);
  vec.insert(vec.end(), B.begin(), B.end());
}


//modifies the vector, so that the median value is at the front (recursive)
void quickSortBest(vector<int> &vec)
{
  if (vec.size() <= 1)
  {
    return;
  }

  //swap middle to front
  int temp = vec[0];
  vec[0] = vec[vec.size() / 2];
  vec[vec.size() / 2] = temp;

  int Lpivot = vec[0];
  vector<int> A = {};
  vector<int> B = {};
  for (int e = 1; e < vec.size(); e++)
  {
    if (vec[e] <= Lpivot)
    {
      A.push_back(vec[e]);
    } else {
      B.push_back(vec[e]);
    }
  }
  quickSortBest(A);
  quickSortBest(B);
  vec.clear();
  vec.insert(vec.end(), A.begin(), A.end());
  vec.push_back(Lpivot);
  vec.insert(vec.end(), B.begin(), B.end());
}

// ************************
// Bubble sort on 10 vectors of length 100
// Sorting successful
// Minimum: 1 sec; Mean: 1 sec; Standard deviation: 1 sec; Maximum: 1 sec
// ************************
void print(TEST_DATA test)
{
  cout << "************************\n";
  cout << sortMethodMap.at(test.method) << " sort on " << test.vectors << " vectors of length " << test.vectors_length << "\n";

  // Check the boolean to print the correct status
  if (test.wasSuccessful) 
  {
    cout << "Sorting successful\n";
  } 
  else 
  {
    cout << "Sorting failed\n";
  }

  // Print the stats
  cout << "Minimum: " << test.min << " sec; "
       << "Mean: " << test.mean << " sec; "
       << "Standard deviation: " << test.std_dev << " sec; "
       << "Maximum: " << test.max << " sec\n";
  cout << "************************\n";
}


// returns a vector with randomized values
vector<int> randomVector(int size, int low, int high)
{
  vector<int> vec(size, 0);
  for (int i = 0; i < vec.size(); i++)
  {
    vec[i] = rand() % (high - low +1) + low;
  }
  return vec;
}


// runs test, puts test result back into the TEST_DATA object
void runTest(TEST_DATA &test)
{
  double result;
  vector<double> results;
  for(int i = 0; i < test.vectors; i++)
  {
    //1 randomize the vector
    vector<int> values = randomVector(test.vectors_length, 0, 1000);
    //2 test the data on sorting algo (test.method)
    result = calcRunTime(test.method, values);

    //3 append result to vector
    results.push_back(result);

    //4 verify the sort was successful
    test.wasSuccessful = isSorted(values);

    //find min, max, mean
    test.min = findMin(results);
    test.max = findMin(results);
    test.mean = findMean(results);
    test.std_dev = findStd_dev(results);
  }
}


// run test, append to the file
void runTest(TEST_DATA &test, ofstream &file)
{
  //run the test, append, to the file (do it for test.vectors times)
  //bubble,10,7e-07
  //insertion,10,6e-07
  //selection,100,2.67e-05
  //quick,10000,0.0143179
  vector<int> vecCopy;
  for(int i = 0; i < test.vectors; i++)
  {
    //make a fresh copy of the test vector so we dont keep sorting the same vector
    vecCopy = test.vec;

    file << sortMethodMap.at(test.method) << "," << test.vec.size() << "," << calcRunTime(test.method, vecCopy) << endl;
  }
  test.wasSuccessful = isSorted(vecCopy);
  if(!test.wasSuccessful)
  {
    cerr << "test failed" << endl;
  }
}


// returns the time it took to sort the vector using a given sort method
double calcRunTime(SortMethod m, vector<int> &vec)
{
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed;

  switch (m)
  {
    case(SortMethod::BUBBLE_SORT):
      start = chrono::high_resolution_clock::now();
      bubbleSort(vec);
      end = chrono::high_resolution_clock::now();
      elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
      break;
    case(SortMethod::INSERT_SORT):
      start = chrono::high_resolution_clock::now();
      insertionSort(vec);
      end = chrono::high_resolution_clock::now();
      elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
      break;
    case(SortMethod::SELECT_SORT):
      start = chrono::high_resolution_clock::now();
      selectionSort(vec);
      end = chrono::high_resolution_clock::now();
      elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
      break;
    case(SortMethod::QUICK_SORT):
      start = chrono::high_resolution_clock::now();
      quickSort(vec);
      end = chrono::high_resolution_clock::now();
      elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
      break;
    case(SortMethod::QUICK_SORT_BEST):
      start = chrono::high_resolution_clock::now();
      quickSortBest(vec);
      end = chrono::high_resolution_clock::now();
      elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
      break;
    default:
      cerr << "wrong sort type" << endl;
  }
    return elapsed;
}


double findMin(const vector<double>& vec)
{
  double minVal = vec[0];
  for (int i = 1; i < vec.size(); ++i)
  {
    if (vec[i] < minVal)
    {
      minVal = vec[i];
    }
  }
  return minVal;
}


double findMax(const vector<double>& vec)
{
  if (vec.empty()) return 0.0; 
  
  double maxVal = vec[0];
  for (int i = 1; i < vec.size(); ++i)
  {
    if (vec[i] > maxVal)
    {
      maxVal = vec[i];
    }
  }
  return maxVal;
}


double findMean(const vector<double>& vec)
{
  if (vec.empty()) return 0.0;
  
  double sum = 0.0;
  for (int i = 0; i < vec.size(); ++i)
  {
    sum += vec[i];
  }
  
  return sum / vec.size(); 
}


double findStd_dev(const vector<double> vec)
{
  double mean = 0;
  for (int i = 0; i < vec.size(); i++)
  {
    mean += vec[i];
  }
  mean = mean / vec.size();
  double sd = 0;
  for (int i = 0; i < vec.size(); i++)
  {
    sd += (vec[i]-mean)*(vec[i]-mean);
  }
  sd = sd / (vec.size()-1);
  return sqrt(sd);
}


//best case vector (sorted)
vector<int> generateBestCaseVector(int size) 
{
    vector<int> vec(size);
    for (int i = 0; i < size; i++) 
    {
        vec[i] = i; // Results in: 0, 1, 2, 3, 4...
    }
    return vec;
}


//worst case vector (not sorted)
vector<int> generateWorstCaseVector(int size) 
{
    vector<int> vec(size);
    for (int i = 0; i < size; i++) 
    {
        vec[i] = size - i; // Results in: 100, 99, 98, 97...
    }
    return vec;
}


//creates tests and runs them to their file
void runTestsToFile(SortMethod method, ofstream &best_file, ofstream &average_file, ofstream &worst_file, int size)
{
  //we need to check if the algo is quick sort so we can call a differert function on the best case
  if(method == SortMethod::QUICK_SORT)
  {
    //cout << "starting " << sortMethodMap.at(method) << endl;
    //create the test object calling the method that sorts a sorted vector (0,1,2,3...) using the best case algorithm for quicksort
    TEST_DATA best = {SortMethod::QUICK_SORT_BEST, generateBestCaseVector(size), 50, size};
    //continue creating other tests
    TEST_DATA avg = {method, randomVector(size, 0, size), 50, size};
    TEST_DATA worst = {method, generateWorstCaseVector(size), 50, size};

    //pass the test object into the function
    runTest(best, best_file);
    runTest(avg, average_file);
    runTest(worst, worst_file);
  } else {
    //cout << "starting " << sortMethodMap.at(method) << endl;
    TEST_DATA best = {method, generateBestCaseVector(size), 50, size};
    TEST_DATA avg = {method, randomVector(size, 0, size), 50, size};
    TEST_DATA worst = {method, generateWorstCaseVector(size), 50, size};

    //pass the test object into the function
    runTest(best, best_file);
    runTest(avg, average_file);
    runTest(worst, worst_file);
  }
}

