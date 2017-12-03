#include <iostream>
#include <vector>
using namespace std;
class Matrix
{
	vector< vector <float>> grid;
	int width, height;
public:
	Matrix(vector< vector <float>>);
	Matrix multiply(Matrix);
	Matrix transpose();
	void printMatrix();
};
Matrix zeros(int, int);
float dotProduct(vector<float>, vector<float>);

Matrix::Matrix(vector< vector <float>> m_grid)
{
	grid = m_grid;
	height = m_grid.size();
	width = m_grid[0].size();
}

Matrix Matrix::multiply(Matrix b)
{
	//error handling
	if (width != b.height) {
		throw "Cannot multiply the two matrices. Number of columns in the first matrix must be equal to the number of rows in the second";
	}

	Matrix product = zeros(height,b.width);
	Matrix b_T = b.transpose();

	for (int row1 = 0; row1 < height; row1++) {
		vector <float> currentRow;
		for (int row2 = 0; row2 < b_T.height; row2++) {
			currentRow.push_back(dotProduct(grid[row1], b_T.grid[row2]));
		}
		product.grid[row1] = currentRow;
	}

	return Matrix(product);
}

Matrix Matrix::transpose()
{
	Matrix matrix_transpose = zeros(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix_transpose.grid[j][i] = grid[i][j];
		}
	}
	return matrix_transpose;
}

void Matrix::printMatrix()
{

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << grid[i][j] << "\t";
		}
		cout << endl;
	}
}

float dotProduct(vector<float> v1, vector<float> v2) {
	//error handling
	if (v1.size() != v2.size()) {
		throw "cannot perform dot product on vectors of different size";
	}

	float dp = 0.0;
	for (int i = 0; i < v1.size(); i++) {
		dp += v1[i] * v2[i];
	}
	return dp;
}

Matrix zeros(int height, int width) {
	vector < vector <float> > zerosVector(height, vector <float>(width, 0.0));

	return Matrix(zerosVector);
}

vector < vector <float>> get2DVectorFromArray(float twoDarray[], int rows, int cols) {
	vector< vector <float> > twoDVector;
	for (int i = 0; i < rows; i++){
		vector <float> currentRow;
		for (int j = 0; j < cols; j++) {
			currentRow.push_back(twoDarray[i*cols + j]);
		}
		twoDVector.push_back(currentRow);
	}

	return twoDVector;
}


int main() {
	float m_a[] = { 1.0,2.0,3.0,
					4.0,5.0,6.0,
					7.0,8.0,9.0 };
	vector < vector <float>> matrix_a = get2DVectorFromArray(m_a,3,3);
	Matrix a(matrix_a);

	float m_b[] = { 1.0,3.0,
					4.0,6.0,
					7.0,9.0};
	vector < vector <float>> matrix_b = get2DVectorFromArray(m_b, 3, 2);
	Matrix b(matrix_b);

	try {
		Matrix mul = a.multiply(b);
		mul.printMatrix();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	system("pause");
	return 0;
}