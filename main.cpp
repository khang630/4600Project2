/*
Course: CSCE 4600.002 Introduction to Operating Systems
Group 14: Khang Nguyen, Christelle Ndaya, Hung Nguyen
Date: 4/23/22
Descritpion: This program simulates the graph reduction algorithm to determine
whether the graph represented by M is completely reducible and hence deadlock-free.

For compilation, type "g++ main.cpp", then "./a.out". Then enter in your input.txt file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

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

        cout << endl;
        cout << "# of Processes: " << num_processes << endl;
        cout << "# of Resources: " << num_resources << endl;

        int ResourceUnits[num_resources]; // an array to hold the number of units per resource
        int Available[num_resources];     // an array that holds the amount of available units of resources

        for (int i = 0; i < num_resources - 1; ++i)
        {
            getline(fin, str, ',');
            ResourceUnits[i] = stoi(str); // assign resource units to corresponding resource in array
            // cout << str << endl;
        }

        getline(fin, str, '\n');
        ResourceUnits[num_resources - 1] = stoi(str); // assign last resource unit to last corresponding resource in array
        // cout << str << endl;

        // Resource Units Array
        cout << endl;
        cout << "Contents of Resource Units Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            cout << "Resource [" << i + 1 << "]: " << ResourceUnits[i] << " units" << endl;
        }

        // copy ResourceUnits array into Available array
        for (int i = 0; i < num_resources; ++i)
        {
            Available[i] = ResourceUnits[i];
        }

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

        // Matrix M Array
        cout << endl;
        cout << "Contents of Matrix M" << endl;
        for (int i = 0; i < matrixsize; ++i)
        {
            for (int j = 0; j < matrixsize; ++j)
            {
                cout << matrixM[i][j] << " ";
            }
            cout << endl;
        }

        int AllocationMatrix[num_processes][num_resources]; // Allocation Matrix
        int tempMatrix[num_resources][num_processes];       // Matrix to hold variables for turning array

        // Storing unflipped Allocation matrix in tempMatrix
        int Allocationrow = 0;
        int Allocationcol = 0;
        for (int i = matrixsize - num_resources; i < matrixsize; ++i)
        {
            for (int j = 0; j < num_processes; ++j)
            {
                tempMatrix[Allocationrow][Allocationcol] = matrixM[i][j];
                Allocationcol++; // increment col
                // cout << matrixM[i][j] << " ";
            }
            Allocationcol = 0; // reset col
            Allocationrow++;   // increment row
            // cout << endl;
        }

        // Flipping tempMatrix
        for (int i = 0; i < num_processes; ++i)
        {
            for (int j = 0; j < num_resources; ++j)
            {
                AllocationMatrix[i][j] = tempMatrix[j][i];
            }
        }

        // Allocation 2D Array
        cout << endl;
        cout << "Contents of Allocation 2D Array" << endl;
        for (int i = 0; i < num_processes; ++i)
        {
            for (int j = 0; j < num_resources; ++j)
            {
                cout << AllocationMatrix[i][j] << " ";
            }
            cout << endl;
        }

        // going through and finding the available resources after allocation
        for (int i = 0; i < num_processes; ++i)
        {
            for (int j = 0; j < num_resources; ++j)
            {
                if (AllocationMatrix[i][j] > 0)
                {
                    Available[j] -= AllocationMatrix[i][j]; // decrement resource unit
                }
            }
        }

        int RequestMatrix[num_processes][num_resources]; // Request Matrix

        // Request Matrix
        int Requestrow = 0;
        int Requestcol = 0;
        for (int i = 0; i < num_processes; ++i)
        {
            // j is initialized with matrixsize-num_processes to make j start at the columns where the resources start
            // the upper right quadrant of the given matrix M is what we want in our Request 2D array
            for (int j = matrixsize - num_resources; j < matrixsize; ++j)
            {
                RequestMatrix[Requestrow][Requestcol] = matrixM[i][j];
                Requestcol++; // increment col
                // cout<<matrixM[i][j]<<" ";
            }
            Requestcol = 0; // reset col
            Requestrow++;   // increment row
            // cout<<endl;
        }

        // Request 2D Array
        cout << endl;
        cout << "Contents of Request 2D Array" << endl;
        for (int i = 0; i < num_processes; ++i)
        {
            for (int j = 0; j < num_resources; ++j)
            {
                cout << RequestMatrix[i][j] << " ";
            }
            cout << endl;
        }

        // Available Array
        cout << endl;
        cout << "Contents of Available Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            cout << "Resource [" << i + 1 << "]: " << Available[i] << " available units" << endl;
        }

        //----Solving using Algorithm Reduction----
        int Worktemp[num_resources];
        bool Finishtemp[num_processes]; // intialize all processes as being finished

        // Initializng Worktemp array with Available
        for (int i = 0; i < num_resources; ++i)
        {
            Worktemp[i] = Available[i];
        }

        // Setting everything in Finishtemp to false
        for (int i = 0; i < num_processes; ++i)
        {
            Finishtemp[i] = false;
        }

        // transfer work array to vector form
        // vector<int> Work(sizeof(Worktemp) / sizeof(Worktemp[0])); // Available

        int counter = num_processes; // start off with total # of processes
        int iterations=0; //keeps track of the # of iterations through the arrays. If more than max, then it is in DEADLOCK
        int comparecounter = 0;
        int processdone = 0;           // to indicate if a process has ran
        int temparray[num_resources];  // hold request row
        int temparray2[num_resources]; // hold allocation row
        string result;                 // store result in a string message

        //this determines if the while loop has run over its maximum. If it does, it means that the graph is in DEADLOCK
        int n = num_processes;
        // apply n(n-1)/2 for sequence of numbers ...5+4+3+2+1
        int max = ((n + 1) * n) / 2;

        while (1) // infinite loop
        { 
            if (iterations > max+1) //+1 to account for the extra iteration that triggers this if condition
            {
                result = "DEADLOCKED!!";
                break; // break out of the infinite loop
            }
            
            counter = counter % num_processes; // keep looping numbers
            if (processdone == num_processes)
            {
                result = "DEADLOCK FREE!!";
                break; // break out of the infinite loop
            }

            if (Finishtemp[counter] == false) // if a prcoess still has not finished yet
            {
                comparecounter = 0;
                for (int i = 0; i < num_resources; ++i)
                {
                    temparray[i] = RequestMatrix[counter][i]; // get Request row info and put in temparray
                }
                // vector<int> tempvector(sizeof(temparray) / sizeof(temparray[0])); // turn temparray into vector

                for (int i = 0; i < num_resources; ++i)
                {
                    if (temparray[i] <= Worktemp[i])
                    {
                        comparecounter++;
                    }
                }

                if (comparecounter == num_resources) // if request vector is <= work vector, than that process is able to run
                {
                    for (int i = 0; i < num_resources; ++i)
                    {
                        temparray2[i] = AllocationMatrix[counter][i]; // get Request row info and put in temparray
                    }

                    for (int i = 0; i < num_resources; ++i)
                    {
                        Worktemp[i] = Worktemp[i] + temparray2[i]; // get Request row info and put in temparray
                    }

                    Finishtemp[counter] = true; // indicate that the process has ran and is finished
                    processdone++;              // indicate that a process is done and increment
                }
            }

            counter++; // increment counter
            iterations++; //increment iterations
        }

        // Finish Array
        cout << endl;
        cout << "Contents of Finishtemp Array" << endl;
        for (int i = 0; i < num_processes; ++i)
        {
            cout << Finishtemp[i] << " ";
        }

        // Final Availble Array
        cout << endl;
        cout << endl;
        cout << "Contents of End Available Array" << endl;
        for (int i = 0; i < num_resources; ++i)
        {
            cout << Worktemp[i] << " ";
        }

        cout << endl;
        cout << endl;
        cout << result << endl;
        cout << endl;
    }
    fin.close(); // close input file

    return 0;
}