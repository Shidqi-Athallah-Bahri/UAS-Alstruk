#include <iostream>
#include <string>
using namespace std;

// Struktur untuk data Pelanggan
struct Customer {
    string name;        // Nama pelanggan
    string order;      // Nama menu yang dipesan
    int queueNumber;   // Nomor antrian pelanggan
    int quantity;      // Jumlah pesanan
    Customer* next;    // Pointer ke pelanggan berikutnya
};

// Struktur untuk Queue
struct Queue {
    Customer* front;    // Pointer ke pelanggan di depan antrian
    Customer* rear;     // Pointer ke pelanggan di belakang antrian
    int currentQueueNumber; // Nomor antrian saat ini
};

// Struktur untuk Menu Merchant
struct menuMerchant {
    string namaMenu;    // Nama menu
    int jumlahStok;     // Jumlah stok menu
    menuMerchant *next; // Pointer ke menu berikutnya
};

menuMerchant *head, *tail, *cur; // Pointer global untuk linked list menu

// Fungsi untuk menginisialisasi queue
// Parameter: q (referensi ke struktur Queue)
// Output: Mengatur front, rear, dan currentQueueNumber ke nilai awal
void initQueue(Queue &q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.currentQueueNumber = 0; // Nomor antrian dimulai dari 0
}

// Fungsi untuk memeriksa apakah queue kosong
// Return: true jika queue kosong, false jika tidak
bool isEmpty(Queue q) {
    return q.front == nullptr;
}

// Fungsi untuk menambahkan pelanggan ke antrian
// Output: Menambahkan pelanggan ke antrian dengan nomor antrian otomatis
void enqueue(Queue &q, string name, string order, int quantity) {
    Customer* newCustomer = new Customer;
    newCustomer->name = name;
    newCustomer->order = order;
    newCustomer->quantity = quantity;
    newCustomer->queueNumber = ++q.currentQueueNumber; // Increment nomor antrian
    newCustomer->next = nullptr;

    // Jika queue kosong, pelanggan menjadi front dan rear
    if (isEmpty(q)) {
        q.front = newCustomer;
        q.rear = newCustomer;
    } else {
        // Tambahkan pelanggan di belakang antrian
        q.rear->next = newCustomer;
        q.rear = newCustomer;
    }
    
    cout << "Pelanggan " << name << " ditambahkan ke antrian dengan nomor " 
         << newCustomer->queueNumber << " (Pesanan: " << order << ", Jumlah: " << quantity << ")" << endl;
}

// Fungsi untuk mengeluarkan pelanggan dari antrian
// Output: Menghapus pelanggan dari depan antrian dan menampilkan informasi
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    Customer* temp = q.front;
    cout << "Pelanggan " << temp->name << " dengan nomor antrian " 
         << temp->queueNumber << " telah dilayani." << endl;

    q.front = q.front->next;
    delete temp;

    // Jika queue menjadi kosong, atur rear ke nullptr
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
}

