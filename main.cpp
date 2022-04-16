#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int num_processes;
    int num_resources;

    ifstream fin;     // for reading in
    string inputfile; // input file

    cout << "Enter the name of the input text file: "; // prompt user to enter input text file
    cin >> inputfile;

    fin.open(inputfile); // open input file
    if (fin.is_open())   // if input file is opened
    {
        string str; // for each line of the input file

        getline(fin, str);         // get number of processes
        num_processes = stoi(str); // convert string to num
        getline(fin, str);         // get number of processes
        num_resources = stoi(str); // convert string to num

        cout << num_processes << endl;
        cout << num_resources << endl;

        int ResourceUnits[num_resources]; // an array to hold the number of units per resource

        for (int i = 0; i < num_resources - 1; ++i)
        {
            getline(fin, str, ',');
            ResourceUnits[i] = stoi(str); // assign resource units to corresponding resource in array
            cout << str << endl;
        }

        getline(fin, str, '\n');
        ResourceUnits[num_resources - 1] = stoi(str); // assign last resource unit to last corresponding resource in array
        cout << str << endl;

        int matrixsize = num_processes + num_resources; // adding the # of processes and resources gives us the # of rows and columns in the matrix M
        int matrixM[matrixsize][matrixsize];            // initialize a matrix M with the correct row and column #s based on the processes and resources

        for (int i = 0; i < matrixsize; ++i)
        {
            for (int j = 0; j < matrixsize - 1; ++j)
            {
                getline(fin, str, ',');
                matrixM[i][j] = stoi(str); // assign number to array
                // cout << str << " ";
            }
            getline(fin, str, '\n');
            matrixM[i][matrixsize - 1] = stoi(str); // assign number to last columns
            // cout << str << endl;
        }

        // TEST contents of 2d array
        /*
        for(int i=0;i<matrixsize;++i)
        {
            for(int j=0;j<matrixsize;++j)
            {
                cout<<matrixM[i][j]<<" ";
            }
            cout<<endl;
        }
        */

    }
    fin.close(); // close input file

    return 0;
}