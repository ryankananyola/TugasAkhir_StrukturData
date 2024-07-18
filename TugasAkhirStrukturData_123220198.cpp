#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<unordered_map>

using namespace std;

struct Pasien {
    string nama;
    int ID, durasiInap, totalHarga;
    char golongan;
};

unordered_map<int, Pasien> patientMap;
vector<Pasien> patientList;
vector<Pasien> history;

int getHarga(char golongan) {
    switch (golongan) {
        case 'A':
            return 150000;
        case 'B':
            return 200000;
        case 'C':
            return 250000;
        case 'D':
            return 300000;
        case 'E':
            return 350000;
        default:
            return 0;
    }
}

void addPasien(string nama, int ID, char golongan, int durasiInap) {
    int harga = getHarga(golongan);
    Pasien PasienBaru = {nama, ID, durasiInap, durasiInap * harga, golongan};
    patientMap[ID] = PasienBaru;
    patientList.push_back(PasienBaru);
}

void tampilInfoPasien() {
    cout << left << setw(15) << "ID Pasien" << setw(20) << "Nama" << setw(15) << "Golongan" << setw(15) << "Lama Inap" << setw(15) << "Total Harga" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    
    for (const auto &Pasien : patientMap) {
        cout << left << setw(15) << Pasien.second.ID << setw(20) << Pasien.second.nama << setw(15) << Pasien.second.golongan << setw(15) << Pasien.second.durasiInap << setw(15) << Pasien.second.totalHarga << endl;
    }
}

void cariPasien(char inisialAwal, char inisialAkhir) {
    vector<Pasien> PasienDalamRentang;

    for (const auto &Pasien : patientMap) {
        string namaPasien = Pasien.second.nama;
        char inisial = namaPasien[0];

        if (toupper(inisial) >= toupper(inisialAwal) && toupper(inisial) <= toupper(inisialAkhir)) {
            PasienDalamRentang.push_back(Pasien.second);
        }
    }

    if (PasienDalamRentang.empty()) {
        cout << "Tidak ada pasien dengan inisial nama dalam rentang tersebut." << endl;
    } else {
        cout << endl << left << setw(15) << "ID Pasien" << setw(20) << "Nama" << setw(15) << "Golongan" << setw(15) << "Lama Inap" << setw(15) << "Total Harga" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        for (const auto &Pasien : PasienDalamRentang) {
            cout << left << setw(15) << Pasien.ID << setw(20) << Pasien.nama << setw(15) << Pasien.golongan << setw(15) << Pasien.durasiInap << setw(15) << Pasien.totalHarga << endl;
        }
    }
}

void hapusPasien(int ID) {
    auto hapus = patientMap.find(ID);
    if (hapus != patientMap.end()) {
        Pasien hapusDataPasien = hapus->second;
        history.push_back(hapusDataPasien);
        patientMap.erase(hapus);
        cout << "Data berhasil dihapus" << endl;
    } else {
        cout << "Pasien dengan ID " << ID << " tidak ditemukan." << endl;
    }
}

void tampilHistory() {
    if (history.empty()) {
        cout << "History masih kosong." << endl;
    } else {
        cout << "Data yang telah dihapus:" << endl;
        cout << left << setw(15) << "ID Pasien" << setw(20) << "Nama" << setw(15) << "Golongan" << setw(15) << "Lama Inap" << setw(15) << "Total Harga" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
            for (const auto &Pasien : history) {
                cout << left << setw(15) << Pasien.ID << setw(20) << Pasien.nama << setw(15) << Pasien.golongan << setw(15) << Pasien.durasiInap << setw(15) << Pasien.totalHarga << endl;
            }
    }
}

int main() {
    int pilihMenu;
    char kembali = 'y';

    while (kembali == 'y') {
        system("cls");
        cout << "SISTEM MANAJEMEN RUMAH SAKIT" << endl << endl;
        cout << "= MENU UTAMA =" << endl;
        cout << "1. Input Data Pasien" << endl;
        cout << "2. Tampil Data Pasien" << endl;
        cout << "3. Cari Data Pasien" << endl;
        cout << "4. Hapus Data Pasien" << endl;
        cout << "5. Tampil Data yang Telah Dihapus (History)" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih Menu : ";
        cin >> pilihMenu;

        switch (pilihMenu) {
            case 1: {
                string nama;
                int durasiInap;
                char golongan;

                system("cls");
                cout << "===============================" << endl;
                cout << "|        MENU INPUT DATA      |" << endl;
                cout << "===============================" << endl << endl;

                cout << "Data Harga Rawat Inap: " << endl << endl;
                cout << "------------------------------" << endl;
                cout << "| Golongan |       Harga      |" << endl;
                cout << "|-----------------------------|" << endl;
                cout << "|     A    | Rp150.000 /malam |" << endl;
                cout << "|     B    | Rp200.000 /malam |" << endl;
                cout << "|     C    | Rp250.000 /malam |" << endl;
                cout << "|     D    | Rp300.000 /malam |" << endl;
                cout << "|     E    | Rp350.000 /malam |" << endl;
                cout << "|-----------------------------|" << endl << endl;

                cout << "Silahkan Input Data dibawah ini" << endl;
                cout << "Nama      : ";
                cin.ignore();
                getline(cin, nama);
                cout << "Golongan  : ";
                cin >> golongan;
                cout << "Lama Inap : ";
                cin >> durasiInap;
                addPasien(nama, patientMap.size() + 1, golongan, durasiInap);
                break;
            }

            case 2:
                system("cls");
                cout << "= DATA PASIEN =" << endl;
                tampilInfoPasien();
                break;

            case 3: {
                system("cls");
                char inisialAwal, inisialAkhir;
                cout << "= CARI DATA PASIEN BERDASARKAN RENTANG INISIAL NAMA =" << endl;
                cout << "Masukkan rentang inisial nama (A-Z): ";
                cin >> inisialAwal >> inisialAkhir;
                cariPasien(toupper(inisialAwal), toupper(inisialAkhir));
                break;
            }
                
            case 4: {
                system("cls");
                int ID;
                cout << "= HAPUS DATA PASIEN =" << endl;
                cout << "Masukkan ID Pasien yang akan dihapus: ";
                cin >> ID;
                hapusPasien(ID);
                break;
            }

            case 5: {
                system("cls");
                cout << "= HISTORY DATA YANG DIHAPUS =" << endl;
                tampilHistory();
                break;
            }

            case 6: {
                cout << "TERIMA KASIH" << endl;
                system("pause");
                return 0;
            }
            
            default:
                cout << "Pilihan menu tidak valid." << endl;
                break;
        }

        if (kembali == 'y') {
            cout << "\nKembali ke menu utama? (y/n): ";
            cin >> kembali;
        }
    }

    return 0;
}
