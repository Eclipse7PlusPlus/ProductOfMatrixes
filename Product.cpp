#include <iostream>
#include <iomanip>
#include <random>
#include <stdexcept>

void InputSize(int32_t&, int32_t&);
void InputMatrix(int32_t**, int32_t, int32_t);
void ProductOfMatrix(int32_t**, int32_t**, int32_t, int32_t, int32_t, int32_t);
void DeleteMatrix(int32_t**, int32_t);


int main() {
    try {
        // For first matrix
        int32_t columnsfirst = 0;
        int32_t rowsfirst = 0;
        int32_t rowssecond = 0;
        int32_t columnssecond = 0;
        
        InputSize(columnsfirst, rowsfirst);
        int32_t** matrixfirst = new int32_t*[rowsfirst];
        for (int i = 0; i < rowsfirst; ++i) {
            matrixfirst[i] = new int32_t[columnsfirst];
        }
        InputMatrix(matrixfirst, columnsfirst, rowsfirst);

        // For second matrix
        InputSize(columnssecond, rowssecond);
        int32_t** matrixsecond = new int32_t*[rowssecond];
        for (int i = 0; i < rowssecond; ++i) {  
            matrixsecond[i] = new int32_t[columnssecond];
        }
        InputMatrix(matrixsecond, columnssecond, rowssecond);

        // Result        
        ProductOfMatrix(matrixfirst, matrixsecond, rowsfirst, columnsfirst, rowssecond, columnssecond);
        
        // Deletion 
        DeleteMatrix(matrixfirst, rowsfirst);
        DeleteMatrix(matrixsecond, rowssecond);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

void InputSize(int32_t& columns, int32_t& rows) {
    std::cout << "Enter number of columns: ";
    std::cin >> columns;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;

    if (columns <= 0 || rows <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
}

void InputMatrix(int32_t** matrix, int32_t columns, int32_t rows) {
    std::cout << "Matrix elements:" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dis(-100, 100);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = dis(gen);
            std::cout << std::setw(6) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void ProductOfMatrix(int32_t** matrixfirst, int32_t** matrixsecond, 
                    int32_t rowsfirst, int32_t columnsfirst, 
                    int32_t rowssecond, int32_t columnssecond) {
    if (columnsfirst != rowssecond) {
        throw std::invalid_argument("Invalid arguments of rows and columns");
    }
    
    int32_t** matrixresult = new int32_t*[rowsfirst];
    for (int i = 0; i < rowsfirst; ++i) {
        matrixresult[i] = new int32_t[columnssecond];
    }
    
    for (int i = 0; i < rowsfirst; ++i) {
        for (int j = 0; j < columnssecond; ++j) {
            matrixresult[i][j] = 0;
            for (int k = 0; k < columnsfirst; ++k) {
                matrixresult[i][j] += matrixfirst[i][k] * matrixsecond[k][j];
            }
        }
    }
    
    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < rowsfirst; ++i) {
        for (int j = 0; j < columnssecond; ++j) {
            std::cout << std::setw(6) << matrixresult[i][j];
        }
        std::cout << std::endl;
    }
    
    DeleteMatrix(matrixresult, rowsfirst);
                    }

 void DeleteMatrix(int32_t** matrix, int32_t rows) {
for (int i = 0; i < rows; ++i){
 delete[] matrix[i];
     }
 delete[] matrix;
 }                  
