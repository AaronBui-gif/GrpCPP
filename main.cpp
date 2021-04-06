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

/*** Set-up functions. ***/
int count_data(string); // checked
void get_array(string, double*, double*, int); // checked
int compare(const void*, const void*);
double mean(double*, int);

// B. Statistic functions
double median(double*, int); // B1
double mode(double*, int); // B2
double variance(double*, int, double); // B3.1
double stdev(double*, int, double); // B3.2
double mean_abs_dev(double*, int); // B4
double FirstQuatile(double*, int); // B5
double skewness(double*, int, double); // B6
double kurtosis(double*, int, double); // B7

// C. Inferential Statistics functions
float covariance(double*, double*, int, double, double); // C1
float pearsonCorrelationCoefficient(float, double, double); // C2
void linear_reg(double*, double*, float, double, double, double, double); // C3
void print_linear_reg(double, double);

// Members name
void printMembers();

/*** MAIN FUNCTION ***/
int main(int argc, char* argv[]) {
    /*** If user does not input 2 arguments ***/
    if (argc != 2) {
        cout << "Input can only contain two arguments" << endl;
        exit(1);
    }
    cout << endl;

    // declare filename from command line
    string filename = argv[1];

    int size = count_data(filename); // count number of data
    // create arrays to store data
    double* array_x = new double[size];
    double* array_y = new double[size];
    get_array(filename, array_x, array_y, size); // extract data into the arrays

    // back up arrays for part C before sorting
    double* org_x = new double[size];
    double* org_y = new double[size];
    for (int i = 0; i < size; i++) {
        org_x[i] = array_x[i];
        org_y[i] = array_y[i];
    }

    // FOR TESTING
    /*for (int i = 0; i < size; i++) {
        cout << "x: " << array_x[i] << ", " << "y: " << array_y[i] << endl << endl; // test
    }

    cout << "back up" << endl;
    for (int i = 0; i < size; i++) {
        cout << "x: " << org_x[i] << ", " << "y: " << org_y[i] << endl << endl; // test
    }*/

    /*** Sort array ***/
    qsort(array_x, size, sizeof(double), compare);
    qsort(array_y, size, sizeof(double), compare);

    // FOR TESTING
    /*cout << "sorted" << endl;
    for (int i = 0; i < size; i++) {
        cout << "x: " << array_x[i] << ", " << "y: " << array_y[i] << endl << endl;
    }*/

    // Mean of X and Y
    double mean_x = mean(array_x, size);
    double mean_y = mean(array_y, size);

    /*
    SECTION B: DESCRIPTIVE STATISTICS
        1. Median
        2. Mode
        3. Variance and Standard deviation
        4. Mean absolute deviation
        5. First Quartile
        6. Skewness
        7. Kurtosis
    */
    // B1. Median of X and Y
    double med_x = median(array_x, size);
    double med_y = median(array_y, size);
    cout << "median_x = " << med_x << " - " << "median_y = " << med_y << endl;

    // B2. Mode of X and Y
    /*double mod_x = mode(array_x, size),
         mod_y = mode(array_y, size);

     cout << "mode_x = " << mod_x << " - " << "mode_y = " << mod_y << endl; */

    // B3.1 Variance of array X and array Y
    double var_x = variance(array_x, size, mean_x);
    double var_y = variance(array_y, size, mean_y);
    cout << "var_x= " << var_x << " - var_y = " << var_y << endl;

    // B3.2 Standard deviation of array X and array Y
    double stdDevX = stdev(array_x, size, mean_x);
    double stdDevY = stdev(array_y, size, mean_y);
    cout << "stdev_x= " << stdDevX << " - stdev_y = " << stdDevY << endl;

    // B4. Mean Absolute Deviations
    double mean_abs_x = mean_abs_dev(array_x, size);
    double mean_abs_y = mean_abs_dev(array_y, size);
    cout << "mad_x= " << mean_abs_x << " - mad_y = " << mean_abs_y << endl;

    // B5. First Quartile
    double quatileArrX = FirstQuatile(array_x, size);
    double quatileArrY = FirstQuatile(array_y, size);
    cout << "q1_x= " << quatileArrX << " - q1_y = " << quatileArrY << endl;

    // B6. Skewness of array X and array Y
    double skew_x = skewness(array_x, size, mean_x);
    double skew_y = skewness(array_y, size, mean_y);
    cout << "skew_x= " << skew_x << " - skew_y = " << skew_y << endl;

    // B7. Kurtosis of array X and array Y
    double kurto_x = kurtosis(array_x, size, mean_x);
    double kurto_y = kurtosis(array_y, size, mean_y);
    cout << "kurt_x= " << kurto_x << " - kurt_y = " << kurto_y << endl;

    /*
    SECTION C: INFERENTIAL STATISTICS
        1. Covariance
        2. Pearson correlatiion coefficient
        3. Linear Regression
    */
    // C1. Covariance of array X and array Y
    double cov = covariance(org_x, org_y, size, mean_x, mean_y);
    cout << "cov(x_y) = ";
    cout << cov << endl;

    // C2. Pearson correlation coefficient of array X and array Y
    float PearsonCorrelation = pearsonCorrelationCoefficient(cov, stdDevX, stdDevY);
    cout << "r(x_y) = ";
    cout << PearsonCorrelation << endl;

    // C3. Linear Regression
    double a, b;
    linear_reg(&a, &b, PearsonCorrelation, mean_x, mean_y, stdDevX, stdDevY);
    print_linear_reg(a, b);

    // delete allocated memories
    delete array_x, array_y, org_x, org_y;
    // Print out name of the members
    printMembers();
    return 0;
}

