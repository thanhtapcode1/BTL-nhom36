#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

//================== SACH======================
struct sach {
    string masach;
    string tensach;
    string tacgia;
    int soluong;
};
struct nodeSach {
    sach data;
    nodeSach* next;
};
class listSach {
   private:
    nodeSach* head;
    nodeSach* tail;

   public:
    listSach();
    nodeSach* createnodesach(sach s);
    nodeSach* timSachTheoMa(string ma);
    nodeSach* timSachTheoTen(string ten);
    void xoasachbangma(string ma);
    void xoasachbangten(string ten);
    bool isempty();
    void indssach();
    void themsachdauds(sach s);
    void themsachcuoids(sach s);
    void themsachbatkids(sach s, int pos);
    int soluongsach();
    void themsoLuongSach(string ma, int soluong);
    void inSachDaTimID(string masach);
    void inSachDaTimTen(string tensach);
    nodeSach* getHead();
};
//------------------ Cai dat ham list Sach--------------------------------------
listSach::listSach() {
    head = NULL;
    tail = NULL;
}
nodeSach* listSach::getHead() { return head; }
int listSach::soluongsach() {
    int size = 0;
    for (nodeSach* p = head; p != NULL; p = p->next) {
        size++;
    }
    return size;
}
bool listSach::isempty() { return head == NULL; }
nodeSach* listSach::createnodesach(sach s) {
    nodeSach* p = new nodeSach();
    p->data = s;
    p->next = NULL;
    return p;
}
void listSach::themsachdauds(sach s) {
    nodeSach* p = createnodesach(s);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
}
void listSach::themsachcuoids(sach s) {
    nodeSach* p = createnodesach(s);
    if (head == NULL) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
}
void listSach::themsachbatkids(sach s, int pos) {
    int size = soluongsach();
    if (pos <= 0 || pos > size + 1) {
        cout << "vi tri chen khong hop le!" << endl;
        return;
    }
    nodeSach* p = createnodesach(s);
    nodeSach* a = head;
    if (pos == 1) {
        themsachdauds(s);
        return;
    } else if (pos == size + 1) {
        themsachcuoids(s);
        return;
    }
    for (int i = 1; i < pos - 1; i++) {
        a = a->next;
    }
    p->next = a->next;
    a->next = p;
    size++;
}
void listSach::indssach() {
    if (isempty()) {
        cout << "Danh sach rong!" << endl;
        return;
    }
    cout << string(38, '=') << "DANH SACH SACH" << string(38, '=') << endl;
    cout << left << setw(5) << "STT" << setw(12) << "Ma sach" << setw(35) << "Ten sach" << setw(25)
         << "Tac gia" << setw(10) << "So luong" << endl;
    cout << string(90, '-') << endl;
    int i = 1;
    for (nodeSach* p = head; p != NULL; p = p->next) {
        cout << left << setw(5) << i++ << setw(12) << p->data.masach << setw(35) << p->data.tensach
             << setw(25) << p->data.tacgia << setw(10) << p->data.soluong << endl;
    }
}
nodeSach* listSach::timSachTheoMa(string ma) {
    nodeSach* p = head;
    while (p != NULL) {
        if (p->data.masach == ma)
            return p;
        p = p->next;
    }
    return NULL;
}
nodeSach* listSach::timSachTheoTen(string ten) {
    nodeSach* p = head;
    while (p != NULL) {
        if (p->data.tensach == ten)
            return p;
        p = p->next;
    }
    return NULL;
}

void listSach::themsoLuongSach(string ma, int soluong) {
    nodeSach* a = timSachTheoMa(ma);
    if (a == NULL) {
        cout << "Khong tim thay sach co ma " << ma;
        return;
    }
    a->data.soluong += soluong;
    cout << "Da them " << soluong << " quyen sach cho ma: " << ma << endl;
}

