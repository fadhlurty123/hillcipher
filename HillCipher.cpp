#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>     

using namespace std;

int cariDet(vector<vector<int>> keyMatrix, int n){	
	int det1, det2, det3;
	int determinan;
	if (n == 2){
		determinan = ((keyMatrix[0][0] * keyMatrix[1][1]) - (keyMatrix[1][0] * keyMatrix[0][1]));
		return determinan;
	}
	else if (n == 3){
		det1 = (keyMatrix[1][1] * keyMatrix[2][2]) - (keyMatrix[2][1] * keyMatrix[1][2]); 
		det2 = (keyMatrix[1][0] * keyMatrix[2][2]) - (keyMatrix[2][0] * keyMatrix[1][2]); 
		det3 = (keyMatrix[1][0] * keyMatrix[2][1]) - (keyMatrix[2][0] * keyMatrix[1][1]);

		determinan = ((keyMatrix[0][0] * det1) - (keyMatrix[0][1] * det2) + (keyMatrix[0][2] * det3));
		return determinan;
	}
	return 0;
}

vector <vector <int>> cariInverse ( vector<vector<int>> keyMatrix, int n, int determinan){
	vector<vector<int>> inverseMatrix(n,vector<int>(n));

	int each;
	int invDet;

	while (determinan < 0){
		determinan += 26;
	}

	for (int i = 0 ; i < 26 ; i++){
		if ((determinan * i) % 26 == 1){
			invDet =  i;
		}
	}
 	cout << "Inverse determinan   : " << invDet << endl;
    cout << "=========================="<<endl;
	if (n == 2)	{
		swap(keyMatrix[0][0], keyMatrix[1][1]);

		keyMatrix[0][1] = - (keyMatrix[0][1]);
		keyMatrix[1][0] = - (keyMatrix[1][0]);

		for (int i = 0 ; i < 2; i ++){
			for (int j = 0; j < 2 ; j++){
				each = keyMatrix[i][j];

				while (each < 0){
					each += 26;
				}
				inverseMatrix[i][j] = (each * invDet) % 26;
			}
		}

	}
	else if (n == 3){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				each = ((keyMatrix[(j+1)%3][(i+1)%3] * keyMatrix[(j+2)%3][(i+2)%3]) - (keyMatrix[(j+1)%3][(i+2)%3] * keyMatrix[(j+2)%3][(i+1)%3]));

				while (each < 0){
					each += 26;
				}

				(inverseMatrix[i])[j] = (each * invDet) % 26;
			}
		}
	}
	return inverseMatrix;
}

