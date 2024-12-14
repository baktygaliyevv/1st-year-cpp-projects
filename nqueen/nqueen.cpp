/**Report 
The presented code solves an n-Queen problem, the goal of which is to place as many ladies as possible on a nxn board, where n is specified by the user. 
To implement this problem, I used a depth first search algorithm, which allows to solve this problem efficiently. To perform this task a lot of functions were involved. 
The functions checkrow, checkcolumn, checkdiagonal1 and checkdiagonal2 speak for themselves, they check a certain part of the chessboard (row, diagonal etc.), whether the 
queen can be placed and return a boolean result (true or false). The isSafe function is an important part of the code because it checks all the above-mentioned functions 
to make sure the queen is safe in a certain area of the board. This function, as well as those mentioned above, returns a boolean result (true or false). 
The solveNQueens function uses the DFS algorithm to safely place the queen on the chessboard. If the queen can be located safely, the function calls itself 
through recursion to continue the placement process. If the queen cannot be placed safely, the function goes back and tries the next row in the same column. 
If all possible rows have been tried and no queen has been placed on them, the function returns false, if so, it returns true. The printboard function is needed 
to print the result to the console. It looks at each cell of the board and prints the unicode symbol of the queen if there is a queen in that cell, if not, it prints 
the unicode symbol of empty square. The main function asks the user to enter a number (n) which is the size of the chessboard and will search for a solution and output 
it to the console. If the user enters an invalid input(text), he will receive an error: “Invalid input. Please enter a number.” If the user has entered a number less than 4, 
he will also receive an error: “Invalid input. Please enter a number that is greater than or equal to 4.”
  */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;
/**
  * bool checkRow(vector<vector<int>>& board, int row, int col)
  * Summary:
  *    The checkRow function checks if there are any 1's in the given row of the board.
  * Parameters:
       row: integer representing the row
       col: integer representing the columns in the board
       board: vector of vectors representing the board
  * Return Value: A boolean value of true if there are no 1's in the row, false otherwise.
  * Description:
  *    The checkRow function checks if there are any queens in the given row of the 
  *    board by iterating through the row and checking if there are any 1's. If there are, it returns false,     
  *    indicating that the row is not valid. If there are no 1's in the row, it returns true, 
  *    indicating that the row is valid.
  */
bool checkRow(vector<vector<int>>& board, int row, int col) {
  for (int i = 0; i < col; i++) {
    if (board[row][i] == 1) {
      return false;
    }
  }
  return true;
}
 /**
  * bool checkColumn(vector<vector<int>>& board, int row, int col)
  * Summary:
  *    The checkColumn function checks if there are any 1's in the given column of the board.
  * Parameters:
       row: integer representing the row
       col: integer representing the columns in the board
       board: vector of vectors representing the board
  * Return Value: A boolean value of true if there are no 1's in the column, false otherwise.
  * Description:
  *    The checkColumn function checks if there are any queens in the given column of the 
  *    board by iterating through the column and checking if there are any 1's. If there are, it returns false,     
  *    indicating that the column is not valid. If there are no 1's in the column, it returns true, 
  *    indicating that the column is valid.
  */
bool checkColumn(vector<vector<int>>& board, int row, int col) {
  for (int i = 0; i < row; i++) {
    if (board[i][col] == 1) {
      return false;
    }
  }
  return true;
}
 /**
  * bool checkDiagonal1(vector<vector<int>>& board, int row, int col)
  * Summary:
  *    The checkDiagonal1 function checks if there are any 1's in the first diagonal of the board starting from the given row and column.
  * Parameters:
       row: integer representing the row to start checking the diagonal from
       col: integer representing the column to start checking diagonal from
       board: vector of vectors representing the board
  * Return Value: A boolean value of true if there are no 1's in the diagonal, false otherwise.
  * Description:
  *    The checkDiagonal1 function checks if there are any queens in the first diagonal of the 
  *    board by iterating through the diagonal and checking if there are any 1's. If there are, it returns false,     
  *    indicating that the diagonal is not valid. If there are no 1's in the diagonal, it returns true, 
  *    indicating that the diagonal is valid.
  */
bool checkDiagonal1(vector<vector<int>>& board, int row, int col) {
  int i, j;
  for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j] == 1) {
      return false;
    }
  }
  for (i = row, j = col; i < board.size() && j < board.size(); i++, j++) {
    if (board[i][j] == 1) {
      return false;
    }
  }
  return true;
}
 /**
  * bool checkDiagonal2(vector<vector<int>>& board, int row, int col)
  * Summary:
  *    The checkDiagonal2 function checks if there are any 1's in the second diagonal of the board starting from the given row and column.
  * Parameters:
       row: integer representing the row to start checking the diagonal from
       col: integer representing the column to start checking diagonal from
       board: vector of vectors representing the board
  * Return Value: A boolean value of true if there are no 1's in the diagonal, false otherwise.
  * Description:
  *    The checkDiagonal2 function checks if there are any queens in the second diagonal of the 
  *    board by iterating through the diagonal and checking if there are any 1's. If there are, it returns false,     
  *    indicating that the diagonal is not valid. If there are no 1's in the diagonal, it returns true, 
  *    indicating that the diagonal is valid.
  */
