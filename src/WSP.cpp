#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
#include <time.h>

string tc1 = "test1 (7x8).txt";
string tc2 = "test2 (11x11).txt";
string tc3 = "test3 (14x16).txt";
string tc4 = "test4 (20x20).txt";
string tc5 = "test5 (20x24).txt";
string tc6 = "test6 (22x22).txt";
string tc7 = "test7 (30x30).txt";
string tc8 = "test8 (34x34).txt";
string tc9 = "test9 (31x31).txt";

// Struct comparasi
struct strC {
    bool same;
    int num;
};

/* Deskripsi  : Fungsi compare digunakan untuk membandingkan 2 buah kata, serta menghitung berapa huruf yang dibandingkan 
   Output  : {bool, int} */
strC compare (string s1, string s2) {
    bool same = true;
    int num = 0;
    strC comp;
    int i = 0;
    if (s1.length() != s2.length()) {
        same = false;
    }
    if (same) {
        while (i < s1.length() && same) {
            num++;
            if (s1[i] != s2[i]) {
                same = false;
            }
            else {
                i++;
            }
        }
    }
    comp.same = same;
    comp.num = num;
    return comp;
}


int main(){
    int i, j, k, l, i1, j1;
    int row, col;
    int ws, pure;   // Untuk menghitung dimensi matrix
    bool endMat;    // Batas akhir matrix
    bool fileExist = false;
    ifstream myfile;
    string mytext;
    string file_name;
    do
    {
        cout << "MASUKKAN NAMA FILE: ";getline(cin, file_name);
        file_name = "../test/"+file_name;       // Bagian ini bisa diganti dengan tc1, tc2 ,....
        myfile.open (file_name);
        if (myfile) {
            fileExist = true;
        }
        else {
            cout << "File tidak ditemukan..!!" << endl << endl;
            myfile.close();
            this_thread::sleep_for(milliseconds(5000));
            system("CLS");
        }
    } while (not(fileExist));

//      **************************************************************
    /* {BAGIAN BACA FILE}
       Digunakan untuk membentuk matriks word puzzle dan array pattern */

//      **************************************************************

    // BAGIAN 1, MENGHITUNG DIMENSI MATRIKS
    getline(myfile, mytext);
    row = 1;
    ws = mytext.length();
    col = (ws+1)/2;
    endMat = false;
    while (getline (myfile,mytext) && not(endMat)) {
        pure = mytext.length();
        mytext.erase(remove(mytext.begin(), mytext.end(), ' '), mytext.end());
        if (pure == ws && mytext.length() == col) {
            row ++;
        }
        else {
            endMat = true;
        }
    }
    myfile.close();
    
    // BAGIAN 2, MEMBUAT MATRIKS
    myfile.open (file_name);
    char mat[row][col];
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            myfile >> mat[i][j];
        }
    }

//      **************************************************************
    /* {BAGIAN OUPUT FILE}
       Digunakan untuk mengecek apakah pembacaan file sudah benar atau tidak*/

//      **************************************************************

    // BAGIAN 1, OUTPUT MATRIKS
    cout << endl;
    cout << "UKURAN MATRIKS :  " << row << " x " << col << endl;
    cout << endl;
    // 2. Print Matrix  ??
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout<<mat[i][j] << " ";
        }
        cout<<endl;
    }
    cout << endl;
    cout << "<<<<<============================================>>>>>>" << endl;
    cout<<endl;


    /* {BAGIAN CHECKING ALGORITMA}
       Digunakan untuk penyelesaian Word Puzzle Game */
       
    string str;                 // Concate dari matriks
    string ptrn;                // Kata yang dicari
    string dummy;               // dummy untuk baris kosong
    strC comp;                  // Comparasi 2 string
    bool found;                 // Flag
    int len;                    // Panjang kata
    int tot;                    // Banyak comparison uktuk 1 kata
    int time;                   // Lama eksekusi
    int totALL = 0;             // Banyak comparison total
    int timeAll = 0;            // Lama eksekusi total
    int top, bot, right, left;  // Batas kata dalam matriks

    getline(myfile, dummy);     // Mengambil whitespace '\n'
    getline(myfile, dummy);     // Mengambil whitespace '\n'

    while (getline (myfile, ptrn)) {
        cout << "Kata                 : " << ptrn << endl;
        cout << endl;
        len = ptrn.length();
        found = false;
        tot = 0;
        auto start = high_resolution_clock::now();

        i = 0;
        while (i < row && not(found)) {
            j = 0;
            while (j < col && not(found)) {
                top = (i-len+1);
                bot = (i+len-1);
                right = (j+len-1);
                left = (j-len+1);

                // 1. Arah atas
                if (not(found) && top >= 0) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i-k][j];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (top<=i1 && i1<=i) && (j1==j) ){
                                    cout<<mat[i1][j1] << " ";
                                }
                                else {
                                    cout << "-" << " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 2. Arah bawah
                if (not(found) && bot < row) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i+k][j];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (i<=i1 && i1<=bot) && (j1==j) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 3. Arah kanan
                if (not(found) && right < col) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i][j+k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (j<=j1 && j1<=right) && (i1==i) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 4. Arah kiri
                if (not(found) && left >= 0) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i][j-k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (left<=j1 && j1<=j) && (i1==i) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 5. Arah kanan-atas
                if (not(found) && right < col && top >= 0) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i-k][j+k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (j<=j1 && j1<=right) && (top<=i1 && i1<=i) && ((i+j)==(i1+j1)) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 6. Arah kanan-bawah
                if (not(found) && right < col && bot < row) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i+k][j+k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (j<=j1 && j1<=right) && (i<=i1 && i1<=bot) && ((i-j)==(i1-j1)) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 7. Arah kiri-atas
                if (not(found) && left >= 0 && top >= 0) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i-k][j-k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (left<=j1 && j1<=j) && (top<=i1 && i1<=i) && ((i-j)==(i1-j1)) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }

                // 8. Arah kiri-bawah
                if (not(found) && left >= 0 && bot < row) {
                    str = "";
                    for (k = 0; k < len; k++) {
                        str = str + mat[i+k][j-k];
                    }
                    comp = compare(ptrn,str);
                    tot += comp.num;
                    found = comp.same;
                    if (found) {
                        
                        for (i1 = 0; i1 < row; i1++) {
                            for (j1 = 0; j1 < col; j1++) {
                                if ( (left<=j1 && j1<=j) && (i<=i1 && i1<=bot) && ((i+j)==(i1+j1)) ){
                                    cout<<mat[i1][j1]<< " ";
                                }
                                else {
                                    cout << "-"<< " ";
                                }
                            }
                            cout<<endl;
                        }
                        
                    }
                }
                if (found) {
                    cout << endl;
                    cout << "Total comparison     : " << tot << endl;
                    totALL += tot;
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    time = duration.count();
                    timeAll += time;
                    cout << "Waktu eksekusi       : " << time << " microseconds" << endl;
                    
                    cout << "<<<----------------------------------->>>" << endl;
                    cout<<endl;
                }
                if (not(found) && i == (row-1) && j == (col-1)) {
                    cout << "KATA TIDAK DITEMUKAN....!!!" << endl;
                    cout << "<<<----------------------------------->>>" << endl;
                    cout<<endl;
                }
                j++;
            }
            i++;
        }
    }
    myfile.close();
    cout << "Total semua comparison     : " << totALL << endl;
    cout << "Waktu total eksekusi       : " << timeAll << " microseconds" << endl << endl;
    
    return 0;
}