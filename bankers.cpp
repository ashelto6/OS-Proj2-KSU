//Antonio Shelton-McGaha
//OS Project 2
//4/21/2022

#include <iostream>
#include <fstream>
#include <string>

int main()
{

    std::ifstream inFile;
    inFile.open("input.txt");

    const int numOfProcesses = 5; // Number of processes
    const int numOfResults = 3; // Number of resources

    int allocation[numOfProcesses][numOfResults]; //Allocation Matrix
 
    int max[numOfProcesses][numOfResults]; //Max Matrix

    int avail[numOfResults]; //Available Resources Matrix
 
    std::string line;
    getline(inFile, line);

    //fills alloc[][] from txt file
    for (int i = 0; i < numOfProcesses; ++i)
        for(int j = 0; j < numOfResults; ++j)
            inFile >> allocation[i][j];

    //fills max[][] from txt file
    for (int i = 0; i < numOfProcesses; ++i)
        for(int j = 0; j < numOfResults; ++j)
            inFile >> max[i][j];   

    for(int i = 0; i < numOfResults; ++i)
        inFile >> avail[i];

    inFile.close();


    int finish[numOfProcesses]; 
    int seq[numOfProcesses];    //stores the correct safe sequence
    int seqIndex = 0;

    //initializes finish array values to 0 
    for( int i = 0; i < numOfProcesses; ++i )
        finish[i] = 0;

    int need[numOfProcesses][numOfResults]; //stores the values for how many resources each process is requesting
    for( int i = 0; i < numOfProcesses; ++i ) 
    {
        for( int j = 0; j < numOfResults; ++j )
            need[i][j] = max[i][j] - allocation[i][j];
    }

    for( int k = 0; k < 5; ++k ) 
    {
        for( int i = 0; i < numOfProcesses; ++i ) 
        {
            if ( !finish[i] ) 
            {
                int flag = 0;
                for (int j = 0; j < numOfResults; ++j) 
                {
                    if (need[i][j] > avail[j])
                    { //if a process needs more resources than are available
                        flag = 1;
                        break;
                    }
                }

                if ( !flag ) 
                {
                    seq[seqIndex++] = i;

                    for( int y = 0; y < numOfResults; ++y )
                        avail[y] += allocation[i][y];

                    finish[i] = 1;
                }
            }
        }
    }

  int flag = 1; //if flag is 0, the sequence is not safe; if 1, sequence is safe

  // checks if sequence is safe or not
  for( int i = 0; i < numOfProcesses; ++i )
  {
        if( !finish[i] )
        {
            flag = 0;
            std::cout << "Sequence is not safe\n";
            break;
        }
  }
 
  //if sequence is safe it prints the order 
  if( flag == 1 )
  {
    std::cout << "Safe Sequence -> ";

    for( int i = 0; i < numOfProcesses - 1; ++i )
        std::cout << "P" << seq[i] << ", ";

    std::cout << "P" << seq[numOfProcesses - 1] << "\n";
  }
}