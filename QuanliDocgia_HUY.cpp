#include <iomanip>
#include <iostream>
using namespace std;

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
    if (p->data.madg == id) return p;
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
  cout << "\n=================================================================="
          "==========\n";
  cout << "| " << left << setw(8) << "ID";
  cout << "| " << left << setw(30) << "HO VA TEN";
  cout << "| " << left << setw(7) << "TUOI";
  cout << "| " << left << setw(20) << "GIOI TINH" << setw(3) << " |";
  cout << "\n------------------------------------------------------------------"
          "---------\n";
  for (nodeDg* p = head; p != NULL; p = p->next) {
    cout << "| " << left << setw(8) << p->data.madg;
    cout << "| " << left << setw(30) << p->data.ten;
    cout << "| " << left << setw(7) << p->data.tuoi;
    cout << "| " << left << setw(20) << p->data.gioitinh << setw(3) << " |";
    cout << endl;
  }
  cout << "===================================================================="
          "========\n";
}
void listDg::in1DG(string ma) {
  nodeDg* p = timtheoID(ma);
  if (!p) {
    cout << "Khong tim thay doc gia!\n";
    return;
  }
  cout << "\n=================================================================="
          "=========\n";
  cout << "| " << left << setw(8) << "ID";
  cout << "| " << left << setw(30) << "HO VA TEN";
  cout << "| " << left << setw(7) << "TUOI";
  cout << "| " << left << setw(20) << "GIOI TINH" << setw(3) << " |";
  cout << "\n------------------------------------------------------------------"
          "---------\n";
  cout << "| " << left << setw(8) << p->data.madg;
  cout << "| " << left << setw(30) << p->data.ten;
  cout << "| " << left << setw(7) << p->data.tuoi;
  cout << "| " << left << setw(20) << p->data.gioitinh << setw(3) << " |";
  cout << endl;
  cout << "===================================================================="
          "========\n";
}