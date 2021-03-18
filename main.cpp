//
// Created by Huy Bui Thanh on 16/03/2021.
//

#include "main.h"

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

using namespace std;

// Calling functions.
void read_file();
void input_token(string line);
void input_arr();
void bucketsort(int arr[], int n);

int main() {
    read_file();
    return 0;
}

/*** FUNCTION to read a file ***/
void read_file(){
    // Declare variables.
    int index_x = 0;
    int index_y = 0;
    string line;
    string word;
    int a;
    int b;
    string word2;
    string intermediate;
    vector<string>tokens(500);
    vector<int> int_tokens(500);
    char word_x;
    int arr_x[20];
    int arr_y[500];
    int count = 0;

    int int_x = 0;

    int int_y = 0;
//    for (int i = 0; i < 3; i++){
//        cout << arr_x[i] << endl;
//    }
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpCPP/Data/data4.csv");
    // If file is found then open it
    if (myfile.is_open()) {
        // Reading file until End of File.
        while (!(myfile.eof())) {

            myfile >> word >> word2;
            cout << "word" << endl;
            cout << word << endl;
            cout << "word2" << endl;
            cout << word2 << endl;
            int x = stoi(word);
            cout << "This is x" << endl;
            cout << x << endl;
            int y = stoi(word2);
            cout << "This is y" << endl;
            cout << y << endl;
            while (count == 0){
                cout << "This is element x: " << endl;
                arr_x[index_x] = x;
                cout << arr_x[index_x] << endl;
                cout << "index x" << endl;
                cout << index_x << endl;
                x = 0;
                index_x++;
                count++;
//                cout << "This is count " << endl;
//                cout << count << endl;
                cout << "index x" << endl;
                cout << index_x << endl;
            }
            while (count == 1){
                cout << "This is element y: " << endl;
                arr_y[index_y] = y;
                cout << arr_y[index_y] << endl;
                cout << "index y" << endl;
                cout << index_y << endl;
                index_y++;
                count = 0;

            }
        }
            myfile.close(); // Closing File.
            cout << "This is array x" << endl;
            for (int i = 0; i < 20; i++){
                cout << arr_x[i] << endl;
            }

            cout << "This is array y" << endl;
            for (int i = 0; i < 3; i++){
                cout << arr_y[i] << endl;
            }
    }
    else cout << "Unable to open file";
}

/*** FUNCTION to sort array ***/
void bucketSort(float arr[], int n)
{

    // 1) Create n empty buckets
    vector<float> b[n];

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

