/***
    Course: Software Engineering Design EEET2482
    Assignment: Group Assignment 1
    Contributor: Bui Thanh Huy - s3740934
                 Nguyen Huy Hoang - s3764704
                 Ho Minh Dung - s3795370
                 Lai Nghiep Tri - s3799602
                 Nguyen Dich Long - s3879052
    Lecturer: Minh Dinh
    School: RMIT
***/
/*** Calling Libraries ***/
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <string>

using namespace std;

/*** Function Declaration ***/
// A. Utility functions
int count_data(string); // count number of data from a file
bool get_array(string, double*, double*, int); // get array from a file 
double mean(double*, int); // calculate mean of a set of data
void swap(double*, double*); // swap 2 numbers
int partition(double[], int, int); // utility for quickSort
void quickSort(double[], int, int); // sort through an array of values
bool is_number(char[]); // check if a string is a number

// B. Statistic functions
double median(double*, int); // B1
void mode(double*, int*, int); // B2
void print_mode(double*, int*, int, char); 
double variance(double*, int, double); // B3.1 
double stdev(double*, int, double); // B3.2
double mean_abs_dev(double*, int); // B4 
double q1(double*, int); // B5
double skewness(double*, int, double); // B6
double kurtosis(double*, int, double); // B7

// C. Inferential Statistics functions
double covariance(double*, double*, int, double, double); // C1
double pearsonCorrelationCoefficient(double, double, double); // C2
void linear_reg(double*, double*, float, double, double, double, double); // C3
void print_linear_reg(double, double);

// Members name
void printMembers();

/*** Main Function ***/
int main(int argc, char* argv[]) {
    // Check the number of inputs from command line
    if (argc != 2) {
        cerr << "Input can only contain two arguments" << endl;
        return 1;
    }

    // Set-up and calculate some related quantities
    string filename = argv[1]; // store filename from command line with a string
    int size = count_data(filename); // count number of data
    
    // Create arrays to store data
    double* array_x = new double[size];
    double* array_y = new double[size];
    bool check = get_array(filename, array_x, array_y, size); // extract data from input file into the arrays
    if (check == false) {
        return -1;
    }
    
    // Back up the arrays for part C before sorting
    double* org_x = new double[size];
    double* org_y = new double[size];
    for (int i = 0; i < size; i++) {
        org_x[i] = array_x[i];
        org_y[i] = array_y[i];
    }

    // Sort the array
    quickSort(array_x, 0, size - 1);
    quickSort(array_y, 0, size - 1);

    // Calculate mean of x data set, mean of y data set
    double mean_x = mean(array_x, size);
    double mean_y = mean(array_y, size);

    /*
    SECTION B: DESCRIPTIVE STATISTICS
        1.   Median
        2.   Mode
        3.1. Variance and 
        3.2. Standard deviation
        4.   Mean absolute deviation
        5.   First Quartile
        6.   Skewness
        7.   Kurtosis
    */
    cout << "PART B: Descriptive Statistics" << endl;
    // B1. Median of X and Y
    double med_x = median(array_x, size);
    double med_y = median(array_y, size);
    cout << "median_x = " << med_x << " - " << "median_y = " << med_y << endl << endl;

    // B2. Mode of X and Y
    int* appear = new int[size]; // array to store number of appearances
    mode(array_x, appear, size); // calculate the mode for x
    print_mode(array_x, appear, size, 'x'); // display the result //4th char input: to recognize the data set
    
    mode(array_y, appear, size); // calulate the mode for y
    print_mode(array_y, appear, size, 'y');
  
    // B3.1 Variance of array X and array Y
    double var_x = variance(array_x, size, mean_x);
    double var_y = variance(array_y, size, mean_y);
    cout << "var_x= " << var_x << " - var_y = " << var_y << endl << endl;

    // B3.2 Standard deviation of array X and array Y
    double stdDevX = stdev(array_x, size, mean_x);
    double stdDevY = stdev(array_y, size, mean_y);
    cout << "stdev_x= " << stdDevX << " - stdev_y = " << stdDevY << endl << endl;

    // B4. Mean Absolute Deviations
    double mean_abs_x = mean_abs_dev(array_x, size);
    double mean_abs_y = mean_abs_dev(array_y, size);
    cout << "mad_x= " << mean_abs_x << " - mad_y = " << mean_abs_y << endl << endl;

    // B5. First Quartile
    double q1X = q1(array_x, size);
    double q1Y = q1(array_y, size);
    cout << "q1_x= " << q1X << " - q1_y = " << q1Y << endl << endl;

    // B6. Skewness of array X and array Y
    double skew_x = skewness(array_x, size, mean_x);
    double skew_y = skewness(array_y, size, mean_y);
    cout << "skew_x= " << skew_x << " - skew_y = " << skew_y << endl << endl;

    // B7. Kurtosis of array X and array Y
    double kurto_x = kurtosis(array_x, size, mean_x);
    double kurto_y = kurtosis(array_y, size, mean_y);
    cout << "kurt_x= " << kurto_x << " - kurt_y = " << kurto_y << endl << endl;
    
    /*
    SECTION C: INFERENTIAL STATISTICS
        1. Covariance
        2. Pearson correlatiion coefficient
        3. Linear Regression
    */
    cout << "PART C: Inferential Statistics" << endl;
    // C1. Covariance of array X and array Y
    double cov = covariance(org_x, org_y, size, mean_x, mean_y);
    cout << "cov(x_y) = " << cov << endl << endl;

    // C2. Pearson correlation coefficient of array X and array Y
    float PearsonCorrelation = pearsonCorrelationCoefficient(cov, stdDevX, stdDevY);
    cout << "r(x_y) = " << PearsonCorrelation << endl << endl;

    // C3. Linear Regression
    double a, b; // declare the slope a and the y-intercept b of the Linear Regression
    linear_reg(&a, &b, PearsonCorrelation, mean_x, mean_y, stdDevX, stdDevY); // calculate a and b
    print_linear_reg(a, b); // print out the equation 

    // Delete allocated memories
    delete[] array_x, array_y, org_x, org_y, appear;
    
    // Print out name of the members
    printMembers();
    return 0;
}