void listSach::inSachDaTimID(string masach) {
    nodeSach* p = timSachTheoMa(masach);
    if (p == NULL) {
        cout << "Khong tim thay sach.";
        return;
    }
    cout << "Tim thay sach :";
    cout << "Masach:" << p->data.masach << " | Ten:" << p->data.tensach << " | TacGia:" << p->data.tacgia << " | SL:" << p->data.soluong;
}
void listSach::inSachDaTimTen(string ten) {
    nodeSach* p = timSachTheoTen(ten);
    if (p == NULL) {
        cout << "Khong tim thay sach.";
        return;
    }
    cout << "Tim thay sach :";
    cout << "Masach:" << p->data.masach << " | Ten:" << p->data.tensach << " | TacGia:" << p->data.tacgia << " | SL:" << p->data.soluong;
}
//===================== Doc Gia=================================================
struct docGia {
    string madg;
    string ten;
    int tuoi;
    string gioitinh;
};
struct nodeDg {
    docGia data;
    nodeDg* next;
};
class listDg {
   private:
    nodeDg* head;
    nodeDg* tail;

   public:
    listDg();
    nodeDg* createNode(docGia x);
    void themcuoi(docGia x);
    bool isEmpty();
    nodeDg* timtheoID(string id);
    string taoIDtudong();
    void xoadgID(string id);
    nodeDg* getHead();
    void inDsdg();
    void in1DG(string madg);
    void capnhattt(string madg, string ten, int tuoi, string gioitinh);
};
//------------------ Cai dac ham doc gia--------------------------------------
listDg ::listDg() {
    head = NULL;
    tail = NULL;
}
nodeDg* listDg::getHead() { return head; }
bool listDg::isEmpty() { return head == NULL; }
nodeDg* listDg::createNode(docGia x) {
    nodeDg* p = new nodeDg();
    p->data = x;
    p->next = NULL;
    return p;
}
void listDg::themcuoi(docGia x) {
    nodeDg* p = createNode(x);
    if (head == NULL) {
        head = tail = p;
        return;
    } else {
        tail->next = p;
        tail = p;
    }
}
nodeDg* listDg::timtheoID(string id) {
    nodeDg* p = head;
    while (p != NULL) {
        if (p->data.madg == id)
            return p;
        p = p->next;
    }
    return NULL;
}
string listDg::taoIDtudong() {
    int dem = 0;
    for (nodeDg* p = head; p != NULL; p = p->next) {
        dem++;  // dem so doc gia hien co
    }
    int nextNum = dem + 1;  // doc gia ke tiep
    string id = "DG";
    if (nextNum < 10)
        id += "00" + to_string(nextNum);
    else if (nextNum < 100)
        id += "0" + to_string(nextNum);
    else
        id += to_string(nextNum);
    return id;
}
void listDg::xoadgID(string id) {
    nodeDg* p = head;
    nodeDg* truoc = NULL;
    while (p != NULL && p->data.madg != id) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        cout << "Khong tim thay doc gia co ID: " << id << endl;
        return;
    }
    if (truoc == NULL)
        head = p->next;
    else
        truoc->next = p->next;
    delete p;
    cout << "Da xoa doc gia co ID: " << id << endl;
}
void listDg::capnhattt(string madg, string ten, int tuoi, string gioitinh) {
    nodeDg* p = timtheoID(madg);
    p->data.ten = ten;
    p->data.tuoi = tuoi;
    p->data.gioitinh = gioitinh;
}
void listDg::inDsdg() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    cout << "\n============================================================================\n";
    cout << "| " << left << setw(8) << "ID";
    cout << "| " << left << setw(30) << "HO VA TEN";
    cout << "| " << left << setw(7) << "TUOI";
    cout << "| " << left << setw(20) << "GIOI TINH" << setw(3) << " |";
    cout << "\n---------------------------------------------------------------------------\n";
    for (nodeDg* p = head; p != NULL; p = p->next) {
        cout << "| " << left << setw(8) << p->data.madg;
        cout << "| " << left << setw(30) << p->data.ten;
        cout << "| " << left << setw(7) << p->data.tuoi;
        cout << "| " << left << setw(20) << p->data.gioitinh << setw(3) << " |";
        cout << endl;
    }
    cout << "============================================================================\n";
}
void listDg::in1DG(string ma) {
    nodeDg* p = timtheoID(ma);
    cout << "\n===========================================================================\n";
    cout << "| " << left << setw(8) << "ID";
    cout << "| " << left << setw(30) << "HO VA TEN";
    cout << "| " << left << setw(7) << "TUOI";
    cout << "| " << left << setw(20) << "GIOI TINH" << setw(3) << " |";
    cout << "\n---------------------------------------------------------------------------\n";
    cout << "| " << left << setw(8) << p->data.madg;
    cout << "| " << left << setw(30) << p->data.ten;
    cout << "| " << left << setw(7) << p->data.tuoi;
    cout << "| " << left << setw(20) << p->data.gioitinh << setw(3) << " |";
    cout << endl;
    cout << "============================================================================\n";
}
//=================Muon tra sach=======================================================
struct muontra {
    string madg;
    string masach;
    string tensach;
    string trangthai;
};
class listMuontra {
   public:
    vector<muontra> dsmt;
    bool kiemtraSachDangMuonID(string maSach);
    bool kiemtraSachDangMuonTen(string tenSach);
    bool kiemtraMuonSachIDDG(string id);
    bool kiemtraMuonSachTenDG(string tendg);
    void muonSach(string madg, nodeSach* a);
    void traSach(string madg, nodeSach* a);
    void dsDaMuon(string madg);
};
bool listMuontra::kiemtraSachDangMuonID(string maSach) {
    for (auto& mt : dsmt) {
        if (mt.masach == maSach && mt.trangthai == "Dang muon") {
            return true;  // Có người đang mượn
        }
    }
    return false;
}
bool listMuontra::kiemtraSachDangMuonTen(string tenSach) {
    for (auto& mt : dsmt) {
        if (mt.tensach == tenSach && mt.trangthai == "Dang muon") {
            return true;  // Có người đang mượn
        }
    }
    return false;
}
bool listMuontra::kiemtraMuonSachIDDG(string iddg) {
    for (auto& mt : dsmt) {
        if (mt.madg == iddg && mt.trangthai == "Dang muon") {
            return true;  // Có người đang mượn
        }
    }
    return false;
}
void listMuontra::muonSach(string madg, nodeSach* a) {
    if (a == NULL) {
        cout << "Khong ton tai sach co ma " << madg;
        return;
    }
    if (a->data.soluong <= 0) {
        cout << "Da het sach.";
        return;
    }
    a->data.soluong--;
    muontra mt;
    mt.madg = madg;
    mt.masach = a->data.masach;
    mt.tensach = a->data.tensach;
    mt.trangthai = "Dang muon";
    dsmt.push_back(mt);
    cout << "Ban da muon thanh cong sach :" << a->data.tensach;
}
void listMuontra::traSach(string madg, nodeSach* a) {
    for (auto& x : dsmt) {
        if (x.madg == madg && x.masach == a->data.masach &&
            x.trangthai == "Dang muon") {
            x.trangthai = "Da tra";
            a->data.soluong++;
            cout << "Tra sach thanh cong.";
            return;
        }
    }
    cout << "Khong tim thay sach da muon";
}
void listMuontra::dsDaMuon(string madg) {
    for (auto& x : dsmt) {
        if (x.madg == madg) {
            cout << "========= Sach da muon =========\n";
            cout << "- Ma sach:" << x.masach << " -Ten Sach:" << x.tensach
                 << " -Trang thai:" << x.trangthai << endl;
        }
    }
}
void listSach::xoasachbangma(string ma) {
    nodeSach* p = head;
    nodeSach* truoc = NULL;
    while (p != NULL && p->data.masach != ma) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        cout << "Khong tim thay ma sach!" << endl;
        return;
    }
    if (p == head && p == tail) {  // chi co 1 node
        head = tail = NULL;
    } else if (p == head) {
        head = p->next;  // xoa dau
    } else {
        truoc->next = p->next;  // xoa o giua
        if (p == tail) {        // neu node o cuoi thi doi tail len
            tail = truoc;
        }
    }
    delete p;
    cout << "Da xoa sach co ma: " << ma << endl;
}
void listSach::xoasachbangten(string ten) {
    nodeSach* p = head;
    nodeSach* truoc = NULL;
    while (p != NULL && p->data.tensach != ten) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        cout << "Khong tim thay ma sach!" << endl;
        return;
    }
    if (p == head && p == tail) {  // chi co 1 node
        head = tail = NULL;
    } else if (p == head) {
        head = p->next;  // xoa dau
    } else {
        truoc->next = p->next;  // xoa o giua
        if (p == tail) {        // neu node o cuoi thi doi tail len
            tail = truoc;
        }
    }
    delete p;
    cout << "Da xoa sach co ten: " << ten << endl;
}
//====================== TaiKhoan=================================
struct taikhoan {
    string username;
    string pasword;
    string vaitro;
    string madg;
};

