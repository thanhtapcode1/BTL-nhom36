#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
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
    if (x.madg == madg && x.masach == masach &&
        (x.trangthai == "Dang muon" || x.trangthai == "Cho duyet")) {
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
  bool flag = false;
  cout << "========= Sach da muon =========\n";
  for (auto& x : dsmt) {
    if (x.madg == madg) {
      flag = true;
      cout << "- Ma sach:" << x.masach << " -Ten Sach:" << x.tensach
           << " -Trang thai:" << x.trangthai << endl;
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
  cout << left << setw(10) << "Ma DG" << setw(35) << "Sach Da Muon" << setw(20)
       << "Trang thai" << endl;
  cout << string(65, '-') << endl;  // in ra 65 ki tu -
  for (auto& x : dsmt) {
    cout << left << setw(10) << x.madg << setw(35) << x.tensach << setw(20)
         << x.trangthai << endl;
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
      cout << "- DG: " << x.madg << " | Sach: " << x.tensach
           << " | Ma: " << x.masach << endl;
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