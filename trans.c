/*                                                                                          
 * trans.c - Matrix transpose B = A^T                                                       
 *                                                                                          
 * Each transpose function must have a prototype of the form:                               
 * void trans(int M, int N, int A[N][M], int B[M][N]);                                      
 *                                                                                          
 * A transpose function is evaluated by counting the number of misses                       
 * on a 1KB direct mapped cache with a block size of 32 bytes.                              
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*                                                                                          
 * transpose_submit - This is the solution transpose function that you                      
 *     will be graded on for Part B of the assignment. Do not change                        
 *     the description string "Transpose submission", as the driver                         
 *     searches for that string to identify the transpose function to                       
 *     be graded.                                                                           
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  int blocksize;

  int i;
  int j;
  int row;
  int column;
  int diagonal;

  int temp = 0;
  int holder = 0;


  if (M == 32 && N == 32) {
    blocksize = 8;
    for (column =0; column < N; column+=blocksize) {
      for (row = 0; row < M; row += blocksize) {
        for (j = row; j < row + blocksize; ++j) {
          for (i = column; i < column + blocksize; ++i) {
            if (j != i) {
              B[i][j] = A[j][i];
            }else {
              temp = A[j][i];
              diagonal = j;
              holder = 1;
                             }
          }
          if (column == row) {
            B[diagonal][diagonal] = temp;
          }
        }
      }
    }
  }
  if (M == 64 && N == 64) {
    blocksize = 4;
    for (column = 0; column < M; column += blocksize) {
      for (row = 0; row < N; row += blocksize) {
        for (i = row; i < row + blocksize; i++) {
        for (j = column; j < column + blocksize; j++) {
          if (i !=j) {
            B[j][i] = A[i][j];
          } else {
            temp = A[i][j];
            diagonal = i;
            holder = 1;
          }
        }
          if (column == row) {
            B[diagonal][diagonal] = temp;
          }
        }
      }
    }
  }
  if (M == 64 && N == 64) {
    blocksize = 4;
    for (column = 0; column < M; column += blocksize) {
      for (row = 0; row < N; row += blocksize) {
        for (i = row; i < row + blocksize; i++) {
        for (j = column; j < column + blocksize; j++) {
          if (i !=j) {
            B[j][i] = A[i][j];
          } else {
            temp = A[i][j];
            diagonal = i;
            holder = 1;
          }
        }
        if (holder == 1) {
          B[diagonal][diagonal] = temp;
          holder = 0;
        }
      }
    }
  }
  }
  if (M == 61 && N == 67) {
    blocksize = 20;
    for (column = 0; column < N; column +=blocksize) {
      for (row = 0; row < M; row += blocksize) {
        for (i = row; i < row + blocksize; i++) {
          for (j = column; j < column + blocksize; j++) {
            if (i > 66 || j > 60) {
              continue;
            } else {
              B[j][i] = A[i][j];
            }
          }
        }
      }
    }
  }
*                                                                                          
 * You can define additional transpose functions below. We've defined                       
 * a simple one below to help you get started.                                              
 */

/*                                                                                          
 * trans - A simple baseline transpose function, not optimized for the cache.               
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}
/*                                                                                          
 * You can define additional transpose functions below. We've defined                       
 * a simple one below to help you get started.                                              
 */

/*                                                                                          
 * trans - A simple baseline transpose function, not optimized for the cache.               
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*                                                                                          
 * registerFunctions - This function registers your transpose                               
 *     functions with the driver.  At runtime, the driver will                              
 *     evaluate each of the registered functions and summarize their                        
 *     performance. This is a handy way to experiment with different                        
 *     transpose strategies.                                                                
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);
    registerTransFunction(trans, trans_desc);
}

/*                                                                                          
 * is_transpose - This helper function checks if B is the transpose of                      
 *     A. You can check the correctness of your transpose by calling                        
 *     it before returning from the transpose function.                                     
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
