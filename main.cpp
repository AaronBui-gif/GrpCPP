/***
    Course: Software Engineering Design EEET2482
    Assignment: Group Assignment 1
    Contributor: Bui Thanh Huy - s3740934
                 Nguyen Huy Hoang - s3764704

    Lecturer: Minh Dinh
    School: RMIT
***/

/*** Calling Libraries ***/
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

/*** Calling functions. ***/
int* getArrayX(string argument, int arr_x[]);
int* getArrayY(string argument, int arr_y[]);
void skip_line(istream &is, size_t size, char delim);
string get_separate_word(string str);
string get_separate_word2(string str);
void countSort(int arr[], int size);

// Statistic functions
double median(const int arr[], int size);
double mode(int arr[], int size);
double variance(int arr[], int size, double mean);
double FirstQuatile(int arr[], int size);
double stdev(int arr[], int size, double mean);
double skewness(int arr[], int size, double mean);
double kurtosis(int arr[], int size, double mean);

// Inferential Statistics functions
double mean(int array[], int size);
float covariance(int array1[], int array2[], int size, double mean_x, double mean_y);
float pearsonCorrelationCoefficient(int array1[], int array2[], int size, float covariance, double stdevX, double stdevY);

// Members name
void printMembers();
/*** MAIN FUNCTION ***/
int main(int argc, char* argv[]) {
    /*** Declare variables ***/
    string datas;
    int arrX[50000];
    int arrY[50000];
    /*** If user does not input 2 arguments ***/
    if (argc != 2){
        cout << "Format can only contain two arguments" << endl;
        exit(1);
    }

    // Convert argv to string
    string second_argument = argv[1];

    // Set datas contains values in the file.
    int *arrayX = getArrayX(second_argument, arrX);
    int *arrayY = getArrayY(second_argument, arrY);
//    cout << "---------------Array X: -------------------" << endl;
//    for (int i = 0; i < 50000; ++i) {
//        arrX[i] = *(arrayX + i);
//        cout << arrX[i] << endl;
//    }
//
//    cout << "---------------Array Y: -------------------" << endl;
//    for (int i = 0; i < 50000; ++i) {
//        arrY[i] = *(arrayY + i);
//        cout << arrY[i] << endl;
//    }

    /*** Sort array ***/
    countSort(arrX, 50000);
    countSort(arrY, 50000);

//    /*** Print out after sort array ***/
//    cout << "---------------Array X sort: -------------------" << endl;
//    for (int i = 0; i < 50000; ++i) {
//        cout << arrX[i] << endl;
//    }
//
//    cout << "---------------Array Y sort: -------------------" << endl;
//    for (int i = 0; i < 50000; ++i) {
//        cout << arrY[i] << endl;
//    }
    int size_x = sizeof(arrX)/sizeof(arrX[0]),
            size_y = sizeof(arrY)/sizeof(arrY[0]);

    // Mean of X and Y
    double mean_x = mean(arrX, size_x);
    double mean_y = mean(arrY, size_y);

    cout << "mean x = " << mean_x << " - mean y = " << mean_y << endl;

    //--Median of X and Y--

    float med_x = median(arrX, size_x),
            med_y = median(arrY, size_y);
    cout << "median_x = " << med_x << " - " << "median_y = " << med_y << endl;

    //--Mode of X and Y--
    double mod_x = mode(arrX, size_x),
            mod_y = mode(arrY, size_y);

    cout << "mode_x = " << mod_x << " - " << "mode_y = " << mod_y << endl;

    // Variance of array X and array Y
    double var_x = variance(arrX, size_x, mean_x);
    double var_y = variance(arrY, size_y, mean_y);
    cout << "var_x= " << var_x << " - var_y = " << var_y << endl;

    // Standard deviation of array X and array Y
    double stdDevX = stdev(arrX, size_x, mean_x);
    double stdDevY =  stdev(arrY, size_y, mean_y);
    cout << "stdev_x= " << stdDevX << " - stdev_y = " << stdDevY << endl;

    // Mean Absolute Deviations



    // First Quartile
    double quatileArrX = FirstQuatile(arrX, size_x);
    double quatileArrY = FirstQuatile(arrY, size_y);
    cout << "q1_x= " << quatileArrX << " - q1_y = " << quatileArrY << endl;

    // Skewness of array X and array Y
    double skew_x = skewness(arrX, size_x, mean_x);
    double skew_y = skewness(arrY, size_y, mean_y);
    cout << "skew_x= " << skew_x << " - skew_y = " << skew_y << endl;

    // Kurtosis of array X and array Y
    double kurto_x = kurtosis(arrX, size_x, mean_x);
    double kurto_y = kurtosis(arrY, size_y, mean_y);
    cout << "kurt_x= " << kurto_x << " - kurt_y = " << kurto_y << endl;

    // Covariance of array X and array Y
    double cov = covariance(arrX, arrY, size_x, mean_x, mean_y);
    cout << "cov(x_y) = ";
    cout << cov << endl;

    // Pearson correlation coefficient of array X and array Y
    float pearsonCorrelation = pearsonCorrelationCoefficient(arrX, arrY, size_x, cov, stdDevX, stdDevY);
    cout << "r(x_y) = ";
    cout << pearsonCorrelation << endl;

    // Print out name of the members
    printMembers();
    return 0;
}

