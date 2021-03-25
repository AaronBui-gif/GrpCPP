//
// Created by Huy Bui Thanh on 16/03/2021.
//

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
    cout << "---------------Array X: -------------------" << endl;
    for (int i = 0; i < 50000; ++i) {
        arrX[i] = *(arrayX + i);
        cout << arrX[i] << endl;
    }

    cout << "---------------Array Y: -------------------" << endl;
    for (int i = 0; i < 50000; ++i) {
        arrY[i] = *(arrayY + i);
        cout << arrY[i] << endl;
    }

    /*** Sort array ***/
    countSort(arrX, 50000);
    countSort(arrY, 50000);

    /*** Print out after sort array ***/
    cout << "---------------Array X sort: -------------------" << endl;
    for (int i = 0; i < 50000; ++i) {
        cout << arrX[i] << endl;
    }

    cout << "---------------Array Y sort: -------------------" << endl;
    for (int i = 0; i < 50000; ++i) {
        cout << arrY[i] << endl;
    }
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
