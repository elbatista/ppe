/* ***************************************************************************
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  As a special exception, you may use this file as part of a free software
 *  library without restriction.  Specifically, if other files instantiate
 *  templates or use macros or inline functions from this file, or you compile
 *  this file and link it with other files to produce an executable, this
 *  file does not by itself cause the resulting executable to be covered by
 *  the GNU General Public License.  This exception does not however
 *  invalidate any other reasons why the executable file might be covered by
 *  the GNU General Public License.
 *
 ****************************************************************************
 *  Authors: Dalvan Griebler <dalvangriebler@gmail.com>
 *         
 *  Copyright: GNU General Public License
 *  Description: This is a simple matrix multiplication algorithm. 
 *  File Name: matrix_multi.cpp
 *  Version: 1.0 (25/05/2018)
 *  Compilation Command: g++ -std=c++1y matrix_multi.cpp -o exe
 ****************************************************************************
*/

#include <iostream>
#include <chrono>
#include "tbb/tbb.h"

//Matrix sizes
#define MX 8

//all the matrix
long int **matrix1, **matrix2, **matrix;

void val(){
	long int i, j;
	for(i=0; i<MX; i++){
		for(j=0; j<MX; j++){
			matrix1[i][j]	= i+1;
			matrix2[i][j]	= j+1;
			matrix[i][j]	= 0;
		}
	}	
}

void printMatrix(long int **matrix){
	int i, j;
	for(i=0; i<MX; i++){
		printf("\n");
		for(j=0; j<MX; j++){
			printf("%ld ", matrix[i][j]);
		}
	}
	printf("\n");				
}

//matrix multiplication algorithm
void multiply(){
	
	int i, j;

	for(long i=0; i<MX; i++){
		for(long j=0; j<MX; j++){

			//criação de uma função lambda com particionamento blocked_range
			//auto bodyF = [i,j](const tbb::blocked_range<int> &r, int in) -> void {
			//	for(int i2 = r.begin(); i2 < r.end(); ++i2){
			//		matrix[i][j] += (matrix1[i][i2] * matrix2[i2][j]);
			//	}
			//	return;
			//};

			//tbb::parallel_for(tbb::blocked_range<int>(0, MX), bodyF);

			for(long int k=0; k<MX; k++){
				matrix[i][j] += (matrix1[i][k] * matrix2[k][j]);
			}
		}
	}
}

//main function
int main(int argc, char const *argv[]){

	matrix = new long int*[MX];  
	matrix1 = new long int*[MX];
	matrix2 = new long int*[MX];

	for (long int i=0; i < MX; i++){
	    matrix[i] = new long int[MX];
	    matrix1[i] = new long int[MX];
	    matrix2[i] = new long int[MX];
	}

	//tbb::task_scheduler_init init(4); //inicialização com numero de workers
	
	//assigning fixed values to the matrix
	val();

	//matrix multiplication algorithm call
	multiply();
	
	printf("SIZE OF MATRICES = %d\n", MX);

	//printing the resultant matrix (you may comment when bigger sizes will be set-up)
	printMatrix(matrix1);
	printMatrix(matrix2);
	printMatrix(matrix);

	delete matrix;
	delete matrix1;
	delete matrix2;
}
