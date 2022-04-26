/*
Antonio Shelton-McGaha
OS Project 2
*/

#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream in("input.txt");

    const int numOfProcesses = 5; // # of proc
    const int numOfResults = 3; // # of res

    int allocation[numOfProcesses][numOfResults];
    int max[numOfProcesses][numOfResults];
    int accessible[numOfResults];
 
    std::string line;
    getline(in, line);

    //populates 2D allocation array
    for( int i = 0; i < numOfProcesses; ++i )
        for( int j = 0; j < numOfResults; ++j )
            in >> allocation[i][j];

    //populated 2D max array
    for( int i = 0; i < numOfProcesses; ++i )
        for( int j = 0; j < numOfResults; ++j )
            in >> max[i][j];   

    for( int i = 0; i < numOfResults; ++i )
        in >> accessible[i];

    in.close();
    
    int finish[numOfProcesses]; 
    for( int i = 0; i < numOfProcesses; ++i )
        finish[i] = 0;

    int required[numOfProcesses][numOfResults];
    for( int i = 0; i < numOfProcesses; ++i ) 
    {
        for( int j = 0; j < numOfResults; ++j )
            required[i][j] = max[i][j] - allocation[i][j];
    }

    int sequenceIdx = 0;
    int sequence[numOfProcesses];
    for( int k = 0; k < 5; ++k ) 
    {
        for( int i = 0; i < numOfProcesses; ++i ) 
        {
            if( !finish[i] ) 
            {
                int flag = 0;
                for( int j = 0; j < numOfResults; ++j ) 
                {
                    if( required[i][j] > accessible[j] )
                    { 
                        flag = 1;
                        break;
                    }
                }

                if( !flag ) 
                {
                    sequence[sequenceIdx++] = i;

                    for( int y = 0; y < numOfResults; ++y )
                        accessible[y] += allocation[i][y];

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
        std::cout << "P" << sequence[i] << ", ";

    std::cout << "P" << sequence[numOfProcesses - 1] << "\n";
  }
}
