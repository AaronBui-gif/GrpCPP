//
// Created by Huy Bui Thanh on 16/03/2021.
//

#include "main.h"

/*** Calling Libraries ***/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator
#include <sstream>

using namespace std;

/*** Calling functions. ***/
vector<string> read_file(string argument);
vector<int> string_to_int_vector(vector<string> datas);
int* fillArrX(vector<int> int_datas);
int* fillArrY(vector<int> int_datas);
int *input_array();
void bucketsort(int arr[], int n);

/*** MAIN FUNCTION ***/
int main(int argc, char* argv[]) {
    /*** Declare variables ***/
    vector<string> datas;
    vector<int> int_datas;
    int *arr_x;
    int *arr_y;
    /*** If user does not input 2 arguments ***/
    if (argc != 2){
        cout << "Format can only contain two arguments" << endl;
        exit(1);
    }
    // Convert argv to string
    string second_argument = argv[1];
    vector<string> arguments(argv, argv +argc);
    // Set datas contains values in the file.
    datas = read_file(second_argument);
    /*** PRINT OUT datas in vector<string> ***/
    for (int i = 0; i < datas.size(); ++i) {
        cout << datas[i] << endl;
    }

    /*** Convert vector<string> to vector<int> ***/
    int_datas = string_to_int_vector(datas);
    /*** PRINT OUT datas in vector<int> ***/
    for (int i = 0; i < datas.size(); ++i) {
        cout << int_datas[i] << endl;
    }

    /*** Input values to array ***/
    arr_x = fillArrX(int_datas);
    arr_y = fillArrY(int_datas);
    size_t sizeArrX = sizeof(&arr_x)/ sizeof(arr_x[0]);
    /*** Print out elements in the array ***/
    cout << "Printing elements in array x" << endl;
    for (int i = 0; i < sizeArrX; ++i) {
        cout << arr_x[i] << " ";
    }
    cout << endl;
    return 0;
}

/*** FUNCTION to read a file ***/
vector<string> read_file(string argument){
    // Declare variables.
    string line;
    string word;
    string word2;
    string intermediate;
    vector<string> separate_word;

    // Reading file
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpCPP/Data/" + argument );
    // If file is found then open it
    if (myfile.is_open()) {
        // Reading file until End of File.
        while (getline(myfile, word, ',')) {
                cout << word << endl;
                stringstream ss(word);
                string single_word;
                while(getline(ss, single_word, ' ')) {
                    separate_word.push_back(single_word);
                }
            }
    }
    else cout << "Unable to open file";
    myfile.close(); // Closing File.

    return separate_word;
}

/*** FUNCTION to convert vector<string> to vector<int> ***/
vector<int> string_to_int_vector(vector<string> datas) {
    vector<int> numbers;
    for (int i = 0; i < datas.size(); ++i) {
        int num = atoi(datas.at(i).c_str());
        numbers.push_back(num);
    }

    return numbers;
}
/*** FUNCTION to input vector<int> to array x contains numbers ***/
int * fillArrX(vector<int> int_datas){
    int temp_arr[int_datas.size() / 2];
    for (int i = 0; i < int_datas.size(); ++i) {
        if (i % 2 == 0){
            temp_arr[i] = int_datas[i];
        }

    }

    return temp_arr;
}

/*** FUNCTION to input vector<int> to array y contains numbers ***/
int * fillArrY(vector<int> int_datas){
    int temp_arr[int_datas.size() / 2];
    for (int i = 0; i < int_datas.size(); ++i) {
        if (i % 2 == 1){
            temp_arr[i] = int_datas[i];
        }

    }

    return temp_arr;
}

/*** FUNCTION to sort array ***/
void bucketSort(int arr[], int n)
{

    // 1) Create n empty buckets
    vector<int> b[n];

    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

