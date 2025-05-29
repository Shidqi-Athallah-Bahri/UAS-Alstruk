#include <iostream>
#include <string>
using namespace std;

// Struktur untuk data Pelanggan
struct Customer {
    string nama;        // Nama pelanggan
    string pesanan;    // Nama menu yang dipesan
    int nomorAntrian;  // Nomor antrian pelanggan
    int jumlah;        // Jumlah pesanan
    Customer* next;    // Pointer ke pelanggan berikutnya
};

// Struktur untuk Antrian
struct Queue {
    Customer* depan;    // Pointer ke pelanggan di depan antrian
    Customer* belakang; // Pointer ke pelanggan di belakang antrian
    int nomorAntrianSaatIni; // Nomor antrian saat ini
};

// Struktur untuk Menu Kantin
// Struct yang digunakan
struct menuMerchant {
    string namaMenu;
    int jumlahStok;
    int hargaMenu;
    menuMerchant* next;
};

// Dua linked list untuk dua merchant
menuMerchant *head1 = nullptr, *tail1 = nullptr;
menuMerchant *head2 = nullptr, *tail2 = nullptr;

// Struktur untuk Riwayat Pesanan
struct OrderHistory {
    string nama;
    string pesanan;
    int nomorAntrian;
    int jumlah;
};

// Deklarasi array untuk riwayat pesanan (maksimal 100 pesanan untuk contoh)
OrderHistory history[100];
int historyCount = 0; // Menghitung jumlah entri riwayat

// Fungsi untuk menginisialisasi antrian
void initQueue(Queue &q) {
    q.depan = nullptr;
    q.belakang = nullptr;
    q.nomorAntrianSaatIni = 0;
}

// Fungsi untuk memeriksa apakah antrian kosong
bool isEmpty(Queue q) {
    return q.depan == nullptr;
}

// Fungsi untuk menambahkan pelanggan ke antrian
void enqueue(Queue &q, string nama, string pesanan, int jumlah) {
    Customer* pelangganBaru = new Customer;
    pelangganBaru->nama = nama;
    pelangganBaru->pesanan = pesanan;
    pelangganBaru->jumlah = jumlah;
    pelangganBaru->nomorAntrian = ++q.nomorAntrianSaatIni;
    pelangganBaru->next = nullptr;

    if (isEmpty(q)) {
        q.depan = pelangganBaru;
        q.belakang = pelangganBaru;
    } else {
        q.belakang->next = pelangganBaru;
        q.belakang = pelangganBaru;
    }
    
    cout << "Pelanggan " << nama << " ditambahkan ke antrian dengan nomor " 
         << pelangganBaru->nomorAntrian << " (Pesanan: " << pesanan << ", Jumlah: " << jumlah << ")" << endl;
}

// Fungsi untuk mengeluarkan pelanggan dari antrian dan mencatat riwayat
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    Customer* temp = q.depan;
    cout << "Pelanggan " << temp->nama << " dengan nomor antrian " 
         << temp->nomorAntrian << " telah dikonfirmasi." << endl;

    // Simpan ke riwayat pesanan
    if (historyCount < 100) {
        history[historyCount].nama = temp->nama;
        history[historyCount].pesanan = temp->pesanan;
        history[historyCount].nomorAntrian = temp->nomorAntrian;
        history[historyCount].jumlah = temp->jumlah;
        historyCount++;
    } else {
        cout << "Riwayat pesanan penuh!" << endl;
    }

    q.depan = q.depan->next;
    delete temp;

    if (q.depan == nullptr) {
        q.belakang = nullptr;
    }
}

