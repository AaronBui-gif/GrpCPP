//
// Created by Huy Bui Thanh on 16/03/2021.
//

#include "main.h"

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator
#include <sstream>

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
    string line;
    string intermediate;
    vector<string>tokens(50000);
    vector<int> int_tokens(50000);
    int arr_x[50000];
    int arr_y[50000];
    int count = 0;
    int x = 0;
    int int_x = 0;
    int y = 0;
    int int_y = 0;
    ifstream myfile("/Users/huybuithanh/CLionProjects/GrpAssn1/Data/data1.csv");
    // If file is found then open it
    if (myfile.is_open()) {
        // Reading file until End of File.
        while (!myfile.eof()) {
            // Reading line in file.
            while(getline(myfile, line)) {
                stringstream check1(line);
                while(getline(check1, intermediate, ','))
                {
                    tokens.push_back(intermediate);
                }
            }
            myfile.close(); // Closing File.
        }
        for (int i=0; i< 50000; i++)
        {
            int num = atoi(tokens.at(i).c_str());
            int_tokens.push_back(num);
        }
        for(int i = 0; i < 1000; i++){
            if(i % 2 == 0){
                arr_x[x] = int_tokens[i];
                x++;
            } else if (i % 2 == 1){
                arr_y[y] = int_tokens[i];
                y++;
            }
        }
//        for(int i = 0; i < tokens.size(); i++) {
//            cout << tokens[i] << '\n';
//        }
        for (int i = 0; i < 1000; i++){
            cout << arr_x[i] << endl;
        }
    }
    else cout << "Unable to open file";
}

/*** FUNCTION to split string into token ***/
void input_token(string line){
    string intermediate;
    stringstream check1(line);
    vector<string>(tokens);
    while(getline(check1, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }

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