bool dangnhap(taikhoan dstk[], int soTk, string user, string pass, taikhoan& tkHientai) {
    for (int i = 0; i < soTk; i++) {
        if ((dstk[i].username == user) && (dstk[i].pasword == pass)) {
            tkHientai = dstk[i];
            return true;
        }
    }
    return false;
}
void taoTaiKhoan(taikhoan dstk[], int& soTk, listDg& Dsdocgia, int& sotkUser) {
    cout << "==============Dang ky==============\n";
    taikhoan tk;
    cout << "Nhap ten dang nhap: ";
    cin >> tk.username;
    cout << "Nhap mat khau: ";
    cin >> tk.pasword;
    cout << "Nhap vai tro (admin/user): ";
    cin >> tk.vaitro;
    if (tk.vaitro == "user" || tk.vaitro == "User") {
        tk.madg = Dsdocgia.taoIDtudong();
        docGia dg;
        dg.madg = tk.madg;
        dg.ten = "Chua cap nhat";
        dg.tuoi = 0;
        dg.gioitinh = "Chua cap nhat";
        Dsdocgia.themcuoi(dg);
        cout << "Tao tai khoan thanh cong .ID :" << dg.madg;
    } else {
        tk.madg = "N/A";
        cout << "Tao tai khoan thanh cong!\n";
    }
    dstk[soTk++] = tk;
}
void doiMk(taikhoan& tkhientai, taikhoan dstk[], int sotk) {
    string mkCu, mkMoi;
    cout << "Nhap mat khau cu ";
    cin >> mkCu;
    if (mkCu != tkhientai.pasword) {
        cout << "Mat khai khong hop le.";
        return;
    }
    cout << "Nhap mat khau moi :";
    cin >> mkMoi;
    // cap nhat tk hien tai
    tkhientai.pasword = mkMoi;
    // cap nhat trong danh sach tk
    for (int i = 0; i < sotk; i++) {
        if (dstk[i].username == tkhientai.username) {
            dstk[i].pasword = mkMoi;
            break;
        }
    }
    cout << "Doi mat khau thanh cong.";
}
void xoataikhoan(taikhoan dstk[], int& sotk, string madg) {
    int vitri = -1;
    for (int i = 0; i < sotk; i++) {
        if (dstk[i].madg == madg) {
            vitri = i;
            break;
        }
    }
    for (int i = vitri; i < sotk - 1; i++) {
        dstk[i] = dstk[i + 1];
    }
    sotk--;
}
//================================================================================
void nhapSach(sach& a) {
    cout << "Nhap ma sach :";
    cin >> a.masach;
    cin.ignore();
    cout << "Nhap ten sach :";
    getline(cin, a.tensach);
    cout << "Nhap tac gia :";
    getline(cin, a.tacgia);
    cout << "Nhap so luong :";
    cin >> a.soluong;
}
//====================FILE=======================================================
void luudstk(taikhoan dstk[], int sotk) {
    fstream fs("dstk.txt", ios ::out);
    for (int i = 0; i < sotk; i++) {
        fs << dstk[i].madg << ",";
        fs << dstk[i].username << ",";
        fs << dstk[i].pasword << ",";
        fs << dstk[i].vaitro << endl;
    }
    fs.close();
}
void loadTaikhoan(taikhoan dstk[], int& sotk) {
    ifstream file("dstk.txt");
    sotk = 0;
    string line;
    while (getline(file, line)) {  // đọc cho tới khi gặp \n
        if (line.empty())
            continue;
        stringstream tk(line);  // xu ly tung dong`
        string madg, username, pass, vaitro;
        getline(tk, madg, ',');
        getline(tk, username, ',');
        getline(tk, pass, ',');
        getline(tk, vaitro, ',');
        dstk[sotk].madg = madg;
        dstk[sotk].username = username;
        dstk[sotk].pasword = pass;
        dstk[sotk].vaitro = vaitro;
        sotk++;
    }
    file.close();
}
void luudsdocgia(listDg& dsdg) {
    fstream fs("dsdg.txt", ios ::out);
    nodeDg* p = dsdg.getHead();
    while (p != NULL) {
        fs << p->data.madg << ",";
        fs << p->data.ten << ",";
        fs << p->data.tuoi << ",";
        fs << p->data.gioitinh << endl;
        p = p->next;
    }
    fs.close();
}
void loadDocgia(listDg& dsdg) {
    ifstream file("dsdg.txt");
    string line;
    while (getline(file, line)) {  // đọc cho tới khi gặp \n
        if (line.empty())
            continue;
        docGia dg;
        string tuoiStr;
        stringstream ss(line);  // xu ly tung dong`
        getline(ss, dg.madg, ',');
        getline(ss, dg.ten, ',');
        getline(ss, tuoiStr, ',');
        getline(ss, dg.gioitinh, ',');
        dg.tuoi = stoi(tuoiStr);  // chuyen string sang int
        dsdg.themcuoi(dg);
    }
    file.close();
}
void luuDSSach(listSach& ds) {
    ofstream fs("dssach.txt");
    if (!fs)
        return;
    for (nodeSach* p = ds.getHead(); p != NULL; p = p->next) {
        fs << p->data.masach << "," << p->data.tensach << "," << p->data.tacgia
           << "," << p->data.soluong << "\n";
    }
}