// Fungsi untuk menampilkan daftar pelanggan yang sedang mengantri
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    cout << "\nDaftar Antrian Pelanggan:" << endl;
    cout << "------------------------" << endl;
    Customer* current = q.depan;
    while (current != nullptr) {
        cout << "Nomor Antrian: " << current->nomorAntrian << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Pesanan: " << current->pesanan << endl;
        cout << "Jumlah: " << current->jumlah << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Fungsi untuk menambah menu baru ke linked list
void addMenu(menuMerchant*& head, menuMerchant*& tail, string namaMenu, int jumlahStok, int hargaMenu) {
    menuMerchant* newMenu = new menuMerchant{namaMenu, jumlahStok, hargaMenu, nullptr};

    if (head == nullptr) {
        head = tail = newMenu;
    } else {
        tail->next = newMenu;
        tail = newMenu;
    }
}


void deleteMenu(menuMerchant*& head, string namaMenu) {
    menuMerchant *cur = head, *prev = nullptr;
    while (cur != nullptr) {
        if (cur->namaMenu == namaMenu) {
            if (prev == nullptr) {
                // Deleting head node
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            cout << "Menu " << namaMenu << " telah dihapus." << endl;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Menu " << namaMenu << " tidak ditemukan." << endl;
}

void tambahMenu(menuMerchant*& head, menuMerchant*& tail){
    string namaMenu;
    int jumlahStok;
    int hargaMenu;
    cout << "Masukkan nama menu: ";
    cin.ignore(); // clear leftover newline
    getline(cin, namaMenu); // allow spaces in menu name
    cout << "Masukkan jumlah stok: ";
    cin >> jumlahStok;
    cout << "Masukkan Harga: ";
    cin >> hargaMenu;

    addMenu(head, tail ,namaMenu ,jumlahStok ,hargaMenu);
}

void tambahMenu2(){
    string namaMenu;
    int jumlahStok;
    int hargaMenu;
    cout << "Masukkan nama menu: ";
    cin >> namaMenu;
    cout << "Masukkan jumlah stok: ";
    cin >> jumlahStok;
    cout << "Masukkan Harga: ";
    cin >> hargaMenu;

    addMenu(head2, tail2,namaMenu ,jumlahStok ,hargaMenu);
}

//ini gak kepake
// void hapusMenu(menuMerchant* head){
//     string namaMenu;
//     cout << "Masukkan nama menu yang ingin dihapus: ";
//     cin.ignore(); // Mengabaikan newline karakter sebelumnya
//     getline(cin, namaMenu); // Menggunakan getline untuk menangani spasi
//     deleteMenu(head, namaMenu);
// }

// fungsi untuk mengecek apakah menu ada di linkedlist
bool cekMenu(menuMerchant* head, string namaMenu){
     while (head != nullptr) {
        if (head->namaMenu == namaMenu)
        return true;
        head = head->next;
    }
    return false;
}

// Fungsi untuk memeriksa ketersediaan stok menu pake head loh ya
bool cekStok(menuMerchant* head, string namaMenu, int jumlah) {
    while (head != nullptr) {
        if (head->namaMenu == namaMenu) return head->jumlahStok >= jumlah;
        head = head->next;
    }
    return false;
}

//fungsi untuk mengurangi stok pake head loh ya
void kurangiStok(menuMerchant* head, string namaMenu, int jumlah) {
    if (cekStok(head, namaMenu, jumlah)) {
        while (head != nullptr) {
            if (head->namaMenu == namaMenu) {
                head->jumlahStok -= jumlah;
                cout << "Stok " << namaMenu << " dikurangi sebanyak " << jumlah << endl;
                return;
            }
            head = head->next;
        }
    } else {
        cout << "Stok tidak cukup atau menu tidak ditemukan." << endl;
    }
}


// Fungsi untuk menambah stok menu
void tambahStokMenu(menuMerchant* head, string namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            int tambah;
            cout << "Masukkan jumlah stok yang ingin ditambah: ";
            cin >> tambah;
            if (tambah > 0) {
                current->jumlahStok += tambah;
                cout << "Stok berhasil ditambah. Stok sekarang: " << current->jumlahStok << endl;
            } else {
                cout << "Jumlah harus lebih dari 0!" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

// Fungsi untuk mengubah harga menu
void ubahHargaMenu(menuMerchant* head, string namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            int hargaBaru;
            cout << "Masukkan harga baru: ";
            cin >> hargaBaru;
            if (hargaBaru > 0) {
                current->hargaMenu = hargaBaru;
                cout << "Harga berhasil diubah. Harga sekarang: Rp" << current->hargaMenu << endl;
            } else {
                cout << "Harga harus lebih dari 0!" << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

void kosongkanStok(menuMerchant* head, const string& namaMenu) {
    menuMerchant* current = head;
    while (current != nullptr) {
        if (current->namaMenu == namaMenu) {
            current->jumlahStok = 0;
            cout << "Stok menu \"" << namaMenu << "\" telah dikosongkan." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Menu tidak ditemukan." << endl;
}

//wrapper untuk ubahStok
void ubahStok(menuMerchant * head, string namaMenu){
    int pilih;
    cout << "Mengubah Stok" <<endl;
    cout << "1. Tambah Stok" <<endl;
    cout << "2. Kurangi Stok" << endl;
    cout << "3. Kosongkan Stok" <<endl;
    cin >> pilih;

    int jumlah;
    switch (pilih)
    {
    case 1:
        tambahStokMenu(head, namaMenu);
        break;
    case 2:
        cout << "Masukkan jumlah Stok" << endl;
        kurangiStok(head, namaMenu, jumlah);
        break;
    case 3:
        kosongkanStok(head, namaMenu);
        break;
    default:
        break;
    }

}

// ini wrapper untuk semua pilihan yang bisa mengubah menu
void ubahMenu(menuMerchant*& head, menuMerchant* tail, string namaMenu) {
    int pilihan;
    do{
    cout << "\n=== Menu Edit Menu Merchant ===" << endl;
    cout << "Menu yang dipilih: "<< namaMenu <<endl;
    cout << "1. Hapus Menu" << endl;
    cout << "2. Ubah Stok Menu" << endl;
    cout << "3. Ubah Harga Menu" << endl;
    cout << "4. Kembali" << endl;
    cout << "Pilih opsi (1-5): ";
    cin >> pilihan;
    cin.ignore(); // Bersihkan newline

    
    switch (pilihan) {
        case 1:
            // Hapus menu
            deleteMenu(head, namaMenu);
            break;
        case 2:
            // Ubah stok
           ubahStok(head, namaMenu);
            break;
        case 3:
            // Ubah harga
            ubahHargaMenu(head, namaMenu);
            break;
        case 4:
            // Kembali
            cout << "Kembali ke menu utama." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    }while(pilihan != 4 && pilihan != 1);
}

// Fungsi untuk menampilkan semua menu
void displayMenu(menuMerchant* head) {
    if (head == nullptr) {
        cout << "Daftar menu kosong!" << endl;
        return;
    }
    int i = 1;
    while (head != nullptr) {
        cout << i++ << ". " << head->namaMenu << " (Stok: " << head->jumlahStok
             << ") Harga: Rp" << head->hargaMenu << endl;
        head = head->next;
    }
}


// Fungsi untuk menampilkan riwayat pesanan
void displayHistory() {
    if (historyCount == 0) {
        cout << "Riwayat pesanan kosong!" << endl;
        return;
    }

    cout << "\nRiwayat Pesanan:" << endl;
    cout << "----------------" << endl;
    for (int i = 0; i < historyCount; i++) {
        cout << "Pesanan ke-" << (i + 1) << ":" << endl;
        cout << "Nama: " << history[i].nama << endl;
        cout << "Pesanan: " << history[i].pesanan << endl;
        cout << "Nomor Antrian: " << history[i].nomorAntrian << endl;
        cout << "Jumlah: " << history[i].jumlah << endl;
        cout << "----------------" << endl;
    }
}

// Fungsi untuk input data pelanggan
void inputCustomer(Queue &q) {
    string nama;
    int pilihanMenu, jumlah;
    
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(1, '\n');
    getline(cin, nama);
    
    displayMenu(head1);
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return;
    }

    int index = 1;
    string menuTerpilih;
    bool menuDitemukan = false;
    menuMerchant* current = head1; // gunakan pointer sementara

    while (current != nullptr) {
        if (index == pilihanMenu) {
            menuTerpilih = current->namaMenu;
            menuDitemukan = true;
            break;
        }
        current = current->next;
        index++;
    }

    if (!menuDitemukan) {
        cout << "Pilihan menu tidak valid!" << endl;
        return;
    }

    if (cekStok(head1, menuTerpilih, jumlah)) {
        enqueue(q, nama, menuTerpilih, jumlah);
        kurangiStok(head1, menuTerpilih, jumlah);
    } else {
        cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
    }
}

//ton, 
void inputCustomer2(Queue &q) {
    string nama;
    int pilihanMenu, jumlah;
    
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(1, '\n');
    getline(cin, nama);
    
    displayMenu(head2);
    cout << "Pilih nomor menu: ";
    cin >> pilihanMenu;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    if (jumlah <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return;
    }

    
    int index = 1;
    string menuTerpilih;
    bool menuDitemukan = false;
    menuMerchant* current = head2; // gunakan pointer sementara


    while (head2 != nullptr) {
        if (index == pilihanMenu) {
            menuTerpilih = head2->namaMenu;
            menuDitemukan = true;
            break;
        }
        head2 = head2->next;
        index++;
    }

    if (!menuDitemukan) {
        cout << "Pilihan menu tidak valid!" << endl;
        return;
    }

    if (cekStok(head2,menuTerpilih, jumlah)) {
        enqueue(q, nama, menuTerpilih, jumlah);
        kurangiStok(head2, menuTerpilih, jumlah);
    } else {
        cout << "Maaf, stok " << menuTerpilih << " tidak cukup untuk " << jumlah << " pesanan!" << endl;
    }
}

// Fungsi untuk menampilkan menu utama
void showMenu() {
    cout << "\nSistem Antrian Kantin" << endl;
    cout << "1. Tambah Pesanan" << endl;
    cout << "2. Confirm Antrian" << endl;
    cout << "3. Tampilkan Antrian" << endl;
    cout << "4. Tampilkan Daftar Menu" << endl;
    cout << "5. Riwayat Pesanan" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih opsi (1-6): ";
}

// Fungsi utama
int main() {
    Queue q;
    initQueue(q);

    // Inisialisasi daftar menu

    addMenu(head1,tail1, "Rice Bowl", 0, 13000);
    addMenu(head1,tail1, "Air Putih", 8, 3000);
    addMenu(head1,tail1, "Soto Sapi", 9, 12000);
    addMenu(head1,tail1, "Soto Ayam", 100, 12000);
    addMenu(head1,tail1, "Soto Babi", 12, 12000);

    addMenu(head2,tail2, "Babi Guling", 10, 15000);
    addMenu(head2, tail2, "Ayam Panggang", 6, 12000);


    int merchantPilihan;
    menuMerchant* head = nullptr;
    menuMerchant* tail = nullptr;

    cout << "=== Pilih Merchant ===" << endl;
    cout << "1. Merchant 1" << endl;
    cout << "2. Merchant 2" << endl;
    cout << "Pilihan: ";
    cin >> merchantPilihan;

    if (merchantPilihan == 1) {
        head = head1;
        tail = tail1;
    } else if (merchantPilihan == 2) {
        head = head2;
        tail = tail2;
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return 0;
    }

    int pilihan;
    do {
        showMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
            if (merchantPilihan == 1)
            {
                inputCustomer(q); // ini buat yang stok merchant pertama
            }else{
                inputCustomer2(q);// ini buat yang stok merchant kedua
            }
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                displayQueue(q);
                break;
            case 4: {
                displayMenu(merchantPilihan == 1 ? head1 : head2);
                cout << "\nSub-Menu Daftar Menu:" << endl;
                cout << "1. Tambah Menu" << endl;
                cout << "2. Ubah Menu" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Pilih opsi (1-2): ";
                string namaMenu;
                int subPilihan;
                cin >> subPilihan;
                switch (subPilihan) {
                    case 1:
                        if(merchantPilihan == 1){
                            tambahMenu(head1, tail1);
                        }else {
                            tambahMenu(head2, tail2);
                        }
                        
                            break;

                    case 2:
                    cout << "Masukkan Nama Menu: " <<endl;
                        cin.ignore(1, '\n');
                        getline(cin, namaMenu);
                    if(merchantPilihan == 1 && cekMenu(head1, namaMenu))
                    {
                        ubahMenu(head1, tail1, namaMenu); // ini buat stok merchant yang pertama
                    }else if (merchantPilihan == 2 && cekMenu(head2, namaMenu)) {
                        ubahMenu(head2, tail2, namaMenu); // ini buat yang kedua
                    }else {
                        cout << "Menu itu tidak ada" << endl;
                    }
                       break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 5:
                displayHistory();
                break;
            case 6:
                cout << "Terima Kasih" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);

    // Membersihkan memori antrian
    while (!isEmpty(q)) {
        dequeue(q);
    }

    // Membersihkan memori linked list menu
    
    while (head1 != nullptr) {
        menuMerchant *temp = head1;
        head1 = head1->next;
        delete temp;
    }

     while (head2 != nullptr) {
        menuMerchant *temp = head2;
        head2 = head2->next;
        delete temp;
    }

    return 0;
}