/*** FUNCTION to read a file ***/
int* getArrayX(string argument, int arr_x[50000]){
    // Declare variables.
    string line;
    string word;
    string word2;
    string intermediate;
    string single_word = "";
    string single_word2 = "";
    int index_x = 0;
    string word3 = "";

    // Reading file
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpCPP/Data/" + argument );

    // If file is found then open it
    if (myfile.is_open()) {
        // SKip on line in the csv file (skip "x,y")
        skip_line(myfile, 1, '\n');
        // Get words in one line
        while (getline(myfile, word, '\n')) {

            single_word = get_separate_word(word);
            int num = stoi(single_word);
            arr_x[index_x] = num;
            index_x++;
            }
    }

    // If File is not found
    else cout << "Unable to open file";
    myfile.close(); // Closing File.

    return arr_x;
}

/*** FUNCTION to input datas y in the array ***/
int* getArrayY(string argument, int arr_y[50000]){
    // Declare variables.
    string line;
    string word;
    string word2;
    string intermediate;
    string single_word = "";
    string single_word2 = "";
    int index_y = 0;
    string word3 = "";
    // Reading file
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpCPP/Data/" + argument );

    // If file is found then open it
    if (myfile.is_open()) {
        // Skip one line in csv file (skip "x,y")
        skip_line(myfile, 1, '\n');
        // Get words in one line
        while (getline(myfile, word, '\n')) {
            single_word2 = get_separate_word2(word);
            int num2 = stoi(single_word2);
            arr_y[index_y] = num2;
            index_y++;
        }
    }
    // If File is not found
    else cout << "Unable to open file";
    myfile.close(); // Closing File.

    return arr_y;
}

/*** FUNCTION to skip 'size' line in file ***/
void skip_line(istream &is, size_t size, char delim){
    size_t i = 0;
    while (i++ < size){
        is.ignore(80, delim);
    }
}

/*** FUNCTION to get data x ***/
string get_separate_word(string str){
    string word = "";

    for (int x = 0; x < str.length(); x++) {
        if (str[x] == ','){
            break;
        } else {
            word += str[x];
        }
    }
    return word;
}

/*** FUNCTION to get data y ***/
string get_separate_word2 (string str){
    string word = "";
    int int_index = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ','){
            int_index = i;
            break;
        }
    }
            for (int j = int_index + 1; j < str.length(); ++j) {
                if (str[j] == '\n'){
                    break;
                } else {
                    word += str[j];
                }
            }

    return word;
}

