#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "banner.h"
#include "giaodien.h"
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
    if (head == NULL) {
        notifyError("Day sach sach rong ");
        return;
    }
    drawSachHeader();
    nodeSach* p = head;
    int stt = 1;
    while (p != NULL) {
        drawSachRow(
            stt,
            p->data.masach,
            p->data.tensach,
            p->data.tacgia,
            p->data.soluong);
        stt++;
        p = p->next;
    }
    drawSachFooter();
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
        notifyError("Khong tim thay sach co ma: " + ma);
        pauseScreen();
        return;
    }
    if (soluong < 0) {
        notifyError("So luong khong hop le!");
        pauseScreen();
        return;
    }
    a->data.soluong += soluong;
    notifySuccess(("Da them ") + to_string(soluong) + (" cho sach co ma ") + ma);
    pauseScreen();
}

void listSach::inSachDaTimID(string masach) {
    nodeSach* p = timSachTheoMa(masach);
    if (p == NULL) {
        notifyError("Khong tim thay sach");
        return;
    }
    notifySuccess("Tim thay sach");
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
    int i = 1;
    while (true) {
        string id = "DG";
        if (i < 10)
            id += "00" + to_string(i);
        else if (i < 100)
            id += "0" + to_string(i);
        else
            id += to_string(i);

        bool tonTai = false;
        for (nodeDg* p = head; p != NULL; p = p->next) {
            if (p->data.madg == id) {
                tonTai = true;
                break;
            }
        }
        if (tonTai == false) return id;  // nếu chưa tồn tại thì dùng ID này
        i++;
    }
}
void listDg::xoadgID(string id) {
    nodeDg* p = head;
    nodeDg* truoc = NULL;
    while (p != NULL && p->data.madg != id) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        notifyError("Khong tim thay doc gia co ID: " + id);
        pauseScreen();
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
    notifySuccess("Da xoa doc gia co ID: " + id);
    pauseScreen();
}
void listDg::capnhattt(string madg, string ten, int tuoi, string gioitinh) {
    nodeDg* p = timtheoID(madg);
    if (!p) {
        notifyError("Khong tim thay doc gia!");
        return;
    }
    p->data.ten = ten;
    p->data.tuoi = tuoi;
    p->data.gioitinh = gioitinh;
    notifySuccess("Cap nhat thong tin thanh cong");
}
void listDg::inDsdg() {
    if (head == NULL) {
        notifyError("Danh sach doc gia rong");
        return;
    }
    drawDGHeader();
    int stt = 1;
    nodeDg* p = head;
    while (p != NULL) {
        drawDGRow(
            stt,
            p->data.madg,
            p->data.ten,
            p->data.tuoi,
            p->data.gioitinh);
        stt++;
        p = p->next;
    }

    drawDGFooter();
}
void listDg::in1DG(string ma) {
    nodeDg* p = timtheoID(ma);
    if (!p) {
        notifyError("Khong tim thay doc gia");
        return;
    }
    // Màu khung
    setColor(11);
    cout << "\n===============================================================================\n";
    cout << "| " << left << setw(8) << "ID"
         << "| " << left << setw(30) << "HO VA TEN"
         << "| " << left << setw(7) << "TUOI"
         << "| " << left << setw(20) << "GIOI TINH" << " |\n";
    cout << "-------------------------------------------------------------------------------\n";
    resetColor();
    // Màu dữ liệu
    setColor(10);
    cout << "| " << left << setw(8) << p->data.madg
         << "| " << left << setw(30) << p->data.ten
         << "| " << left << setw(7) << p->data.tuoi
         << "| " << left << setw(20) << p->data.gioitinh << " |\n";
    resetColor();
    // Viền dưới
    setColor(11);
    cout << "===============================================================================\n";
    resetColor();
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
        notifyError("Khong ton tai sach co ma: " + masach);
        return;
    }
    if (a->data.soluong <= 0) {
        notifyError("Da het sach");
        return;
    }
    for (auto& x : dsmt) {  // kiem tra da doc gia do da muon sach nay hay chua
        if (x.madg == madg && x.masach == masach && (x.trangthai == "Dang muon" || x.trangthai == "Cho duyet")) {
            notifyError("Ban da gui yeu cau hoac da muon sach nay roi!");
            return;
        }
    }
    muontra mt;
    mt.madg = madg;
    mt.masach = a->data.masach;
    mt.tensach = a->data.tensach;
    mt.trangthai = "Cho duyet";
    dsmt.push_back(mt);
    notifySuccess("Da gui yeu cau den admin");
}
void listMuontra::traSach(string madg, nodeSach* a) {
    if (a == NULL) {
        notifyError("Khong ton tai ma sach vua nhap!");
        return;
    }
    for (auto& x : dsmt) {
        if (x.madg == madg && x.masach == a->data.masach && x.trangthai == "Dang muon") {
            x.trangthai = "Da tra";
            a->data.soluong++;
            notifySuccess("Tra sach thanh cong");
            return;
        }
    }
    notifyError("Khong tim thay sach da muon");
}
void listMuontra::dsDaMuon(string madg) {
    bool flag = false;
    vector<muontra> sachMuon;
    for (auto& x : dsmt) {
        if (x.madg == madg) {
            flag = true;
            sachMuon.push_back(x);
        }
    }
    if (!flag) {
        notifySuccess("Ban chua muon sach nao");
        return;
    }
    // Giao diện bảng đẹp
    drawHeaderSachDaMuon();
    for (auto& x : sachMuon) {
        setColor(10);
        string ten = x.tensach;
        if (ten.size() > 35) ten = ten.substr(0, 32) + "...";
        cout << "| " << left << setw(10) << x.masach
             << "| " << left << setw(35) << ten
             << "| " << left << setw(12) << x.trangthai
             << "|\n";
        resetColor();
    }
    drawFooterSachDaMuon();
}
void listMuontra::intatca() {
    clearScreen();                   // Xóa màn hình trước khi in
    drawHeader("LICH SU MUON TRA");  // Tiêu đề to trên cùng
    if (dsmt.empty()) {
        notifyError("Danh sach muon rong!");
        return;
    }
    drawMuonHeader();  // khung đầu bảng
    setColor(10);
    int stt = 1;
    for (auto& x : dsmt) {
        string tensach = x.tensach;
        if (tensach.size() > 29) tensach = tensach.substr(0, 26) + "...";
        cout << "| " << left << setw(3) << stt++
             << "| " << left << setw(9) << x.madg
             << "| " << left << setw(9) << x.masach
             << "| " << left << setw(29) << tensach
             << "| ";
        if (x.trangthai == "Dang muon")
            setColor(14);  // vàng
        else if (x.trangthai == "Da tra")
            setColor(10);  // xanh lá
        else if (x.trangthai == "Cho duyet")
            setColor(12);  // đỏ
        else
            setColor(7);
        cout << left << setw(9) << x.trangthai;
        resetColor();
        cout << "|\n";
    }
    resetColor();
    drawMuonFooter();  // khung cuối bảng
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
    bool flag = false;
    for (auto& x : dsmt) {
        if (x.trangthai == "Cho duyet") {
            flag = true;
            cout << "- DG: " << x.madg << " | Sach: " << x.tensach << " | Ma: " << x.masach << endl;
        }
    }
    if (flag == false) {
        notifyError("Khong co yeu cau nao dang cho duyet!");
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
string nhapChuoi() {
    string s;
    getline(cin >> ws, s);
    return s;
}
void taoTaiKhoan(taikhoan dstk[], int& soTk, listDg& Dsdocgia, int& sotkUser) {
    taikhoan tk;
    cout << "Nhap ten dang nhap: ";
    tk.username = nhapChuoi();
    for (int i = 0; i < soTk; i++) {
        if (dstk[i].username == tk.username) {
            notifyError("Ten dang nhap da ton tai");
            return;
        }
    }
    cout << "Nhap mat khau: ";
    tk.pasword = nhapChuoi();
    string vaitro;
    while (true) {
        cout << "Nhap vai tro (admin/user): ";
        cin >> vaitro;
        for (auto& c : vaitro) c = tolower(c);  // chuyen ve chu thuong
        if (vaitro == "admin" || vaitro == "user") {
            tk.vaitro = vaitro;
            break;
        }
        notifyError("Vai tro khong hop le .Vui long nhap theo yeu cau!");
    }
    if (tk.vaitro == "user") {
        tk.madg = Dsdocgia.taoIDtudong();
        docGia dg;
        dg.madg = tk.madg;
        dg.ten = "Chua cap nhat";
        dg.tuoi = 0;
        dg.gioitinh = "Chua cap nhat";
        Dsdocgia.themcuoi(dg);
        notifySuccess("Tao tai khoan thanh cong .ID :" + dg.madg);
    } else {
        tk.madg = "N/A";
        notifySuccess("Tao tai khoan thanh cong.");
    }
    dstk[soTk++] = tk;
}
void doiMk(taikhoan& tkhientai, taikhoan dstk[], int sotk) {
    drawHeader("DOI MAT KHAU");
    string mkCu, mkMoi;
    cout << "Nhap mat khau cu :";
    cin >> mkCu;
    if (mkCu != tkhientai.pasword) {
        notifyError("Mat khau khong dung");
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
    notifySuccess("Doi mat khau thanh cong");
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
    system("chcp 65001 > nul");
    system("mode con: cols=160 lines=50");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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
    drawTHUVIEN_Banner();
    hieuungloading();
    loadingEffect();
    cout << "Tai du lieu thanh cong .";
    while (true) {
        vector<string> menuLogin = {
            "1. Dang nhap",
            "2. Dang ky tai khoan",
            "3. Thoat"};
        clearScreen();
        drawTHUVIEN_Banner();
        drawMenuBox(menuLogin, "DANG NHAP HE THONG");
        int lcdn;
        lcdn = nhapSoNguyen();
        if (lcdn == 1) {  // dang nhap
            clearScreen();
            drawTHUVIEN_Banner();
            drawHeader("Dang nhap");
            string user, pass;
            cout << "Ten dang nhap:";
            cin >> user;
            cout << "Mat khau:";
            cin >> pass;
            if (dangnhap(dstk, sotk, user, pass, taikhoanHienTai)) {
                daDangNhap = true;
                notifySuccess("Dang nhap thanh cong");
                pauseScreen();
            } else {
                notifyError("Dang nhap that bai");
                pauseScreen();
            }
        } else if (lcdn == 2) {  // dang ky tk
            clearScreen();
            drawTHUVIEN_Banner();
            drawHeader("Dang ky tai khoan");
            taoTaiKhoan(dstk, sotk, dsDg, sotkUser);
            luudsdocgia(dsDg);
            pauseScreen();
        } else if (lcdn == 3) {  // thoat
            return 0;
        }
        while (daDangNhap == true) {
            if (taikhoanHienTai.vaitro == "admin") {
                vector<string> menuAd = {
                    "1. Them sach",
                    "2. Xoa sach",
                    "3. Xoa doc gia",
                    "4. Tim sach",
                    "5. Them so luong sach",
                    "6. Duyet yeu cau",
                    "7. Hien thi du lieu",
                    "8. Doi mat khau",
                    "9. Dang xuat"};
                clearScreen();
                drawTHUVIEN_Banner();
                drawMenuBox(menuAd, "ADMIN MENU");
                int lc;
                lc = nhapSoNguyen();
                switch (lc) {
                    case 1: {  // THEM SACH
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawSubMenu("THEM SACH MOI", {"Quay lai",
                                                      "Them o dau",
                                                      "Them o cuoi",
                                                      "Them o vi tri bat ky"});
                        int lcthem;
                        while (true) {
                            cout << "→ Nhap lua chon: ";
                            lcthem = nhapSoNguyen();
                            if (lcthem >= 0 && lcthem <= 3) {
                                break;
                            }
                            notifyError("Lua chon khong hop le.Vui long nhap lai (0-3)");
                        }
                        if (lcthem == 0) {
                            break;
                        }
                        sach a;
                        if (dsSach.tonTaiMaSach(a.masach)) {
                            notifyError("Ma sach da ton tai khong the them!");
                            pauseScreen();
                            break;
                        }
                        if (lcthem == 1) {
                            nhapSach(a);
                            dsSach.themsachdauds(a);
                        } else if (lcthem == 2) {
                            nhapSach(a);
                            dsSach.themsachcuoids(a);
                        } else if (lcthem == 3) {
                            int pos;
                            cout << "Nhap vi tri muon them :";
                            nhapSach(a);
                            pos = nhapSoNguyen();
                            dsSach.themsachbatkids(a, pos);
                        }
                        luuDSSach(dsSach);
                        cout << "Them sach thanh cong.";
                        break;
                    }
                    case 2: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("XOA SACH");
                        dsSach.indssach();
                        cout << "\n";
                        drawSubMenu("CHON HINH THUC XOA", {"Quay lai",
                                                           "Xoa theo Ma",
                                                           "Xoa theo Ten"});
                        int lcxoa;
                        while (true) {
                            cout << "→ Nhap lua chon: ";
                            lcxoa = nhapSoNguyen();
                            if (lcxoa >= 0 && lcxoa <= 2) {
                                break;
                            }
                            notifyError("Lua chon khong hop le.Vui long nhap lai (0-2)");
                        }
                        if (lcxoa == 0) {
                            break;
                        }
                        if (lcxoa == 1) {
                            cout << "Nhap Ma can xoa :";
                            string masach;
                            cin >> masach;
                            string masachXoa = masach;
                            if (dsSach.isempty()) {
                                notifyError("Danh sach hien dang rong!");
                                pauseScreen();
                            } else if (dsmuon.kiemtraSachDangMuonID(masach)) {
                                notifyError("Sach nay hien dang duoc doc gia muon. Khong the xoa!");
                                pauseScreen();
                            } else {
                                dsSach.xoasachbangma(masach);
                                notifySuccess("Da xoa sach co ma " + masach);
                                pauseScreen();
                            }
                            dsmuon.xoaLichSuTheoSach(masach);
                            luuDSSach(dsSach);
                        } else if (lcxoa == 2) {
                            cout << "Nhap ten sach can xoa: ";
                            string tenSach = nhapChuoi();
                            if (dsSach.isempty()) {
                                notifyError("Danh sach dang rong!");
                                pauseScreen();
                            } else {
                                nodeSach* p = dsSach.timSachTheoTen(tenSach);
                                if (p == NULL) {
                                    notifyError("Khong tim thay sach co ten: " + tenSach);
                                    pauseScreen();
                                } else {
                                    string tenSachXoa = p->data.tensach;
                                    string maXoa = p->data.masach;
                                    // neu sach dang dc muon => ko xoa
                                    if (dsmuon.kiemtraSachDangMuonID(maXoa)) {
                                        notifyError("Sach dang duoc muon. Khong the xoa!");
                                        pauseScreen();
                                    } else {
                                        dsSach.xoasachbangma(maXoa);
                                        dsmuon.xoaLichSuTheoSach(maXoa);
                                        luuDSSach(dsSach);
                                        notifySuccess("Da xoa sach co ten: " + tenSach);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 3: {  // XOA DOC GIA
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("XOA DOC GIA");
                        dsDg.inDsdg();
                        cout << "\n";
                        cout << "Nhap ID doc gia (nhap 0 de quay lai):";
                        string id;
                        cin >> id;
                        if (id == "0") {
                            break;
                        }
                        if (dsDg.isEmpty()) {
                            notifyError("Danh sach doc gia dang rong!");
                            pauseScreen();
                            break;
                        } else if (!dsDg.timtheoID(id)) {
                            notifyError("Khong co doc gia nay!");
                            pauseScreen();
                        } else if (dsmuon.kiemtraMuonSachIDDG(id)) {
                            notifyError("Doc gia dang muon sach.Khong the xoa!");
                            pauseScreen();
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
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawSubMenu("TIM SACH", {"Quay ve", "Tim theo Ma", "Tim theo Ten"});
                        int lctim;
                        while (true) {
                            cout << "→ Nhap lua chon: ";
                            lctim = nhapSoNguyen();
                            if (lctim >= 0 && lctim <= 2) {
                                break;
                            }
                            notifyError("Lua chon khong hop le.Vui long nhap lai (0-2)");
                        }
                        if (lctim == 0) {
                            break;
                        }
                        if (lctim == 1) {
                            cout << "Nhap ma sach can tim:";
                            string masach;
                            cin >> masach;
                            dsSach.inSachDaTimID(masach);
                            pauseScreen();
                        } else if (lctim == 2) {
                            cout << "Nhap ten sach can tim:";
                            string tensach = nhapChuoi();
                            dsSach.timSachgandung(tensach);
                            pauseScreen();
                        }
                        break;
                    }
                    case 5: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("Them so luong sach");
                        dsSach.indssach();
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
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("Duyet yeu cau muon sach");
                        dsmuon.inYCmuon();
                        string madg, masach;
                        cout << "Nhap ma doc gia can duyet(nhap 0 de quay ve): ";
                        madg = nhapChuoi();
                        if (madg == "0") {
                            break;
                        }
                        cout << "Nhap ma sach can duyet: ";
                        masach = nhapChuoi();
                        nodeSach* a = dsSach.timSachTheoMa(masach);
                        if (!a) {
                            notifyError("Khong hop le!");
                            pauseScreen();
                            break;
                        }
                        if (a->data.soluong <= 0) {
                            notifyError("Da het sach.Khong the duyet!");
                            pauseScreen();
                            break;
                        }
                        dsmuon.duyetYC(madg, masach, a);
                        notifySuccess("Duyet thanh cong");
                        pauseScreen();
                        break;
                    }
                    case 7: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawSubMenu("HIEN THI DU LIEU", {"Quay ve", "Xem danh sach sach", "Xem danh sach doc gia", "Xem lich su muon"});
                        int abc;
                        while (true) {
                            cout << "→ Nhap lua chon: ";
                            abc = nhapSoNguyen();
                            if (abc >= 0 && abc <= 3) {
                                break;
                            }
                            notifyError("Lua chon khong hop le.Vui long nhap lai (0-3)");
                        }
                        if (abc == 0) {
                            break;
                        }
                        if (abc == 1) {
                            dsSach.indssach();
                            pauseScreen();
                        } else if (abc == 2) {
                            dsDg.inDsdg();
                            pauseScreen();
                        } else if (abc == 3) {
                            dsmuon.intatca();
                            pauseScreen();
                        }
                        break;
                    }
                    case 8: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        doiMk(taikhoanHienTai, dstk, sotk);
                        pauseScreen();
                        break;
                    }
                    case 9: {
                        notifyError("Da dang xuat");
                        daDangNhap = false;
                        pauseScreen();
                        break;
                        default:
                            notifyError("Lua chon khong hop le!");
                            pauseScreen();
                    }
                }
            } else if (taikhoanHienTai.vaitro == "user") {
                clearScreen();
                drawTHUVIEN_Banner();
                vector<string> menuUserVec = {
                    "1. Xem sach",
                    "2. Tim sach",
                    "3. Muon sach",
                    "4. Tra sach",
                    "5. Xem sach da muon",
                    "6. Xem thong tin ca nhan",
                    "7. Cap nhat thong tin ca nhan",
                    "8. Doi mat khau",
                    "9. Dang xuat"};
                drawMenuBox(menuUserVec, "USER MENU");
                int lc;
                lc = nhapSoNguyen();
                switch (lc) {
                    case 1:
                        clearScreen();
                        drawTHUVIEN_Banner();
                        dsSach.indssach();
                        pauseScreen();
                        break;
                    case 2: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawSubMenu("TIM SACH", {"Quay ve", "Tim theo Ma", "Tim theo Ten"});
                        int lctim;
                        while (true) {
                            cout << "→ Nhap lua chon: ";
                            lctim = nhapSoNguyen();
                            if (lctim >= 0 && lctim <= 2) {
                                break;
                            }
                            notifyError("Lua chon khong hop le.Vui long nhap lai (0-2)");
                        }
                        if (lctim == 0) {
                            break;
                        }
                        if (lctim == 1) {
                            cout << "Nhap ma sach can tim:";
                            string masach;
                            cin >> masach;
                            dsSach.inSachDaTimID(masach);
                            pauseScreen();
                        } else if (lctim == 2) {
                            cout << "Nhap ten sach can tim:";
                            string tensach = nhapChuoi();
                            dsSach.timSachgandung(tensach);
                            pauseScreen();
                        }
                        break;
                    }
                    case 3: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("MUON SACH");
                        dsSach.indssach();
                        string masach;
                        cout << "Nhap ma sach can muon(nhap 0 de quay ve) :";
                        cin >> masach;
                        if (masach == "0") {
                            break;
                        }
                        nodeSach* p = dsSach.timSachTheoMa(masach);
                        dsmuon.muonSach(masach, taikhoanHienTai.madg, p);
                        pauseScreen();
                        luuDSMuon(dsmuon);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 4: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("TRA SACH");
                        string ma;
                        cout << "Nhap ma sach can tra(nhap 0 de quay ve) :";
                        cin >> ma;
                        if (ma == "0") {
                            break;
                        }
                        nodeSach* p = dsSach.timSachTheoMa(ma);
                        dsmuon.traSach(taikhoanHienTai.madg, p);
                        pauseScreen();
                        luuDSMuon(dsmuon);
                        luuDSSach(dsSach);
                        break;
                    }
                    case 5: {
                        string madg = taikhoanHienTai.madg;
                        dsmuon.dsDaMuon(madg);
                        pauseScreen();
                        break;
                    }
                    case 6:
                        dsDg.in1DG(taikhoanHienTai.madg);
                        pauseScreen();
                        break;
                    case 7: {
                        clearScreen();
                        drawTHUVIEN_Banner();
                        drawHeader("CAP NHAT THONG TIN CA NHAN");
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
                        pauseScreen();
                        luudsdocgia(dsDg);
                        break;
                    }
                    case 8:
                        clearScreen();
                        drawTHUVIEN_Banner();
                        doiMk(taikhoanHienTai, dstk, sotk);
                        pauseScreen();
                        break;
                    case 9:
                        notifySuccess("Da dang xuat");
                        pauseScreen();
                        daDangNhap = false;
                        break;
                    default:
                        notifyError("Lua chon khong hop le!");
                }
            }
        }
        luudsdocgia(dsDg);
        luudstk(dstk, sotk);
        luuDSSach(dsSach);
        luuDSMuon(dsmuon);
    }
}