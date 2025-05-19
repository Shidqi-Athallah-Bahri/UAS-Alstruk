#include <iostream>
using namespace std;

struct menuMerchant
{
    string namaMenu;
    int jumlahStok;

    menuMerchant *next;
};

menuMerchant *head, *tail, *cur;

//fungsi ini digunakan untuk membuat linked list pertama kali
void createMenu(string namaMenu, int jumlahStok)
{
    head = new menuMerchant;
    head->namaMenu = namaMenu;
    head->jumlahStok = jumlahStok;
    head->next = NULL;
    tail = head;
}

//fungsi ini digunakan untuk menambah menu baru
void addMenu(string namaMenu, int jumlahStok)
{
    menuMerchant *newMenu = new menuMerchant;
    newMenu->namaMenu = namaMenu;
    newMenu->jumlahStok = jumlahStok;
    newMenu->next = NULL;

    tail->next = newMenu;
    tail = newMenu;
}

//fungsi ini mereturn boolean apakah menu dan stok ada atau tidak
bool cekstok(string namaMenu)
{
    cur = head;
    while (cur != NULL)
    {
        if (cur->namaMenu == namaMenu)
        {
           if (cur->jumlahStok > 0)
            {
                return true; // Stok ada
            }
            else
            {
                return false; // Stok habis
            }
        }
        cur = cur->next;
    }
    return false;
}

//fungsi ini digunakan untuk mengurangi stok menu dan menampilkan pesan
void kurangiStok(string namaMenu)
{
    if(cekstok(namaMenu))
    {
        cur = head;
        while (cur != NULL)
        {
            if (cur->namaMenu == namaMenu)
            {
                cur->jumlahStok--;
                cout << "Stok berhasil dikurangi" << endl;
                return;
            }
            cur = cur->next;
        }
    }
    else
    {
        cout << "Stok habis" << endl;
    }
}


//fungsi ini digunakan untuk menampilkan semua menu yang ada
void displayMenu()
{
    cur = head;
    while (cur != NULL)
    {
        cout << "Nama Menu: " << cur->namaMenu << endl;
        cout << "Jumlah Stok: " << cur->jumlahStok << endl;
        cur = cur->next;
    }
}   

int main(){
    
    createMenu("Nasi Goreng", 10);
    addMenu("Rice Bowl", 0);
    addMenu("Air Putih", 8);
    int pilihan;
    do
    {   
        cout << "Pilih Menu:" << endl;
        cout << "======================" << endl;
        cout << "1. Nasi Goreng" << endl;
    cout << "2. Rice Bowl" << endl;
    cout << "3. Air Putih" << endl;
    cout << "4. Tampilkan semua menu" << endl;
    cout << "5. Keluar"<<endl;
    cout << "======================" << endl;
    cin >> pilihan;
    switch (pilihan)
    {
        case 1:
        cout << "Anda Memilih Nasi Goreng" << endl;
        kurangiStok("Nasi Goreng");
        break;
        
        case 2:
        cout << "Anda memilih Rice Bowl" << endl;
        kurangiStok("Rice Bowl");
        break;    
        
        case 3:
        cout << "Anda memilih Air Putih" << endl;
        kurangiStok("Air Putih");
        break;
    case 4:
    cout << "Menampilkan semua menu dan stok" << endl;
    displayMenu();
    break;
    
    case 5:
    cout << "Terima Kasih" << endl;
    break;
    
    default:
    cout << "Menu tidak tersedia" << endl;
    break;
}
} while (pilihan != 5);

}