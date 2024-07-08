#include <iostream>

// Node class to represent an element in the sparse matrix
class MatrixNode {
public:
    int rowIdx;         // Row index of the element
    int colIdx;         // Column index of the element
    int elementValue;   // Value of the element
    MatrixNode* nextNode; // Pointer to the next node in the list

    // Initializing a matrix node with given row, column, and value
    MatrixNode(int row, int col, int value) : rowIdx(row), colIdx(col), elementValue(value), nextNode(nullptr) {}
};

// SparseMatrix class for managing the sparse matrix with a linked list
class SparseMatrix {
private:
    MatrixNode* headNode; // Head node of the linked list
    int totalRows;        // Total number of rows in the matrix
    int totalCols;        // Total number of columns in the matrix

public:
    // Initializing a sparse matrix with specified dimensions
    SparseMatrix(int rows, int cols) : headNode(nullptr), totalRows(rows), totalCols(cols) {}

    // Adding an element to the sparse matrix if it's non-zero
    void addElement(int row, int col, int value) {
        if (value == 0) return; // Skipping zero values

        // Creating a new node for the element
        MatrixNode* newNode = new MatrixNode(row, col, value);

        // If the list is empty, set the new node as the head node
        if (!headNode) {
            headNode = newNode;
        } else {
            // Otherwise, traverse to the end of the list and insert the new node
            MatrixNode* currentNode = headNode;
            while (currentNode->nextNode) {
                currentNode = currentNode->nextNode;
            }
            currentNode->nextNode = newNode;
        }
    }

    // Retrieving the value of an element at a specific position
    int fetchElementValue(int row, int col) {
        // Start from the head node and search for the element
        MatrixNode* currentNode = headNode;
        while (currentNode) {
            if (currentNode->rowIdx == row && currentNode->colIdx == col) {
                return currentNode->elementValue; // Return the value if found
            }
            currentNode = currentNode->nextNode; // Move to the next node
        }
        return 0; // Return zero if the element is not found
    }

    // Printing the entire matrix with values at their positions
    void displayMatrixElements() {
        // Iterate through each row and column, and print the corresponding element value
        for (int i = 0; i < totalRows; ++i) {
            for (int j = 0; j < totalCols; ++j) {
                std::cout << fetchElementValue(i, j) << " ";
            }
            std::cout << std::endl; // New line at the end of each row
        }
    }

    // Cleaning up the linked list by deleting all nodes
    ~SparseMatrix() {
        MatrixNode* currentNode = headNode;
        while (currentNode) {
            MatrixNode* tempNode = currentNode;
            currentNode = currentNode->nextNode;
            delete tempNode; // Deleting each node
        }
    }
};

// Main function to interact with the user and manage the sparse matrix
int main() {
    int matrixRows, matrixCols;
    std::cout << "Enter the number of rows and columns in the matrix: ";
    std::cin >> matrixRows >> matrixCols;

    // Creating a sparse matrix with specified dimensions
    SparseMatrix sparseMatrix(matrixRows, matrixCols);
    int userChoice;

    do {
        // Displaying menu options to the user
        std::cout << "Sparse Matrix Menu:\n";
        std::cout << "1. Add Element\n";
        std::cout << "2. Fetch Element Value\n";
        std::cout << "3. Display Matrix Elements\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1: {
            int rowIdx, colIdx, elementValue;
            std::cout << "Enter row, column, and value: ";
            std::cin >> rowIdx >> colIdx >> elementValue;
            sparseMatrix.addElement(rowIdx, colIdx, elementValue); // Adding an element to the matrix
            break;
        }
        case 2: {
            int rowIdx, colIdx;
            std::cout << "Enter row and column: ";
            std::cin >> rowIdx >> colIdx;
            int elementValue = sparseMatrix.fetchElementValue(rowIdx, colIdx); // Fetching the value of an element
            std::cout << "Value at (" << rowIdx << ", " << colIdx << "): " << elementValue << std::endl;
            break;
        }
        case 3:
            std::cout << "Matrix elements:\n";
            sparseMatrix.displayMatrixElements(); // Displaying all elements in the matrix
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (userChoice != 4); // Continue until the user chooses to exit

    return 0;
}
