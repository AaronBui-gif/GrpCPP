//
// Created by Huy Bui Thanh on 16/03/2021.
//

#include "main.h"

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
    cout << "Array X: " << endl;
    for (int i = 0; i < 50000; ++i) {
        cout << *(arrayX + i) << endl;
    }

    cout << "Array Y: " << endl;
    for (int i = 0; i < 50000; ++i) {
        cout << *(arrayY + i) << endl;
    }

    /*** Sort array ***/

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
    int arr_y[50001];
    int index_x = 0;
    int index_y = 0;
    int count = 0;
    string word3 = "";
    // Reading file
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpCPP/Data/" + argument );
    // If file is found then open it

    if (myfile.is_open()) {
        // Reading file until End of File.
        skip_line(myfile, 1, '\n');
        // Get words in one line
        while (getline(myfile, word, '\n')) {

            single_word = get_separate_word(word);
            single_word2 = get_separate_word2(word);
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

int* getArrayY(string argument, int arr_y[]){
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
        // Reading file until End of File.
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
//void bucketSort(int arr[], int n)
//{
//
//    // 1) Create n empty buckets
//    vector<int> b[n];
//
//    // 2) Put array elements
//    // in different buckets
//    for (int i = 0; i < n; i++) {
//        int bi = n * arr[i]; // Index in bucket
//        b[bi].push_back(arr[i]);
//    }
//
//    // 3) Sort individual buckets
//    for (int i = 0; i < n; i++)
//        sort(b[i].begin(), b[i].end());
//
//    // 4) Concatenate all buckets into arr[]
//    int index = 0;
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < b[i].size(); j++)
//            arr[index++] = b[i][j];
//}