int main(){
	int pilihan;
    cout << "=========================="<<endl;
	cout << "    Program Hill Cipher   "<<endl;
	cout << "=========================="<<endl;
    cout << "=========================="<<endl;
	cout << "1. Enkripsi\n2. Dekripsi\n3. Mencari kunci\nPilihan : ";
	cin >> pilihan;

	if (pilihan == 1){
		string input;
		int n;

		cout << "Masukkan pesan  : " ;
		cin.ignore();
		getline(cin, input);

		cout << "Masukkan ukuran matriks (nxn): " ;cin >> n;

		vector <vector<int>> keyMatrix(n,vector<int>(n));

		cout << "Masukan matriks key" << n << "x" << n << " yang invertible: \n" ;

		for ( int i = 0 ; i < n ; i++){
			for ( int j = 0 ; j < n ; j++){
				cout<<"K["<<i<<"]["<<j<<"] : ";cin >> keyMatrix[i][j];
			}
		}
		
		for ( int i = 1 ; i <= input.length() % n ; i++ ){
			input += 'x';
		}

		string output = "";
		string subString = "";

		for ( int k = 1 ; k <= input.length() / n ; k++){
			subString = input.substr( (k - 1) * n, k * n );

			vector<int> resultMatrix(n,0);

			for ( int i = 0 ; i < n ; i++ ){
				for ( int j = 0 ; j < n ; j++ ){	
               
                    resultMatrix[i] = resultMatrix[i] + ( subString[j] - 'a') * keyMatrix[i][j];
                    
                    resultMatrix[i] %= 26;
				}
                output += ( resultMatrix[i] + 'a' );

			}
		}
		cout << "Hasil enkripsi : "<< output << endl;
	}	

	else if (pilihan == 2){
		string input;
		int n;

		cout << "Masukkan pesan : " ;
		cin.ignore();
		getline(cin, input);

		cout << "Masukkan ukuran matriks (nxn): " ;cin >> n;

		vector <vector<int>> keyMatrix(n,vector<int>(n));
		vector <vector<int>> inverseMatrix(n,vector<int>(n));

		cout << "Masukan matriks key" << n << "x" << n << " yang invertible: \n" ;
		for ( int i = 0 ; i < n ; i++){
			for ( int j = 0 ; j < n ; j++){
				cout<<"K["<<i<<"]["<<j<<"] : ";cin >> keyMatrix[i][j];
			}
		}

		for ( int i = 1 ; i <= input.length() % n ; i++ ){
			input += 'x';
		}

		int determinan = cariDet(keyMatrix, n);

		cout << "determinan matriks : " << determinan << endl;
		
		if (determinan == 0){
			cout << "Determinan matriks tidak boleh == 0" << endl;
			exit (EXIT_FAILURE);
		}

		inverseMatrix = cariInverse(keyMatrix, n, determinan);

		string output = "";
		string subString = "";

		for (int k = 1 ; k <= input.length() / n ; k++){
			subString = input.substr (( k - 1 ) * n , k * n );

			vector<int> resultMatrix(n , 0);

			for (int i = 0 ; i < n ; i++){
				for (int j = 0 ; j < n ; j++){

                    resultMatrix[i] +=  inverseMatrix[i][j] * ( subString[j] - 'a' );
                    
					resultMatrix[i] %= 26;
				}
				output += (resultMatrix[i] + 'a');
			}
			
		}
		cout << "Hasil Dekripsi: "<< output << endl ;
	}
	
	else if (pilihan == 3){
        string plainteks,cipherteks;
		int n;

		cout << "Masukkan plainteks : ";cin>>plainteks;
		cout << "Masukkan cipherteks : ";cin>>cipherteks;
        if(plainteks.length() != cipherteks.length()){
            cout << "Jumlah huruf plainteks dan cipherteks berbeda!" <<endl;
            return 0;
        }

        vector <vector<int>> matriksplain(2,vector<int>(2));
        vector <vector<int>> matrikscipher(2,vector<int>(2));
        vector <vector<int>> inpers(2,vector<int>(2));
        string subString = "";

        int x = 0;
        int u = 0;
        for (int j = 0 ; j < 2 ; j++){
            for ( int k = 0 ; k < 2; k++){
                matriksplain[k][j] = plainteks[x] - 'a';
                x++;
            }
        }
        for (int j = 0 ; j < 2 ; j++){
            for ( int k = 0 ; k < 2; k++){
                matrikscipher[k][j] = cipherteks[u] - 'a';
                u++;
            }
        }

        string output = "";
        int determinan = cariDet(matriksplain, 2);
		inpers = cariInverse(matriksplain, 2, determinan);
        vector <vector<int>> hasil(2,vector<int>(2));

        int sum = 0;
        for (int i = 0 ; i < 2; i++){
            for (int j = 0 ; j < 2 ; j++){
                sum = 0;
                for(int k=0; k<2; k++){
                    sum +=  matrikscipher[i][k] * inpers[k][j];
                }
                hasil[i][j] =  sum;

                hasil[i][j] %= 26;
            }
        }
        cout<<"Matriks Key : "<<endl;
        for (int i = 0 ; i < 2; i++){
            for (int j = 0 ; j < 2 ; j++){
                cout<<hasil[i][j]<< " ";
            }
            cout<<endl;
        }

    }
	else{
		cout << "Pilihan tidak ada !" << endl ;
	}
	return 0;
}