bool checkDiagonal2(vector<vector<int>>& board, int row, int col) {
  int i, j;
  for (i = row, j = col; i >= 0 && j < board.size(); i--, j++) {
    if (board[i][j] == 1) {
      return false;
    }
  }
  for (i = row, j = col; i < board.size() && j >= 0; i++, j--) {
    if (board[i][j] == 1) {
      return false;
    }
  }
  return true;
}
 /**
  * bool isSafe(vector<vector<int>>& board, int row, int col)
  * Summary:
  *    The isSafe function checks if a queen can be placed safely on the board at the given row and column.
  * Parameters:
       row: integer representing the row
       col: integer representing the columns in the board
       board: vector of vectors representing the board
  * Return Value:
  *    A boolean value of true if it is safe to place a queen at the given row and column, false otherwise.
  * Description:
  *    The isSafe function checks if it is safe to place a queen at the given row and column on the board by
  *    calling the checkRow, checkColumn, checkDiagonal1, and checkDiagonal2 functions. If all of these functions
  *    return true, indicating that there are no conflicts with the placement of the queen, then isSafe returns true.
  *    Otherwise, it returns false.
  */
bool isSafe(vector<vector<int>>& board, int row, int col) {
  return checkRow(board, row, col) && checkColumn(board, row, col) && checkDiagonal1(board, row, col) && checkDiagonal2(board, row, col);
}
/**
 * bool solveNQueens(vector<vector<int>>& board, int col)
 * Summary:
 *   The solveNQueens function solves the N-Queens problem by recursively placing queens on the board
 *   and checking if they can be placed safely.
 * Parameters:
     row: integer representing the row
     board: vector of vectors representing the board
     col: integer representing the column to place the queen in
 * Return Value:
 *   A boolean value of true if it is possible to place all the queens safely on the board, false otherwise.
 * Description:
 *   The solveNQueens function uses a DFS algorithm to solve the N-Queens problem. It starts by placing a queen
 *   in the first column of the board and checks if it can be placed safely using the isSafe function. If the queen
 *   can be placed safely, the function recursively calls itself to place the next queen in the next column. If a
 *   queen cannot be placed safely, the function backtracks and tries a different row in the current column. If all
 *   possible rows have been tried and no queen can be placed safely in the current column, the function returns false.
 *   If all the queens have been placed safely on the board, the function returns true.
 */
bool solveNQueens(vector<vector<int>>& board, int col) {
  if (col >= board.size()) {
    return true;
  }
  for (int row = 0; row < board.size(); row++) {
    if (isSafe(board, row, col)) {
      board[row][col] = 1;
      if (solveNQueens(board, col + 1)) {
        return true;
      }
      board[row][col] = 0;
    }
  }
  return false;
}
/**
 * void printBoard(vector<vector<int>>& board)
 * Summary:
 *   The printBoard function prints the N-Queens board to the console.
 * Parameters:
     col: integer representing the column to place the queen in
 * Return Value: None
 * Description:
 *   The printBoard function prints the current state of the N-Queens board to the console, 
 *   where a queen is represented by the unicode symbol for a queen (u8"\u2655 ") and an empty square
 *   is represented by the unicode symbol for an empty square (u8"\u25A1 ").
 *   The function iterates over each cell in the board and prints the appropriate symbol based on
 *   whether or not a queen is present in that cell.
 */
void printBoard(vector<vector<int>>& board) {
  const char* queen = u8"\u2655 ";
  const char* empty = u8"\u25A1 "; 
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board.size(); j++) {
      if (board[i][j] == 1) {
        cout << queen;
      } 
      else {
        cout << empty;
      }
    }
    cout << endl;
  }
  cout << endl;
}
// Use that printBoard function instead, if the unicode symbols are not shown.
// void printBoard(vector<vector<int>>& board) {
//   for (int i = 0; i < board.size(); i++) {
//     for (int j = 0; j < board.size(); j++) {
//       if (board[i][j] == 1) {
//         cout << "Q";
//       } 
//       else {
//         cout << ".";
//       }
//     }
//     cout << endl;
//   }
//   cout << endl;
// }
/**
 * int main()
 * Summary:
 *   The main function drives the execution of the N-Queens program by prompting the user 
 *   for input, initializing the chessboard, and calling the solveNQueens and printBoard functions.
 * Parameters: none
 * Return Value: 
 *   An integer value representing the exit status of the program
 * Description:
 *   The main function prompts the user to enter the size of the chessboard and initializes a vector of vectors
 *   representing the chessboard. It then calls the solveNQueens function to solve the N-Queens
 *   problem and the printBoard function to print the solution to the console. If no solution is found, the 
 *   program prints a message indicating that no solution was found.
 *   The function returns 0 upon successful completion of the program.
 */
int main() {
  int n;  
  do {
    cout << "Enter the size of the chesssboard: ";
    cin >> n;
    if (cin.fail()) {
      cout << "Invalid input. Please enter a number" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (n < 4) {
      cout << "Invalid input. Please enter a number that is greater than or equal to 4." << endl;
    }
    else {
      break;
    }
  } while (true);
  vector<vector<int>> board(n, vector<int>(n, 0));
  if (solveNQueens(board, 0)) {
    cout << "Solution:\n";
    printBoard(board);
  } 
  else {
    cout << "No solution found.\n";
  }   
  return 0;
}
