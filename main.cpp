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

        cout << "# of Processes: " << num_processes << endl;
        cout << "# of Resources: " << num_resources << endl;

        int ResourceUnits[num_resources]; // an array to hold the number of units per resource

        for (int i = 0; i < num_resources - 1; ++i)
        {
            getline(fin, str, ',');
            ResourceUnits[i] = stoi(str); // assign resource units to corresponding resource in array
            // cout << str << endl;
        }

        getline(fin, str, '\n');
        ResourceUnits[num_resources - 1] = stoi(str); // assign last resource unit to last corresponding resource in array
        // cout << str << endl;

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

        int AllocationMatrix[num_processes][num_resources]; // Allocation Matrix
        int tempMatrix[num_processes][num_resources];       // Matrix to hold variables for turning array

        // Storing unflipped Allocation matrix in tempMatrix
        int Allocationrow = 0;
        int Allocationcol = 0;
        for (int i = matrixsize - num_processes; i < matrixsize; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                tempMatrix[Allocationrow][Allocationcol] = matrixM[i][j];
                Allocationcol++; //increment col
                //cout << matrixM[i][j] << " ";
            }
            Allocationcol=0; //reset col
            Allocationrow++; //increment row
            //cout << endl;
        }

        //Flipping tempMatrix
        for (int i = 0; i < num_resources; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                AllocationMatrix[i][j]=tempMatrix[j][i];
            }
        }

        //cout << endl;

        int RequestMatrix[num_processes][num_resources]; // Request Matrix

        // Request Matrix
        int Requestrow = 0;
        int Requestcol = 0;
        for (int i = 0; i < num_processes; ++i)
        {
            // j is initialized with matrixsize-num_processes to make j start at the columns where the resources start
            // the upper right quadrant of the given matrix M is what we want in our Request 2D array
            for (int j = matrixsize - num_processes; j < matrixsize; ++j)
            {
                RequestMatrix[Requestrow][Requestcol] = matrixM[i][j];
                Requestcol++; // increment col
                // cout<<matrixM[i][j]<<" ";
            }
            Requestcol = 0; // reset col
            Requestrow++;   // increment row
            // cout<<endl;
        }

        // SHOWING CONTENTS

        // Available Array
        cout << "Contents of Available array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            cout << "Resource " << i + 1 << ": " << ResourceUnits[i] << " units" << endl;
        }

        // Matrix M Array
        cout << "Contents of Matrix M" << endl;
        for (int i = 0; i < matrixsize; ++i)
        {
            for (int j = 0; j < matrixsize; ++j)
            {
                cout << matrixM[i][j] << " ";
            }
            cout << endl;
        }

        // Temp 2D Array
        cout << "Contents of Temp 2D Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                cout << tempMatrix[i][j] << " ";
            }
            cout << endl;
        }

        // Allocation 2D Array
        cout << "Contents of Allocation 2D Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                cout << AllocationMatrix[i][j] << " ";
            }
            cout << endl;
        }

        // Request 2D Array
        cout << "Contents of Request 2D Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                cout << RequestMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    fin.close(); // close input file

    return 0;
}