/*** FUNCTION to sort array ***/
/*** Time complexity: O(n + k) ***/
void countSort(int arr[], int size) {
    // Size of index array has to be same as the size of arr[] to contains all datas.
    int index[50000];
    // Set maximum as the first element in the array.
    int max = arr[0];

    // Find the largest element of the array
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // Size of the count array has to be bigger than the maximum element by one.
    int count[max + 1];
    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in index array
    for (int i = size - 1; i >= 0; i--) {
        index[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++) {
        arr[i] = index[i];
    }
}

/*** FUNCTION to find median ***/
double median(const int arr[], int size) {
    int mid_pos = round(size/2);
    double med = (arr[mid_pos] + arr[mid_pos - 1]);
    return med / 2;
}

/*** FUNCTION to find mode ***/
double mode(int arr[], int size = 50000) {
    // Set maximum as the first element in the array.
    int max_val = arr[0];

    // Find the largest element of the array
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }

    int count[max_val + 1];

    // Initialize count array with all zeros.
    fill_n(count, max_val+1, 0);

    // Store the count of each element
    for (int i = 0; i < size; i++)
        count[arr[i]]++;

    int max_count = count[0],
            mode = count[0];

    for (int i = 1; i < sizeof(count)/ sizeof(int); i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            mode = i;
        }
    }

    cout << "Count[" << mode << "] = " << max_count << endl;

    return mode;
}

/*** FUNCTION to get mean of the array ***/
double mean(int array[], int size){
    double sumMean = 0;
    for (int i = 0; i < size; ++i) {
        sumMean += array[i];
    }

    // Return the mean of elements
    return sumMean / size;
}

/*** FUNCTION to get variance ***/
double variance(int arr[], int size, double mean){
    // Declare
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum += ((arr[i] - mean) * (arr[i] - mean));
    }

    return (sum / (size - 1));
}

/*** FUNCTION to get firs quartile ***/
double FirstQuatile(int arr[], int size) {
    int half_size = round(size / 2);

    float median;

    median = arr[half_size];

    if (half_size % 2 == 0) {
        median = (arr[half_size] + arr[half_size - 1]) / 2;
    }
    else if (half_size % 2 != 0) {
        //half_size = round(half_size);
        median = arr[half_size / 2];
    }

    return median;
}

/*** FUNCTION to get standard deviation ***/
double stdev(int arr[], int size, double mean) {
    return sqrt(variance(arr, size, mean));
}

double skewness(int arr[], int size, double mean) {
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum = ((arr[i] - mean) * (arr[i] - mean) * (arr[i] - mean));
    }

    return sum / (size * (stdev(arr, size, mean) * stdev(arr, size, mean) * stdev(arr, size, mean)));
}

/*** FUNCTION to get kurtosis ***/
double kurtosis(int arr[], int size, double mean) {
    double kur = 0,
            var = variance(arr, size, mean),
            std_dev = sqrt(var);

    for (int i = 0; i < size; i++)
        kur += pow((arr[i] - mean) / std_dev, 4);

    kur = kur/size - 3;

    return kur;
}

/*** FUNCTION to get covariance of array X and array Y ***/
float covariance(int array1[], int array2[], int size, double mean_x, double mean_y){
    // Declare variables.
    float sum = 0;

    // Sigma of (element array X - mean of array X) * (element array Y - mean of array Y)
    for (int i = 0; i < size; ++i) {
        sum = sum + ((array1[i] - mean_x) * (array2[i] - mean_y));
    }
    // Return covariance
    return sum / (size - 1);
}

/*** FUNCTION to get Pearson Correlation Coefficient ***/
float pearsonCorrelationCoefficient(int array1[], int array2[], int size, float covariance, double stdevX, double stdevY){
    // Declare varibales
    float corr = 0;
    // Calculate Pearson Correlation Coefficient
    corr = covariance / (stdevX * stdevY);
    return corr;
}

/*** FUNCTION to print out name ***/
void printMembers(){
    cout << "ASSIGNMENT 2 GROUP <TT>" << endl;
    cout << "s3740934, s3740934@rmit.edu.vn, Huy, Bui Thanh" << endl;
    cout << "XXXXXXX,sXXXXXXX@rmit.edu.vn,FirstName,LastNames" << endl;
    cout << "YYYYYYY,sYYYYYYY@rmit.edu.vn,FirstName,LastNames" << endl;
    cout << "ZZZZZZZ,sZZZZZZZ@rmit.edu.vn,FirstName,LastName" << endl;
}
