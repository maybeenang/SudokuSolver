#include <iostream>
#include <fstream>
using namespace std;

bool isSolved(int mat[9][9], int row, int col, int n) {

	// cek row
	for (int i = 0; i < 9; i++) {
		if (mat[row][i] == n)
			return false;
	}

	// cek column
	for (int i = 0; i < 9; i++) {
		if (mat[i][col] == n)
			return false;
	}

	// cek 3x3 box
	int boxRowStart = (row / 3) * 3;
	int boxColStart = (col / 3) * 3;
	for (int i = boxRowStart; i < boxRowStart + 3; i++) {
		for (int j = boxColStart; j < boxColStart + 3; j++) {
			if (mat[i][j] == n)
				return false;
		}
	}

	return true;

}

bool solveSudoku(int mat[9][9], int row, int col){

	// jika sudoku sudah selesai
	if (row == 8 && col == 9){
		return true;
	}

	// jika sudoku masih belum selesai
	if (col == 9){
		row++;
		col = 0;
	}

	// jika sudoku baris ini sudah terisi
	if (mat[row][col] != 0){
		return solveSudoku(mat, row, col + 1);
	}

	// jika sudoku baris ini belum terisi
	for (int n = 1; n <= 9; n++){

		// cek apakah angka n bisa dimasukkan ke sudoku
		if (isSolved(mat, row, col, n)){
			mat[row][col] = n;

			// jika angka n bisa dimasukkan ke sudoku
			if (solveSudoku(mat, row, col + 1)){
				return true;
			}
		}

		// jika angka n tidak bisa dimasukkan ke sudoku
		mat[row][col] = 0;
	}

	// jika angka n tidak bisa dimasukkan ke sudoku
	return false;

}


int main (){

	// input file stream
	ifstream File;
	cout << "Masukan nama file: ";
	string fileName;
	cin >> fileName;
	File.open("./input/" + fileName);

	// perkondisian ketika inpuran file ada
	if(File.is_open()){

		// deklaraasi matriks
		int matrix[9][9];

		// menampung isi file ke dalam matriks
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				File >> matrix[i][j];
			}
		}

		File.close();

		// menampilkan isi matriks
		for (int i = 0; i < 9; i++){

			if (i % 3 == 0){
				cout << "-------------------------" << endl;
			}

			for (int j = 0; j < 9; j++){

				if (j == 0){
					cout << "| ";
				}

				if (matrix[i][j] == 0){
					cout << "  ";
				}
				else{
					cout << matrix[i][j] << " ";
				}


				if (j == 2 || j == 5 || j == 8){
					cout << "| ";
				}

			}

			if ( i == 8){
				cout << endl << "-------------------------";
			}
			cout << endl;
		}

		cout << endl;

		// jika sudoku bisa di solve
		if (solveSudoku(matrix, 0, 0)){

			// menyimpan hasil solve sudoku ke dalam file
			ofstream File;
			File.open("./output/" + fileName);

			cout << "Solusi Sudoku" << endl;

			// menampilkan hasil solve sudoku
			for (int i = 0; i < 9; i++){

				if (i % 3 == 0){
					cout << "-------------------------" << endl;
				}

				for (int j = 0; j < 9; j++){

					if (j == 0){
						cout << "| ";
					}

					if (matrix[i][j] == 0){
						cout << "  ";
						File << "  ";
					}
					else{
						cout << matrix[i][j] << " ";
						File << matrix[i][j] << " ";
					}

					if (j == 2 || j == 5 || j == 8){
						cout << "| ";
					}
				}
				
				if ( i == 8){
					cout << endl << "-------------------------";
				}
				cout << endl;
				File << endl;

			}

			// menutup file
			File.close();

			cout << endl << "File hasil tersimpan di : ./output/" << fileName << endl;

		}
		else{
			// jika sudoku tidak bisa di solve
			cout << "Tidak ada solusi" << endl;
		}


	}
	else{
		// jika inputan file tidak ada
		cout << "File tidak ditemukan!" << endl;
	}

	File.close();


	return 0;
}