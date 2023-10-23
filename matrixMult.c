
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------

double *input_matrix(int *rows, int *columns, char *matrixIdentifier){

// prompting the user for their dimensions and checking that they are valid

	do {
		printf("How many rows for %s?    ", matrixIdentifier);
		scanf("%d", rows);
   			 if (*rows == 0){
     				 printf("Invalid number of rows.\n");
   			 }
	} while (*rows == 0);

	do {
		printf("How many columns for %s? ", matrixIdentifier);
		scanf("%d", columns);
			if (*columns == 0){
      				printf("Invalid number of columns.\n");
    			}
	} while (*columns == 0);

// dynamically allocating memory from the heap
	double *matrix = malloc(*rows * *columns * sizeof(double));

	if (matrix == NULL){
		printf("Malloc error.\n");
		return NULL;
	}

// reading the values into the memory using row major ordering for the matrix values
	int counter = 1;
	for (int i = 0; i < *rows; i++){
		for (int j = 0; j < *columns; j++){
			matrix[i *(*columns) + j] = counter++;
		}
	}
	
	return matrix;
}
//-----------------------------------------------------------------------------

int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2, int m2_rows, int m2_columns, double *m3){

// rules of matrix multiplication: matrix1 must have same num columns as matrix2 has rows

// checking that the dimensions are appropriate for matrix multiplication
	if (m1_columns != m2_rows){
		return 0;
	}

// Multiplying the two matrices together and putting the result into another dynamically allocated piece of memory 
	for (int i = 0; i < m1_rows; i++){
		for (int j = 0; j < m2_columns; j++){
			m3[i * m2_columns + j] = 0;
			for (int k = 0; k < m1_columns; k++){
				m3[i * m2_columns + j] += m1[i * m1_columns + k] * m2[k * m2_columns + j];
			}
		}
	}
 
	return 1;
}
//-----------------------------------------------------------------------------

void output_matrix(double *matrix, int rows, int columns){

// Outputs the two input and the result matrices	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf("%lf ", matrix[i * columns + j]);
		}

		printf("\n");

	}
}
//-----------------------------------------------------------------------------

int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}

//-----------------------------------------------------------------------------

