#include <iomanip>
#include <iostream>
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
    if (p->data.masach == ma) return true;
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
  cout << left << setw(5) << "STT" << setw(12) << "Ma sach" << setw(35)
       << "Ten sach" << setw(25) << "Tac gia" << setw(10) << "So luong" << endl;
  cout << string(90, '-') << endl;
  int i = 1;
  for (nodeSach* p = head; p != NULL; p = p->next) {
    cout << left << setw(5) << i++ << setw(12) << p->data.masach << setw(35)
         << p->data.tensach << setw(25) << p->data.tacgia << setw(10)
         << p->data.soluong << endl;
  }
}
nodeSach* listSach::timSachTheoMa(string ma) {
  nodeSach* p = head;
  while (p != NULL) {
    if (p->data.masach == ma) return p;
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
    if (temp == ten) return p;
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
  cout << "Masach:" << p->data.masach << " | Ten:" << p->data.tensach
       << " | TacGia:" << p->data.tacgia << " | SL:" << p->data.soluong;
}