//Jonathan Flores
#include <iostream>
#include <cmath>
using namespace std;

bool ok(int q[], int c) {
   for (int i = 0; i < c; ++i)
      if (q[i] == q[c] || abs(q[i] - q[c]) == c - i)
         return false;
   return true;
}

void print(int q[], int n) {
   static int solution = 0;
   int i, j, k, l;
   typedef char box[5][7];   // box is now a data type: a 5x7 2D array of characters
   box bb, wb, *board[n][n]; // bb and wb are boxes (5x7 arrays).  board is a nxn array of pointers to boxes.
   // Fill in bb (black box) and wb (white box).  They each represent a square of the chessboard.
   // Only need to create one of each, since the chessboard can contain many pointers to the same box.
   for (i=0; i<5; i++)
      for (j=0; j<7; j++) {
         wb[i][j] = ' ';
         bb[i][j] = char(219);
      }
   
   // Create 2 more boxes to represent the queens, by drawing a picture of each queen in the 2D array.
   static box wq = { {char(219),char(219),char(219),char(219),char(219),char(219),char(219)},
                     {char(219),' '      ,char(219),' '      ,char(219),' '      ,char(219)},
                     {char(219),' '      ,' '      ,' '      ,' '      ,' '      ,char(219)},
                     {char(219),' '      ,' '      ,' '      ,' '      ,' '      ,char(219)},
                     {char(219),char(219),char(219),char(219),char(219),char(219),char(219)} };
               
   static box bq = { {' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      },
                     {' '      ,char(219),' '      ,char(219),' '      ,char(219),' '      },
                     {' '      ,char(219),char(219),char(219),char(219),char(219),' '      },
                     {' '      ,char(219),char(219),char(219),char(219),char(219),' '      },
                     {' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      } };

   // Fill board with pointers to bb and wb in alternate positions.
   for(i=0; i<n; i++)
      for(j=0; j<n; j++)
         if((i+j)%2 == 0)
            board[i][j] = &wb;
         else
            board[i][j] = &bb;
   
   // Set up the current solution on the chessboard by placing pointers to bq and wq in the appropriate squares. 
   cout << "Solution #" << ++solution << ":\n ";
   for (i=0; i<n;i++){ //replace a white or black queen on board based on what color the sqaure is
      for (j=0; j<n; j++){
         if((q[i]+i)%2==0) board [q[i]][i] = &bq; //if we are on a white sqaure then replace that sqaure with a black queen
         else board [q[i]][i] = &wq; //else we know we are in a black square so replace that sqaure with a white queen
      }
   }
   
   // Print upper border
   cout << "   ";
   for (i=0; i<n*7; i++)
      cout << '_';
   cout << "\n";

   // Print the board
   for (i=0; i<n; i++)          // for each board row
      for (k=0; k<5; k++) {     // for each box row
         cout <<"   "<<char(179);
         for (j=0; j<n; j++)    // for each board column
            for (l=0; l<7; l++) // for each box column
               // board[i][j] is the box pointer in the ith row, jth column of the board.
               // *board[i][j] is the box being pointed to.
               // (*board[i][j])[k][l] is the kth row, lth column of the box.
               cout << (*board[i][j])[k][l];
         cout << char(179) << "\n";
      }

   // Print lower border
   cout << "    ";
   for (i=0; i<n*7; i++)
      cout << char(196);
   cout << endl;
}

int main() {
   int n;
   cout << "Please enter a number: "; //modified to have user enter a number for n
   cin >> n;
   if(n < 1){
      cout << "Invalid input. Please enter a positive integer." << endl;
      return 1;
   }

   int* q = new int[n];
   int c = 0;
   q[0] = 0;
   bool foundSolutions = false; // This will check if any solutions have been found

   while (c >= 0) {  // NEXT COL:
      c++;                // Move to the next column
      if (c >= n) {          // If you have passed the last column, a solution is found
         print(q, n);      // Call the print function and backtrack
         c--;
         foundSolutions = true; // A solution has been found!
      }
      else q[c] = -1;   // set to -1 so in inner loop you can start q[c] from 0
      while (c >= 0) {  // NEXT ROW:
         q[c]++;           // Move to the next row
         if (q[c] >= n) c--;  // If you have passed the end of the row, backtrack
         else              // Otherwise, call the ok function.
            if (ok(q, c)) break; // If ok (returns true), a queen is filled in the row
      }
   }
   delete[] q;

   if (!foundSolutions){
      cout << "0 solutions found for n = " << n << endl;
   }
   return 0;
}