/*** Function Definition ***/
/* A. Utility functions */
// Data counter
int count_data(string filename) {
    // open the file
    ifstream infile(filename, ios::in | ios::binary);
    if (!infile) {
        cerr << "cannot open input file" << endl;
        return 1;
    }
    // go through each line and count everytime there's a new line
    char ch; int counter = 0;
    while (infile.get(ch)) // while not null
        if (ch == '\n') counter++;
    // close the file
    infile.close(); 
    return counter; 
 }

// Read data from file and paste them into the given arrays
bool get_array(string filename, double* array_x, double* array_y, int size) {
    // open the file
    ifstream infile(filename, ios::in | ios::binary);
    if (!infile) {
        cerr << "cannot open input file" << endl;
        return false;
    }

    // skip the title
    string line;
    getline(infile, line);

    // scan while not reaching end of file
    int i = 0;
    char temp[12]; // temp storage when getline
    while (i < size) {
        infile.getline(temp, sizeof(temp), ','); // pass an x value into temp when meet the delim ','
        
        // check if the input is a number
        if (is_number(temp) == false) { 
            cerr << "input is not a number at x" << i << endl;
            return false; // if no, let the user know then return
        } 
        else array_x[i] = stod(temp); // if yes, convert string to double and pass it to an element
        
        const char CR = 13; // carriage return
        infile.getline(temp, sizeof(temp), CR); // pass an y value into temp when meet the CR character

        // check if the input is a number
        if (is_number(temp) == false) { 
            cerr << "input is not a number at y" << i << endl;
            return false;
        }
        else array_y[i] = stod(temp);
        
        infile.getline(temp, sizeof(temp)); // skip the new line character
        i++; // increment of i to go to the next elements of the arrays
    }

    // close the file
    infile.close();
    return true;
}

// Swap 2 numbers given their pointers
void swap(double* a, double* b) { 
    double t = *a; 
    *a = *b; 
    *b = t; 
}

// The sorting function
/* This function takes last element as pivot, places * the pivot element at its correct position in sorted * array, 
and places all smaller (smaller than pivot) * to left of pivot and all greater elements to right * of pivot */
int partition(double arr[], int low, int high) { 
    double pivot = arr[high]; int i = (low - 1); 
    for (int j = low; j <= high - 1; j++) { 
        if (arr[j] <= pivot) { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    }
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}
/* The main function that implements QuickSort * arr[] --> Array to be sorted, * low --> Starting index, * high --> Ending index */
void quickSort(double arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is nowat right place */
        int pi = partition(arr, low, high);
        // Separately sort elements before
        // partition and after partition
         quickSort(arr, low, pi - 1);
         quickSort(arr, pi + 1, high);
    }
}

// Calculate the mean of the input data set of known size
double mean(double* array, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) sum += array[i]; // calculate the sum of all the elements
    return sum / size;
}

// Function to check if a string only contains digit characters
bool is_number(char val[]) {
    char* p = val; // set pointer at the beginning of the string
    int dot_counter = 0; 
    if ((*p) == '+' || (*p) == '-') p++; // if meet a + or - then move forward
    while ((*p) != '\0') { 
        if ((*p) == '.') { 
            dot_counter++; // count dot when meet one
            if (dot_counter > 1) return false; // if there's more than 1 dot, return false
        } 
        else if ((*p) < '0' || (*p) > '9') return false; // invalid character then return false
    p++; 
    }
    return true;
}

