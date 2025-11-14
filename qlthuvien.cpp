#include <windows.h>

#include <algorithm>
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
    void timSachgandung(string tensach);
    void xoasachbangma(string ma);
    bool isempty();
    void indssach();
    void themsachdauds(sach s);
    void themsachcuoids(sach s);
    void themsachbatkids(sach s, int pos);
    int soluongsach();
    void themsoLuongSach(string ma, int soluong);
    void inSachDaTimID(string masach);
    nodeSach* getHead();
    bool tonTaiMaSach(string ma);
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
bool listSach::tonTaiMaSach(string ma) {
    nodeSach* p = head;
    while (p != NULL) {
        if (p->data.masach == ma)
            return true;
        p = p->next;
    }
    return false;
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
    // chuyen chuoi ve chu thuong roi tim kiem
    for (char& c : ten) c = tolower(c);
    nodeSach* p = head;
    while (p != NULL) {
        string temp = p->data.tensach;
        for (char& c : temp) c = tolower(c);
        if (temp == ten)
            return p;
        p = p->next;
    }
    return NULL;
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
}
void listSach::themsoLuongSach(string ma, int soluong) {
    nodeSach* a = timSachTheoMa(ma);
    if (a == NULL) {
        cout << "Khong tim thay sach co ma " << ma;
        return;
    }
    if (soluong < 0) {
        cout << "So luong khong hop le!";
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
void listSach::timSachgandung(string tensach) {
    string maChuThuong = tensach;
    transform(maChuThuong.begin(), maChuThuong.end(), maChuThuong.begin(), ::tolower);  // chuyen input ve chu thuong
    bool flag = false;
    for (nodeSach* p = head; p != NULL; p = p->next) {
        string tenLower = p->data.tensach;
        transform(tenLower.begin(), tenLower.end(), tenLower.begin(), ::tolower);
        if (tenLower.find(maChuThuong) != string::npos) {
            flag = true;
            cout << "\nTim thay sach: ";
            cout << p->data.masach << " | " << p->data.tensach << " | Tac gia: " << p->data.tacgia << " | SL: " << p->data.soluong;
        }
    }
    if (!flag) {
        cout << "Khong tim thay sach nao phu hop!\n";
    }
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
    cout << "Da xoa doc gia co ID: " << id << endl;
}
void listDg::capnhattt(string madg, string ten, int tuoi, string gioitinh) {
    nodeDg* p = timtheoID(madg);
    if (!p) {
        cout << "Khong tim thay doc gia!\n";
        return;
    }
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
    if (!p) {
        cout << "Khong tim thay doc gia!\n";
        return;
    }
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
    void muonSach(string masach, string madg, nodeSach* a);
    void traSach(string madg, nodeSach* a);
    void dsDaMuon(string madg);
    void intatca();
    void xoaLichSuTheoDG(string madg);
    void xoaLichSuTheoSach(string maSach);
    void inYCmuon();
    void duyetYC(string madg, string masach, nodeSach* a);
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
void listMuontra::muonSach(string masach, string madg, nodeSach* a) {
    if (a == NULL) {
        cout << "Khong ton tai sach co ma " << masach;
        return;
    }
    if (a->data.soluong <= 0) {
        cout << "Da het sach.";
        return;
    }
    for (auto& x : dsmt) {  // kiem tra da doc gia do da muon sach nay hay chua
        if (x.madg == madg && x.masach == masach && (x.trangthai == "Dang muon" || x.trangthai == "Cho duyet")) {
            cout << "Ban da gui yeu cau hoac da muon sach nay roi!\n";
            return;
        }
    }
    muontra mt;
    mt.madg = madg;
    mt.masach = a->data.masach;
    mt.tensach = a->data.tensach;
    mt.trangthai = "Cho duyet";
    dsmt.push_back(mt);
    cout << "Da gui yeu cau den admin";
}
void listMuontra::traSach(string madg, nodeSach* a) {
    if (a == NULL) {
        cout << "Khong ton tai sach voi ma vua nhap!\n";
        return;
    }
    for (auto& x : dsmt) {
        if (x.madg == madg && x.masach == a->data.masach && x.trangthai == "Dang muon") {
            x.trangthai = "Da tra";
            a->data.soluong++;
            cout << "Tra sach thanh cong.";
            return;
        }
    }
    cout << "Khong tim thay sach da muon";
}
void listMuontra::dsDaMuon(string madg) {
    bool flag = false;
    cout << "========= Sach da muon =========\n";
    for (auto& x : dsmt) {
        if (x.madg == madg) {
            flag = true;
            cout << "- Ma sach:" << x.masach << " -Ten Sach:" << x.tensach << " -Trang thai:" << x.trangthai << endl;
        }
    }
    if (flag == false) {
        cout << "Ban chua muon sach nao.\n";
    }
}
void listMuontra::intatca() {
    if (dsmt.empty() == true) {
        cout << "Danh sach muon rong!";
        return;
    }
    cout << "\n====================Lich Su Muon====================\n";
    cout << string(65, '=') << endl;
    cout << left << setw(10) << "Ma DG" << setw(35) << "Sach Da Muon" << setw(20) << "Trang thai" << endl;
    cout << string(65, '-') << endl;  // in ra 65 ki tu -
    for (auto& x : dsmt) {
        cout << left << setw(10) << x.madg << setw(35) << x.tensach << setw(20) << x.trangthai << endl;
    }
    cout << string(65, '=');
}
void listMuontra::xoaLichSuTheoDG(string madg) {
    vector<muontra> tam;
    for (auto& mt : dsmt) {
        if (mt.madg != madg) {
            tam.push_back(mt);  // giu lai cac doc gia ko phai doc gia truyen vao ham
        }
    }
    dsmt = tam;
}
void listMuontra::xoaLichSuTheoSach(string maSach) {
    vector<muontra> tam;
    for (auto& mt : dsmt) {
        if (mt.masach != maSach) {
            tam.push_back(mt);  // giu lai sach ko phai sach truyen vao ham
        }
    }
    dsmt = tam;
}
void listMuontra::inYCmuon() {
    cout << "\n=============Duyet Yeu Cau Muon Sach===========\n";
    bool flag = false;
    for (auto& x : dsmt) {
        if (x.trangthai == "Cho duyet") {
            flag = true;
            cout << "- DG: " << x.madg << " | Sach: " << x.tensach << " | Ma: " << x.masach << endl;
        }
    }
    if (flag == false) {
        cout << "Khong co yeu cau nao dang cho duyet!\n";
        return;
    }
}
void listMuontra::duyetYC(string madg, string masach, nodeSach* a) {
    bool flag = false;
    for (auto& x : dsmt) {
        if (x.madg == madg && x.masach == masach && x.trangthai == "Cho duyet") {
            x.trangthai = "Dang muon";
            a->data.soluong--;
            cout << "Duyet thanh cong.\n";
            flag = true;
            return;
        }
    }
    if (flag == false) {
        cout << "Khong tim thay yeu cau hop le!";
    }
}
//====================== TaiKhoan================================================
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
    for (int i = 0; i < soTk; i++) {
        if (dstk[i].username == tk.username) {
            cout << "Ten dang nhap da ton tai!\n";
            return;
        }
    }
    cout << "Nhap mat khau: ";
    cin >> tk.pasword;
    string vaitro;
    cout << "Nhap vai tro (admin/user): ";
    while (true) {
        cin >> vaitro;
        for (auto& c : vaitro) c = tolower(c);  // chuyen ve chu thuong
        if (vaitro == "admin" || vaitro == "user") {
            tk.vaitro = vaitro;
            break;
        }
        cout << "Vai tro khong hop le! vui long nhap theo dinh dang :";
    }
    if (tk.vaitro == "user") {
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
    cout << "Nhap mat khau cu :";
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
            vitri = i;  // i da dc ++
            break;
        }
    }
    if (vitri == -1) return;
    for (int i = vitri; i < sotk - 1; i++) {
        dstk[i] = dstk[i + 1];
    }
    sotk--;
}
//==================================Ham Phu==============================================
int nhapSoNguyen() {
    int x;
    while (true) {
        if (cin >> x) return x;
        cout << "Sai dinh dang! Vui long nhap lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
string nhapChuoi() {
    string s;
    getline(cin >> ws, s);
    return s;
}
void nhapSach(sach& a) {
    cout << "Nhap ma sach:";
    a.masach = nhapChuoi();
    cout << "Nhap ten sach:";
    a.tensach = nhapChuoi();
    cout << "Nhap tac gia:";
    a.tacgia = nhapChuoi();
    cout << "Nhap so luong:";
    a.soluong = nhapSoNguyen();
}
bool kiemtraChuoiLaSo(const string& s) {
    if (s.empty()) {  // chuoi rong""
        return false;
    }
    for (char c : s) {
        if (isdigit((unsigned char)c) == false) {  // ep kieu so nguyen khong dau
            return false;
        }
    }
    return true;
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
    dsdg = listDg();  // xoa du lieu cu
    ifstream file("dsdg.txt");
    if (!file.is_open()) {
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        docGia dg;
        string tuoiStr;
        getline(ss, dg.madg, ',');
        getline(ss, dg.ten, ',');
        getline(ss, tuoiStr, ',');
        getline(ss, dg.gioitinh, ',');
        if (dg.madg == "" || dg.ten == "" || tuoiStr == "" || dg.gioitinh == "")
            continue;
        if (kiemtraChuoiLaSo(tuoiStr))
            dg.tuoi = stoi(tuoiStr);
        else
            dg.tuoi = 0;
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
    ds = listSach();  // clear danh sách cũ
    ifstream file("dssach.txt");

    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        sach s;
        string soluongStr;
        stringstream ss(line);
        getline(ss, s.masach, ',');
        getline(ss, s.tensach, ',');
        getline(ss, s.tacgia, ',');
        getline(ss, soluongStr, ',');
        // bo qua khoang trang""
        if (s.masach == "" || s.tensach == "" || s.tacgia == "" || soluongStr == "") {
            continue;
        }
        // so luong phai la so , neu khac so tra ve 0
        if (kiemtraChuoiLaSo(soluongStr)) {
            s.soluong = stoi(soluongStr);
        } else {
            s.soluong = 0;
        }
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
    dsMuon.dsmt.clear();
    ifstream file("dsmuon.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        muontra mt;
        stringstream ss(line);

        getline(ss, mt.madg, ',');
        getline(ss, mt.masach, ',');
        getline(ss, mt.tensach, ',');
        getline(ss, mt.trangthai, ',');
        // bo qua khoang trang""
        if (mt.madg == "" || mt.masach == "" || mt.tensach == "" || mt.trangthai == "") {
            continue;
        }
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
        lcdn = nhapSoNguyen();
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
            luudsdocgia(dsDg);
        } else if (lcdn == 3) {  // thoat
            return 0;
        }
        while (daDangNhap == true) {
            if (taikhoanHienTai.vaitro == "admin") {
                cout << "\n\n=====================ADMIN MENU======================\n";
                cout << "||          1. THEM SACH                            ||\n";
                cout << "||          2. XOA SACH ( Ma / Ten )                ||\n";
                cout << "||          3. XOA DOC GIA THEO ID                  ||\n";
                cout << "||          4. TIM SACH ( Ma / Ten )                ||\n";
                cout << "||          5. THEM SO LUONG SACH                   ||\n";
                cout << "||          6. DUYET YEU CAU MUON SACH              ||\n";
                cout << "||          7. HIEN THI DU LIEU                     ||\n";
                cout << "||          8. DOI MAT KHAU                         ||\n";
                cout << "||          9. DANG XUAT                            ||\n";
                cout << "=====================================================\n";
                cout << "[[?]] Moi nhap lua chon :";
                int lc;
                lc = nhapSoNguyen();
                switch (lc) {
                    case 1: {  // THEM SACH
                        cout << "===========Them Sach==========\n";
                        cout << " 0.Quay lai\n";
                        cout << " 1.Them dau\n";
                        cout << " 2.Them cuoi\n";
                        cout << " 3.Them giua\n";
                        cout << "[?]Moi nhap lua chon:";
                        int lcthem;
                        lcthem = nhapSoNguyen();
                        if (lcthem == 0) {
                            break;
                        }
                        sach a;
                        nhapSach(a);
                        if (dsSach.tonTaiMaSach(a.masach)) {
                            cout << "Ma sach da ton tai .Khong the them!";
                            break;
                        }
                        if (lcthem == 1)
                            dsSach.themsachdauds(a);
                        else if (lcthem == 2)
                            dsSach.themsachcuoids(a);
                        else if (lcthem == 3) {
                            int pos;
                            cout << "Nhap vi tri muon them :";
                            pos = nhapSoNguyen();
                            dsSach.themsachbatkids(a, pos);
                        }
                        luuDSSach(dsSach);
                        cout << "Them sach thanh cong.";
                        break;
                    }
                    case 2: {  // XOA SACH
                        cout << "\n================Sach Hien Co==================\n";
                        dsSach.indssach();
                        int lcxoa;
                        cout << "===========Xoa Sach==========\n";
                        cout << "0.Quay lai\n";
                        cout << "1.Xoa theo Ma\n";
                        cout << "2.Xoa theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        lcxoa = nhapSoNguyen();
                        if (lcxoa == 0) {
                            break;
                        }
                        if (lcxoa == 1) {
                            cout << "Nhap Ma can xoa :";
                            string masach;
                            cin >> masach;
                            string masachXoa = masach;
                            if (dsSach.isempty())
                                cout << " Danh sach sach hien dang rong!\n";
                            else if (dsmuon.kiemtraSachDangMuonID(masach))
                                cout << " Sach nay hien dang duoc doc gia muon. Khong the xoa!\n";
                            else {
                                dsSach.xoasachbangma(masach);
                                cout << "Da xoa sach co ma " << masachXoa;
                            }
                            dsmuon.xoaLichSuTheoSach(masach);
                            luuDSSach(dsSach);
                        } else if (lcxoa == 2) {
                            cout << "Nhap ten sach can xoa: ";
                            string tenSach = nhapChuoi();
                            if (dsSach.isempty()) {
                                cout << "Danh sach sach dang rong!\n";
                            } else {
                                nodeSach* p = dsSach.timSachTheoTen(tenSach);
                                if (p == NULL) {
                                    cout << "Khong tim thay sach ten: " << tenSach << endl;
                                } else {
                                    string tenSachXoa = p->data.tensach;
                                    string maXoa = p->data.masach;
                                    // neu sach dang dc muon => ko xoa
                                    if (dsmuon.kiemtraSachDangMuonID(maXoa)) {
                                        cout << "Sach dang duoc muon. Khong the xoa!\n";
                                    } else {
                                        dsSach.xoasachbangma(maXoa);
                                        dsmuon.xoaLichSuTheoSach(maXoa);
                                        luuDSSach(dsSach);
                                        cout << "Da xoa sach co ten " << tenSachXoa;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 3: {  // XOA DOC GIA
                        cout << "===========Xoa doc gia==========\n";
                        cout << "Nhap ID doc gia (nhap 0 de quay lai):";
                        string id;
                        cin >> id;
                        if (id == "0") {
                            break;
                        }
                        if (dsDg.isEmpty()) {
                            cout << "Danh sach doc gia dang rong!\n";
                            break;
                        } else if (!dsDg.timtheoID(id)) {
                            cout << "Khong co doc gia nay!\n";
                        } else if (dsmuon.kiemtraMuonSachIDDG(id)) {
                            cout << "Doc gia dang muon sach. Khong the xoa!\n";
                        } else {
                            dsDg.xoadgID(id);
                            dsmuon.xoaLichSuTheoDG(id);
                            xoataikhoan(dstk, sotk, id);
                            luudsdocgia(dsDg);
                            luudstk(dstk, sotk);
                        }
                        break;
                    }
                    case 4: {
                        cout << "===========Tim sach==========\n";
                        int lctim;
                        cout << "0.Quay ve\n";
                        cout << "1.Tim theo Ma\n";
                        cout << "2.Tim theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        lctim = nhapSoNguyen();
                        if (lctim == 0) {
                            break;
                        }
                        if (lctim == 1) {
                            cout << "Nhap ma sach can tim:";
                            string masach;
                            cin >> masach;
                            dsSach.inSachDaTimID(masach);
                        } else if (lctim == 2) {
                            cout << "Nhap ten sach can tim:";
                            string tensach = nhapChuoi();
                            dsSach.timSachgandung(tensach);
                        }
                        break;
                    }
                    case 5: {
                        cout << "===========Them so luong sach==========\n";
                        cout << "Nhap ma sach can them (nhap 0 de quay ve): ";
                        string ma;
                        cin >> ma;
                        if (ma == "0") {
                            break;
                        }
                        cout << "Nhap so luong :";
                        int soluong;
                        soluong = nhapSoNguyen();
                        dsSach.themsoLuongSach(ma, soluong);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 6: {
                        dsmuon.inYCmuon();
                        string madg, masach;
                        cout << "Nhap ma doc gia can duyet: ";
                        madg = nhapChuoi();
                        cout << "Nhap ma sach can duyet: ";
                        masach = nhapChuoi();
                        nodeSach* a = dsSach.timSachTheoMa(masach);
                        if (!a) {
                            cout << "Khong hop le!";
                            break;
                        }
                        if (a->data.soluong <= 0) {
                            cout << "Sach da het, khong the duyet!\n";
                            break;
                        }
                        dsmuon.duyetYC(madg, masach, a);
                        break;
                    }
                    case 7: {
                        cout << "===========Hien thi du lieu==========\n";
                        int abc;
                        cout << "0.Quay ve\n";
                        cout << "1.Danh sach Sach.\n";
                        cout << "2.Danh sach Doc Gia.\n";
                        cout << "3.Lich su muon.\n";
                        cout << "[?]Moi nhap lua chon:";
                        abc = nhapSoNguyen();
                        if (abc == 0) {
                            break;
                        }
                        if (abc == 1)
                            dsSach.indssach();
                        else if (abc == 2)
                            dsDg.inDsdg();
                        else if (abc == 3)
                            dsmuon.intatca();
                        break;
                    }
                    case 8: {
                        cout << "===========Doi mat khau==========\n";
                        doiMk(taikhoanHienTai, dstk, sotk);
                        break;
                    }
                    case 9: {
                        cout << "Da dang xuat";
                        daDangNhap = false;
                        break;
                        default:
                            cout << "Lua chon khong hop le!";
                    }
                }
            } else if (taikhoanHienTai.vaitro == "user") {
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
                lc = nhapSoNguyen();
                switch (lc) {
                    case 1:
                        dsSach.indssach();
                        break;
                    case 2: {
                        cout << "===========Tim Sach==========\n";
                        cout << " 0.Quay ve\n";
                        cout << " 1.Tim theo Ma\n";
                        cout << " 2.Tim theo Ten\n";
                        cout << "[?]Moi nhap lua chon:";
                        int lctim;
                        lctim = nhapSoNguyen();
                        if (lctim == 0) {
                            break;
                        }
                        if (lctim == 1) {
                            string ma;
                            cout << "Ma sach can tim:";
                            cin >> ma;
                            dsSach.inSachDaTimID(ma);
                        } else if (lctim == 2) {
                            string tenSach;
                            cout << "Ten sach can tim:";
                            tenSach = nhapChuoi();
                            dsSach.timSachgandung(tenSach);
                        }
                        break;
                    }
                    case 3: {
                        cout << "\n=============Sach Hien Co===========\n";
                        dsSach.indssach();
                        cout << "===========Muon Sach==========\n";
                        string masach;
                        cout << "Nhap ma sach can muon(nhap 0 de quay ve) :";
                        cin >> masach;
                        if (masach == "0") {
                            break;
                        }
                        nodeSach* p = dsSach.timSachTheoMa(masach);
                        dsmuon.muonSach(masach, taikhoanHienTai.madg, p);
                        luuDSMuon(dsmuon);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 4: {
                        cout << "===========Tra Sach==========\n";
                        string ma;
                        cout << "Nhap ma sach can tra(nhap 0 de quay ve) ";
                        cin >> ma;
                        if (ma == "0") {
                            break;
                        }
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
                        cout << "==========Cap nhat thong tin==========\n";
                        string ten, gioitinh;
                        int tuoi;
                        cout << "Nhap ho va ten cua ban (nhap 0 de quay lai):";
                        ten = nhapChuoi();
                        if (ten == "0") {
                            break;
                        }
                        cout << "Nhap tuoi :";
                        tuoi = nhapSoNguyen();
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