// Fungsi untuk menampilkan daftar pelanggan yang sedang mengantri
// Output: Menampilkan nomor antrian, nama, pesanan, dan jumlah untuk setiap pelanggan
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }

    cout << "\nDaftar Antrian Pelanggan:" << endl;
    cout << "------------------------" << endl;
    Customer* current = q.front;
    while (current != nullptr) {
        cout << "Nomor Antrian: " << current->queueNumber << endl;
        cout << "Nama: " << current->name << endl;
        cout << "Pesanan: " << current->order << endl;
        cout << "Jumlah: " << current->quantity << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Fungsi untuk membuat linked list menu pertama kali
// Output: Membuat node pertama dari linked list menu
void createMenu(string namaMenu, int jumlahStok) {
    head = new menuMerchant;
    head->namaMenu = namaMenu;
    head->jumlahStok = jumlahStok;
    head->next = nullptr;
    tail = head;
}

// Fungsi untuk menambah menu baru ke linked list
// Output: Menambahkan node menu baru di akhir linked list
void addMenu(string namaMenu, int jumlahStok) {
    menuMerchant *newMenu = new menuMerchant;
    newMenu->namaMenu = namaMenu;
    newMenu->jumlahStok = jumlahStok;
    newMenu->next = nullptr;

    tail->next = newMenu;
    tail = newMenu;
}

// Fungsi untuk memeriksa ketersediaan stok menu
// Return: true jika stok cukup, false jika tidak
bool cekStok(string namaMenu, int quantity) {
    cur = head;
    while (cur != nullptr) {
        if (cur->namaMenu == namaMenu) {
            return cur->jumlahStok >= quantity; // Periksa apakah stok cukup
        }
        cur = cur->next;
    }
    return false; // Menu tidak ditemukan
}

// Fungsi untuk mengurangi stok menu
// Output: Mengurangi stok jika tersedia, menampilkan pesan error jika tidak
void kurangiStok(string namaMenu, int quantity) {
    if (cekStok(namaMenu, quantity)) {
        cur = head;
        while (cur != nullptr) {
            if (cur->namaMenu == namaMenu) {
                cur->jumlahStok -= quantity;
                cout << "Stok " << namaMenu << " berhasil dikurangi sebanyak " << quantity << endl;
                return;
            }
            cur = cur->next;
        }
    } else {
        cout << "Stok " << namaMenu << " tidak cukup atau menu tidak ditemukan" << endl;
    }
}

// Fungsi untuk menampilkan semua menu
// Output: Menampilkan daftar menu dengan nomor dan stok
void displayMenu() {
    cur = head;
    if (cur == nullptr) {
        cout << "Daftar menu kosong!" << endl;
        return;
    }
    cout << "\nDaftar Menu:" << endl;
    cout << "------------" << endl;
    int index = 1;
    while (cur != nullptr) {
        cout << index << ". " << cur->namaMenu << " (Stok: " << cur->jumlahStok << ")" << endl;
        cur = cur->next;
        index++;
    }
}

// Fungsi untuk input data pelanggan
// Output: Meminta nama, pilihan menu, dan jumlah pesanan, lalu menambah ke antrian jika valid
void inputCustomer(Queue &q) {
    string name;
    int menuChoice, quantity;
    
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(1, '\n'); // Bersihkan buffer untuk getline
    getline(cin, name);
    
    displayMenu();
    cout << "Pilih nomor menu: ";
    cin >> menuChoice;
    cout << "Masukkan jumlah pesanan: ";
    cin >> quantity;

    // Validasi jumlah pesanan
    if (quantity <= 0) {
        cout << "Jumlah pesanan harus lebih dari 0!" << endl;
        return;
    }

    // Mendapatkan nama menu berdasarkan pilihan
    cur = head;
    int index = 1;
    string selectedMenu;
    bool menuFound = false;

    while (cur != nullptr) {
        if (index == menuChoice) {
            selectedMenu = cur->namaMenu;
            menuFound = true;
            break;
        }
        cur = cur->next;
        index++;
    }

    if (!menuFound) {
        cout << "Pilihan menu tidak valid!" << endl;
        return;
    }

    // Periksa stok dan proses pesanan
    if (cekStok(selectedMenu, quantity)) {
        enqueue(q, name, selectedMenu, quantity);
        kurangiStok(selectedMenu, quantity);
    } else {
        cout << "Maaf, stok " << selectedMenu << " tidak cukup untuk " << quantity << " pesanan!" << endl;
    }
}

// Fungsi untuk menampilkan menu utama
// Output: Menampilkan opsi sistem antrian
void showMenu() {
    cout << "\nSistem Antrian Kantin" << endl;
    cout << "1. Tambah Pelanggan ke Antrian" << endl;
    cout << "2. Layani Pelanggan (Dequeue)" << endl;
    cout << "3. Tampilkan Antrian" << endl;
    cout << "4. Tampilkan Daftar Menu" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi (1-5): ";
}

// Fungsi utama
// Output: Menjalankan sistem antrian dengan menu interaktif
int main() {
    Queue q;
    initQueue(q);

    // Inisialisasi daftar menu
    createMenu("Nasi Goreng", 10);
    addMenu("Rice Bowl", 0);
    addMenu("Air Putih", 8);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                inputCustomer(q);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                displayQueue(q);
                break;
            case 4:
                displayMenu();
                break;
            case 5:
                cout << "Terima Kasih" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 5);

    // Membersihkan memori antrian
    while (!isEmpty(q)) {
        dequeue(q);
    }

    // Membersihkan memori linked list menu
    cur = head;
    while (cur != nullptr) {
        menuMerchant *temp = cur;
        cur = cur->next;
        delete temp;
    }

    return 0;
}