/*** FUNCTION to count number of line in file ***/
int count_data(string filename) {
    // open the file
    ifstream infile(filename, ios::in | ios::binary);
    if (!infile) {
        cerr << "cannot open input file" << endl;
        return 1;
    }

    char ch; int count = 0;
    while (infile.get(ch)) // while not null
        if (ch == '\n') count++;
    // close file
    infile.close();
    return count; // exclude the title
}

/*** FUNCTION to read a file ***/
void get_array(string filename, double* array_x, double* array_y, int size) {
    char temp[12]; // temp storage when getline
    ifstream infile(filename, ios::in | ios::binary);
    if (!infile) {
        cerr << "cannot open input file" << endl;
        return;
    }
    // skip the title
    string line;
    getline(infile, line);

    // scan while not reaching end of file
    int i = 0;
    while (i < size) {
        infile.getline(temp, sizeof(temp), ',');
        array_x[i] = atoi(temp);
        infile.getline(temp, sizeof(temp));
        array_y[i] = atoi(temp);
        i++;
    }
    infile.close();
    return;
}

/*** FUNCTION to sort array ***/
// adapted from http://www.cplusplus.com/reference/cstdlib/qsort/
int compare(const void* a, const void* b) {
    return ( (int)(*(double*)a - *(double*)b) );
}

/*** FUNCTION to find median ***/
double median(double* array, int size) {
    if (size % 2 == 1) {
        return array[(size + 1) / 2 - 1];
    }
    else {
        return (array[size / 2 - 1] + array[size / 2]) / 2;
    }
}

/*** FUNCTION to find mode ***/
/*double mode(int arr[], int size) {
    // Set maximum as the first element in the array.
    int max_val = arr[0];

    // Find the largest element of the array
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }

    int count[max_val + 1];

    // Initialize count array with all zeros.
    fill_n(count, max_val + 1, 0);

    // Store the count of each element
    for (int i = 0; i < size; i++)
        count[arr[i]]++;

    int max_count = count[0],
        mode = count[0];

    for (int i = 1; i < sizeof(count) / sizeof(int); i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            mode = i;
        }
    }

    cout << "Count[" << mode << "] = " << max_count << endl;

    return mode;
}*/

/*** FUNCTION to get mean of the array ***/
double mean(double* array, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i]; // calculate the sum of all the elements
    }
    return sum / size;
}

/*** FUNCTION to get variance ***/
double variance(double* arr, int size, double mean) {
    // Declare
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum += ((arr[i] - mean) * (arr[i] - mean));
    }

    return (sum / (size - 1));
}

/*** FUNCTION to get mean absolute deviations ***/
double mean_abs_dev(double* arr, int size)
{
    float m = mean(arr, size);
    float s = 0;
    for (int i = 0; i < size; i++)
    {
        s += abs(arr[i] - m);
    }
    return (s / size);
}

/*** FUNCTION to get firs quartile ***/
double FirstQuatile(double* arr, int size) {
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
double stdev(double* arr, int size, double mean) {
    return sqrt(variance(arr, size, mean));
}

double skewness(double* arr, int size, double mean) {
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum = ((arr[i] - mean) * (arr[i] - mean) * (arr[i] - mean));
    }

    return sum / (size * (stdev(arr, size, mean) * stdev(arr, size, mean) * stdev(arr, size, mean)));
}

/*** FUNCTION to get kurtosis ***/
double kurtosis(double* arr, int size, double mean) {
    double kur = 0,
            var = variance(arr, size, mean),
            std_dev = sqrt(var);

    for (int i = 0; i < size; i++)
        kur += pow((arr[i] - mean) / std_dev, 4);

    kur = kur / size - 3;

    return kur;
}

/*** FUNCTION to get covariance of array X and array Y ***/
float covariance(double* array1, double* array2, int size, double mean_x, double mean_y) {
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
float pearsonCorrelationCoefficient(float covariance, double stdevX, double stdevY) {
    // Declare varibales
    float corr = 0;
    // Calculate Pearson Correlation Coefficient
    corr = covariance / (stdevX * stdevY);
    return corr;
}

/*** FUNCTION to print out name ***/
void printMembers() {
    cout << endl;
    cout << "ASSIGNMENT 1 GROUP <03>" << endl;
    cout << "s3740934, s3740934@rmit.edu.vn, Huy, Bui Thanh" << endl;
    cout << "s3764704, s3764704@rmit.edu.vn, Hoang, Nguyen Huy" << endl;
    cout << "s3795370, s3795370@rmit.edu.vn, Dung, Ho Minh" << endl;
    cout << "s3799602, s3799602@rmit.edu.vn, Tri, Lai Nghiep" << endl;
    cout << "s3879052, s3879052@rmit.edu.vn, Long, Nguyen Dich" << endl;
}

void linear_reg(double* a, double* b, float pearson, double mean_x, double mean_y, double stdev_x, double stdev_y) {
    *a = (pearson * stdev_y) / stdev_x;
    *b = mean_y - (*a) * mean_x;
}

void print_linear_reg(double a, double b) {
    cout << "y = " << a << "x + " ;
    if (b > 0) cout << b << endl;
    else cout << '(' << b << ')' << endl;
}