void loadDSSach(listSach& ds) {
    ifstream file("dssach.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        sach s;
        string soluongStr;
        stringstream ss(line);
        getline(ss, s.masach, ',');
        getline(ss, s.tensach, ',');
        getline(ss, s.tacgia, ',');
        getline(ss, soluongStr, ',');
        s.soluong = stoi(soluongStr);
        ds.themsachcuoids(s);
    }
    file.close();
}
void luuDSMuon(listMuontra& dsMuon) {
    fstream fs("dsmuon.txt", ios::out);
    for (auto& x : dsMuon.dsmt) {
        fs << x.madg << "," << x.masach << "," << x.tensach << "," << x.trangthai
           << endl;
    }
    fs.close();
}
void loadDSMuon(listMuontra& dsMuon) {
    ifstream file("dsmuon.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        muontra mt;
        stringstream ss(line);
        getline(ss, mt.madg, ',');
        getline(ss, mt.masach, ',');
        getline(ss, mt.tensach, ',');
        getline(ss, mt.trangthai, ',');
        dsMuon.dsmt.push_back(mt);
    }
    file.close();
}
//===================MAIN==========================================================
int main() {
    listDg dsDg;
    listSach dsSach;
    listMuontra dsmuon;
    taikhoan dstk[100];
    int sotk = 0;
    int sotkUser = 0;
    taikhoan taikhoanHienTai;
    bool daDangNhap = false;
    loadTaikhoan(dstk, sotk);
    loadDocgia(dsDg);
    loadDSSach(dsSach);
    loadDSMuon(dsmuon);
    for (int i = 0; i <= 100; i += 5) {  // them vao cho dep
        cout << "\rDang tai... " << i << "%";
        Sleep(50);
    }
    cout << "\nTai du lieu thanh cong .";
    while (true) {
        cout << "\n=========He thong dang nhap==========\n";
        cout << "|| 1. Dang nhap.                   ||\n";
        cout << "|| 2. Dang ky tai khoan            ||\n";
        cout << "|| 3. Thoat                        ||\n";
        cout << "=====================================\n";
        cout << "Nhap lua chon:";
        int lcdn;
        cin >> lcdn;
        if (lcdn == 1) {  // dang nhap
            cout << "==============Dang nhap==============\n";
            string user, pass;
            cout << "Ten dang nhap:";
            cin >> user;
            cout << "Mat khau:";
            cin >> pass;
            if (dangnhap(dstk, sotk, user, pass, taikhoanHienTai)) {
                daDangNhap = true;
                cout << "Dang nhap thanh cong.";
            } else {
                cout << "Sai ten dang nhap hoac mat khau";
            }
        } else if (lcdn == 2) {  // dang ky tk
            taoTaiKhoan(dstk, sotk, dsDg, sotkUser);
        } else if (lcdn == 3) {  // thoat
            return 0;
        }
        while (daDangNhap == true) {
            if ((taikhoanHienTai.vaitro == "admin") || (taikhoanHienTai.vaitro == "Admin")) {
                cout << "\n\n=====================ADMIN MENU======================\n";
                cout << "||          1. THEM SACH                            ||\n";
                cout << "||          2. XOA SACH ( Ma / Ten )                ||\n";
                cout << "||          3. XOA DOC GIA THEO ID                  ||\n";
                cout << "||          4. TIM SACH ( Ma / Ten )                ||\n";
                cout << "||          5. THEM SO LUONG SACH                   ||\n";
                cout << "||          6. HIEN THI DU LIEU                     ||\n";
                cout << "||          7. DOI MAT KHAU                         ||\n";
                cout << "||          8. DANG XUAT                            ||\n";
                cout << "=====================================================\n";
                cout << "[[?]] Moi nhap lua chon :";
                int lc;
                cin >> lc;
                switch (lc) {
                    case 1: {  // THEM SACH
                        cout << " 1.Them dau\n";
                        cout << " 2.Them cuoi\n";
                        cout << " 3.Them giua\n";
                        cout << "[?]Moi nhap lua chon:";
                        int lcthem;
                        cin >> lcthem;
                        sach a;
                        nhapSach(a);
                        if (lcthem == 1)
                            dsSach.themsachdauds(a);
                        else if (lcthem == 2)
                            dsSach.themsachcuoids(a);
                        else if (lcthem == 3) {
                            int pos;
                            cout << "Nhap vi tri muon them :";
                            cin >> pos;
                            dsSach.themsachbatkids(a, pos);
                        }
                        luuDSSach(dsSach);
                        cout << "Them sach thanh cong.";
                        break;
                    }
                    case 2: {  // XOA SACH
                        int lcxoa;
                        cout << "1.Xoa theo Ma\n";
                        cout << "2.Xoa theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        cin >> lcxoa;
                        if (lcxoa == 1) {
                            cout << "Nhap Ma can xoa :";
                            string masach;
                            cin >> masach;
                            if (dsSach.isempty())
                                cout << " Danh sach sach hien dang rong!\n";
                            else if (dsmuon.kiemtraSachDangMuonID(masach))
                                cout << " Sach nay hien dang duoc doc gia muon. Khong the xoa!\n";
                            else
                                dsSach.xoasachbangma(masach);
                        } else if (lcxoa == 2) {
                            cout << "Nhap Ten can xoa :";
                            string tenSach;
                            cin.ignore();
                            getline(cin, tenSach);
                            if (dsSach.isempty())
                                cout << "Danh sach sach hien dang rong!\n";
                            else if (dsmuon.kiemtraSachDangMuonTen(tenSach))
                                cout << "Sach nay hien dang duoc doc gia muon. Khong the xoa!\n";
                            else
                                dsSach.xoasachbangten(tenSach);
                        }
                        break;
                    }
                    case 3: {  // XOA DOC GIA
                        cout << "Nhap ID doc gia can xoa :";
                        string id;
                        cin >> id;

                        if (dsDg.isEmpty())
                            cout << "Danh sach doc gia hien dang rong!";
                        else if (dsmuon.kiemtraMuonSachIDDG(id))
                            cout << "Doc gia dang muon sach. Khong the xoa!";
                        else {
                            dsDg.xoadgID(id);
                            xoataikhoan(dstk, sotk, id);
                            luudsdocgia(dsDg);
                            luudstk(dstk, sotk);
                        }
                        break;
                    }
                    case 4: {
                        int lctim;
                        cout << "1.Tim theo Ma\n";
                        cout << "2.Tim theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        cin >> lctim;

                        if (lctim == 1) {
                            cout << "Nhap ma sach can tim:";
                            string masach;
                            cin >> masach;
                            dsSach.inSachDaTimID(masach);
                        } else if (lctim == 2) {
                            cout << "Nhap ten sach can tim:";
                            string tensach;
                            cin.ignore();
                            getline(cin, tensach);
                            dsSach.inSachDaTimTen(tensach);
                        }
                        break;
                    }
                    case 5: {
                        cout << "Nhap ma sach can them: ";
                        string ma;
                        cin >> ma;
                        int soluong;
                        cin >> soluong;
                        dsSach.themsoLuongSach(ma, soluong);
                        break;
                    }
                    case 6: {
                        int abc;
                        cout << "1.Danh sach Sach.\n";
                        cout << "2.Danh sach Doc Gia.\n";
                        cout << "[?]Moi nhap lua chon:";
                        cin >> abc;
                        if (abc == 1)
                            dsSach.indssach();
                        else if (abc == 2)
                            dsDg.inDsdg();
                        break;
                    }
                    case 7:
                        doiMk(taikhoanHienTai, dstk, sotk);
                        break;
                    case 8:
                        cout << "Da dang xuat";
                        daDangNhap = false;
                        break;
                    default:
                        cout << "Lua chon khong hop le!";
                }
            } else if ((taikhoanHienTai.vaitro == "user") || (taikhoanHienTai.vaitro == "User")) {
                cout << "\n\n=====================USER MENU=======================\n";
                cout << "||          1. XEM DANH SACH SACH                   ||\n";
                cout << "||          2. TIM SACH ( Ma / Ten )                ||\n";
                cout << "||          3. MUON SACH                            ||\n";
                cout << "||          4. TRA SACH                             ||\n";
                cout << "||          5. XEM SACH DA MUON                     ||\n";
                cout << "||          6. XEM THONG TIN CA NHAN                ||\n";
                cout << "||          7. CAP NHAT THONG TIN TAI KHOAN         ||\n";
                cout << "||          8. DOI MAT KHAU                         ||\n";
                cout << "||          9. DANG XUAT                            ||\n";
                cout << "=====================================================\n";
                cout << "[[?]] Moi nhap lua chon :";
                int lc;
                cin >> lc;
                switch (lc) {
                    case 1:
                        dsSach.indssach();
                        break;
                    case 2: {
                        cout << "======= Tim Sach =======\n";
                        cout << " 1.Tim theo Ma\n";
                        cout << " 2.Tim theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        int lctim;
                        cin >> lctim;
                        if (lctim == 1) {
                            string ma;
                            cout << "Ma sach can tim:";
                            cin >> ma;
                            dsSach.inSachDaTimID(ma);
                        } else if (lctim == 2) {
                            string tenSach;
                            cout << "Ten sach can tim:";
                            cin.ignore();
                            getline(cin, tenSach);
                            dsSach.inSachDaTimTen(tenSach);
                        }
                        break;
                    }
                    case 3: {
                        string ma;
                        cout << "Nhap ma sach can muon :";
                        cin >> ma;
                        nodeSach* p = dsSach.timSachTheoMa(ma);
                        dsmuon.muonSach(taikhoanHienTai.madg, p);
                        luuDSMuon(dsmuon);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 4: {
                        string ma;
                        cout << "Nhap ma sach can tra ";
                        cin >> ma;
                        nodeSach* p = dsSach.timSachTheoMa(ma);
                        dsmuon.traSach(taikhoanHienTai.madg, p);
                        luuDSMuon(dsmuon);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 5: {
                        string madg = taikhoanHienTai.madg;
                        dsmuon.dsDaMuon(madg);
                        break;
                    }
                    case 6:
                        dsDg.in1DG(taikhoanHienTai.madg);
                        break;
                    case 7: {
                        string ten, gioitinh;
                        int tuoi;
                        cout << "Nhap ho va ten cua ban :";
                        cin.ignore();
                        getline(cin, ten);
                        cout << "Nhap tuoi :";
                        cin >> tuoi;
                        cout << "Nhap gioi tinh :";
                        cin >> gioitinh;
                        dsDg.capnhattt(taikhoanHienTai.madg, ten, tuoi, gioitinh);
                        luudsdocgia(dsDg);
                        break;
                    }
                    case 8:
                        doiMk(taikhoanHienTai, dstk, sotk);
                        break;
                    case 9:
                        cout << "Da dang xuat";
                        daDangNhap = false;
                        break;
                    default:
                        cout << "Lua chon khong hop le!";
                }
            }
        }
        luudsdocgia(dsDg);
        luudstk(dstk, sotk);
        luuDSSach(dsSach);
        luuDSMuon(dsmuon);
    }
}
