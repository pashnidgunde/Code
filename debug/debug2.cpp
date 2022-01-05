#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

int determinant(std::vector<std::vector<int>> matrix, int n) {
   int det = 0;
   std::vector<std::vector<int>> submatrix(n, std::vector<int>(n, 0));
   if (n == 2)
   return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
   else {
      for (int x = 0; x < n; x++) {
         int subi = 0;
         for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
               if (j == x)
               continue;
               submatrix[subi][subj] = matrix[i][j];
               subj++;
            }
            subi++;
         }
         det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
      }
   }
   return det;
}

string MatrixChallenge(string strArr[], int arrLength) {
  
  int pos = 0;
  for (int i=0; i< arrLength; i++)
  {
      if (strArr[i] == "<>")
      {
        pos = i;
        break;
      }
  }

  std::vector<std::vector<int>> matrix(pos, std::vector<int>(pos,0));
  //std::vector<std::vector<int>> matrix;
  int index = 0;

  for (int i=0; i<pos; i++)
  {
    std::vector<int> v;
    for (int j=0; j<pos;j++)
    {
      matrix[i][j] = std::atoi(strArr[index].c_str());
      index++;
    }
    index++;
  }
  

  // code goes here  
  auto d = determinant(matrix, pos);
  std::cout << "Determinant : " << d << std::endl;
  
  std::stringstream ss;
  ss << d;
  return ss.str();

}


int main(void) { 
   
  // keep this function call here
  {
    string A[] = {"5","0","<>","0","5"};
    int arrLength = sizeof(A) / sizeof(*A);
    cout << MatrixChallenge(A, arrLength);
  }
  
  {
    string A[] = {"1","2","4","<>","2","1","1","<>","4","1","1"};
    int arrLength = sizeof(A) / sizeof(*A);
    cout << MatrixChallenge(A, arrLength);
  }

  return 0;
    
}
