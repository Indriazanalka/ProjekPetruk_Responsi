#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

class Pengguna {
public:
    string namaPengguna;
    string kataSandi;

    Pengguna() {}  
    Pengguna(string nama, string sandi) : namaPengguna(nama), kataSandi(sandi) {}
};


class Film {
public:
    string judul;
    string waktu;

    Film(string j, string w) : judul(j), waktu(w) {}
};


class Bioskop {
public:
    string nama;
    vector<Film> filmList;
    vector<vector<char>> kursi;

    Bioskop(string n, int baris, int kolom) : nama(n), kursi(baris, vector<char>(kolom, 'O')) {}

    void tambahFilm(string judul, string waktu) {
        filmList.push_back(Film(judul, waktu));
    }

    void tampilkanFilm() {
        for (size_t i = 0; i < filmList.size(); ++i) {
            cout << i + 1 << ". " << filmList[i].judul << " pada " << filmList[i].waktu << endl;
        }
    }

    void tampilkanKursi() {
        for (size_t i = 0; i < kursi.size(); ++i) {
            for (size_t j = 0; j < kursi[i].size(); ++j) {
                cout << kursi[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool pesanKursi(int baris, int kolom) {
        if (baris < 0 || baris >= kursi.size() || kolom < 0 || kolom >= kursi[0].size() || kursi[baris][kolom] == 'X') {
            return false;
        }
        kursi[baris][kolom] = 'X';
        return true;
    }
};

class SistemPemesananTiket {
private:
    unordered_map<string, Pengguna> pengguna;
    vector<Bioskop> bioskopList;
    Pengguna* penggunaLogin = nullptr;

public:
    void registrasiPengguna(string namaPengguna, string kataSandi) {
        if (pengguna.find(namaPengguna) != pengguna.end()) {
            cout << "Nama pengguna sudah ada. Silahkan masukkan nama yang valid." << endl;
        } else {
            pengguna[namaPengguna] = Pengguna(namaPengguna, kataSandi);
            cout << "Pengguna terdaftar dengan sukses." << endl;
        }
    }

    bool loginPengguna(string namaPengguna, string kataSandi) {
        if (pengguna.find(namaPengguna) != pengguna.end() && pengguna[namaPengguna].kataSandi == kataSandi) {
            penggunaLogin = &pengguna[namaPengguna];
            cout << "Login berhasil." << endl;
            return true;
        } else {
            cout << "Nama pengguna atau kata sandi salah." << endl;
            return false;
        }
    }

    void tambahBioskop(Bioskop bioskop) {
        bioskopList.push_back(bioskop);
    }

    void tampilkanBioskop() {
        for (size_t i = 0; i < bioskopList.size(); ++i) {
            cout << i + 1 << ". " << bioskopList[i].nama << endl;
        }
    }

    void konfirmasiPembayaran(string judulFilm, string waktuFilm, string namaBioskop, int baris, int kolom) {
        char konfirmasi;
        cout << "Detail Pemesanan:" << endl;
        cout << "Film: " << judulFilm << endl;
        cout << "Waktu: " << waktuFilm << endl;
        cout << "Bioskop: " << namaBioskop << endl;
        cout << "Kursi: Baris " << baris + 1 << ", Kolom " << kolom + 1 << endl;
        cout << "Apakah Anda ingin melanjutkan ke pembayaran? (y/n): ";
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            cout << "Pembayaran berhasil. Tiket Anda telah dikonfirmasi." << endl;
            cout << "Kode tiket Anda: [###BARCODE###]" << endl;
        } else {
            cout << "Pemesanan dibatalkan." << endl;
        }
    }

    void pesanTiket() {
        if (!penggunaLogin) {
            cout << "Silakan login untuk memesan tiket." << endl;
            return;
        }

        tampilkanBioskop();
        int pilihanBioskop;
        cout << "Pilih Bioskop: ";
        cin >> pilihanBioskop;
        if (pilihanBioskop < 1 || pilihanBioskop > bioskopList.size()) {
            cout << "Pilihan tidak valid." << endl;
            return;
        }
        Bioskop &bioskop = bioskopList[pilihanBioskop - 1];

        bioskop.tampilkanFilm();
        int pilihanFilm;
        cout << "Pilih Film: ";
        cin >> pilihanFilm;
        if (pilihanFilm < 1 || pilihanFilm > bioskop.filmList.size()) {
            cout << "Pilihan tidak valid." << endl;
            return;
        }
        Film &film = bioskop.filmList[pilihanFilm - 1];

        bioskop.tampilkanKursi();
        int baris, kolom;
        cout << "Pilih Kursi (baris kolom): ";
        cin >> baris >> kolom;
        if (bioskop.pesanKursi(baris - 1, kolom - 1)) {
            konfirmasiPembayaran(film.judul, film.waktu, bioskop.nama, baris - 1, kolom - 1);
        } else {
            cout << "Gagal memesan kursi. Mungkin sudah dipesan atau nomor kursi tidak valid." << endl;
        }
    }
};

int main() {
    SistemPemesananTiket sistem;

    Bioskop bioskop1("Bioskop XXI", 5, 5);
    bioskop1.tambahFilm("Agak lain,", "10:00");
    bioskop1.tambahFilm("Dilean 1990,", "13:00");
    sistem.tambahBioskop(bioskop1);

    cout << "Selamat Datang di ToxID" << endl << endl;

    int pilihan;
    do {
        cout << "1. Registrasi\n2. Login\n3. Pesan Tiket\n4. Keluar\nPilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
            string namaPengguna, kataSandi;
            cout << "Masukkan nama pengguna: ";
            cin >> namaPengguna;
            cout << "Masukkan kata sandi: ";
            cin >> kataSandi;
            sistem.registrasiPengguna(namaPengguna, kataSandi);
        } else if (pilihan == 2) {
            string namaPengguna, kataSandi;
            cout << "Masukkan nama pengguna: ";
            cin >> namaPengguna;
            cout << "Masukkan kata sandi: ";
            cin >> kataSandi;
            sistem.loginPengguna(namaPengguna, kataSandi);
        } else if (pilihan == 3) {
            sistem.pesanTiket();
        }
    } while (pilihan != 4);

    return 0;
}