/* B. Descriptive statistics Functions */
// B1. Median function
double median(double* array, int size) {
    return (size % 2 == 1) ? array[(size + 1) / 2 - 1] : (array[size / 2 - 1] + array[size / 2]) / 2; 
    // array has odd elements: return middle values; even elements: return mean of 2 middle values
}

// B2. Mode functions
// this function counts the number of appearances of a number in the the given sorted data set, it then stores the counter value inside the "appear" array
// at the index that the number last appeared, then resets the counter e.g. dataset (1,1,1,2) -> appear (0,0,3,1)
void mode(double* arr, int* appear, int size) {
    for (int i = 0; i < size; i++) appear[i] = 0; // reset every value to 0
    int counter = 1; // set counter to 1 because counting from index 1
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) counter++; // because the array is already sorted, same numbers are adjacent
        else { 
            appear[i - 1] = counter; // save counter value when encounter a new value in the array
            counter = 1; // reset counter
        }
    }
    return;
}

void print_mode(double* arr, int* appear, int size, char x_or_y) {
    int max = appear[0]; 
    for (int i = 0; i < size; i++) { // go through the appearance array to find the highest value
        if (appear[i] > max) max = appear[i];
    } 
    int counter = 0; // counter to count the number of modes
    for (int i = 0; i < size; i++) {
        if (appear[i] == max) { // check if there are several modes
            cout << "mode_" << x_or_y << "= " << arr[i] << endl; // print out that mode value
            counter++; // if there are then count;
        } 
    }
    cout << "this " << x_or_y << " data set has " << counter << " mode(s)" << endl << endl; // output the number of modes
    return;
}

// B3.1 Variance function
double variance(double* arr, int size, double mean) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += ((arr[i] - mean) * (arr[i] - mean));
    }
    return (sum / (size - 1));
}

// B4. Mean absolute deviation (MAD) function
double mean_abs_dev(double* arr, int size){
    double m = mean(arr, size), s = 0;
    for (int i = 0; i < size; i++) s += abs(arr[i] - m);
    return (s / size);
}

// B5. First quartile function //
double q1(double* arr, int size) {
    return (size % 2 == 1) ? median(arr, (size - 1) / 2) : median(arr, size / 2);
}

// B3.2 Standard deviation function
double stdev(double* arr, int size, double mean) {
    return sqrt(variance(arr, size, mean));
}

// B6. Skewness function
double skewness(double* arr, int size, double mean) {
    double sum = 0;
    double std_dev = sqrt(variance(arr, size, mean));
    for (int i = 0; i < size; i++)
        sum += pow((arr[i] - mean) / std_dev, 3);
    return sum / size;
}

// B7. Kurtosis function
double kurtosis(double* arr, int size, double mean) {
    double kur = 0,
        std_dev = sqrt(variance(arr, size, mean));
    for (int i = 0; i < size; i++)
        kur += pow((arr[i] - mean) / std_dev, 4);
    return kur / size - 3;
}

/* C. Inferential statistics Functions*/
// C1. Covariance
double covariance(double* array1, double* array2, int size, double mean_x, double mean_y) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + ((array1[i] - mean_x) * (array2[i] - mean_y)); // Sigma (Xi - mean of array X) * (Yi - mean of array Y)
    }
    return sum / (size - 1);
}

// C2. Pearson Correlation Coefficient 
double pearsonCorrelationCoefficient(double covariance, double stdevX, double stdevY) {
    return covariance / (stdevX * stdevY);
}

// C3. Linear Regression
void linear_reg(double* a, double* b, float pearson, double mean_x, double mean_y, double stdev_x, double stdev_y) {
    *a = (pearson * stdev_y) / stdev_x; // calculate slope a
    *b = mean_y - (*a) * mean_x; // calculate y-intercept b
}

void print_linear_reg(double a, double b) {
    cout << "y = " << a << "x + " ;
    if (b >= 0) cout << b << endl; 
    else cout << '(' << b << ')' << endl; // if b is negative, add brackets
}

// Print members
void printMembers() {
    cout << endl << "ASSIGNMENT 1 GROUP <03>" << endl;
    cout << "s3740934, s3740934@rmit.edu.vn, Huy, Bui Thanh" << endl;
    cout << "s3764704, s3764704@rmit.edu.vn, Hoang, Nguyen Huy" << endl;
    cout << "s3795370, s3795370@rmit.edu.vn, Dung, Ho Minh" << endl;
    cout << "s3799602, s3799602@rmit.edu.vn, Tri, Lai Nghiep" << endl;
    cout << "s3879052, s3879052@rmit.edu.vn, Long, Nguyen Dich" << endl;
}
