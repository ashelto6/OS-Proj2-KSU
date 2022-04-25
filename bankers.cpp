/*
Antonio Shelton-McGaha
OS Project 2
*/

#include <iostream>
#include <string>
#include <fstream>

int main()
{

    std::ifstream inFile;
    inFile.open("input.txt");

    const int numOfProcesses = 5; // Number of processes
    const int numOfResults = 3; // Number of resources

    int allocation[numOfProcesses][numOfResults];
 
    int max[numOfProcesses][numOfResults];

    int avail[numOfResults];
 
    std::string line;
    getline(inFile, line);

    //populates 2D allocation array
    for (int i = 0; i < numOfProcesses; ++i)
        for(int j = 0; j < numOfResults; ++j)
            inFile >> allocation[i][j];

    //populated 2D max array
    for (int i = 0; i < numOfProcesses; ++i)
        for(int j = 0; j < numOfResults; ++j)
            inFile >> max[i][j];   

    for(int i = 0; i < numOfResults; ++i)
        inFile >> avail[i];

    inFile.close();


    int finish[numOfProcesses]; 
    int seq[numOfProcesses];
    int seqIndex = 0;
    
    for( int i = 0; i < numOfProcesses; ++i )
        finish[i] = 0;

    int need[numOfProcesses][numOfResults];
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
                    { 
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

  int flag = 1;

  //safe or unsafe?
  for( int i = 0; i < numOfProcesses; ++i )
  {
        if( !finish[i] )
        {
            flag = 0;
            std::cout << "Sequence is not safe\n";
            break;
        }
  }
 
  //if safe sequence print the order of processes
  if( flag == 1 )
  {
    std::cout << "Safe Sequence -> ";

    for( int i = 0; i < numOfProcesses - 1; ++i )
        std::cout << "P" << seq[i] << ", ";

    std::cout << "P" << seq[numOfProcesses - 1] << "\n";
  }
}
