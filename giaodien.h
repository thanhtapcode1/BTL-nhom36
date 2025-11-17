#pragma once
#include <limits.h>
#define byte WindowsByte
#include <windows.h>
#undef byte
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ====== COLOR ======
inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
inline void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// ====== CLEAR SCREEN ======
inline void clearScreen() {
    system("cls");
}
// ====== TITLE (CĂN GIỮA) ======
inline void drawTitle(const string& title, int width = 50) {
    int padLeft = (width - (int)title.length()) / 2;
    cout << "+" << string(width, '=') << "+\n";
    cout << "|" << string(padLeft, ' ') << title
         << string(width - padLeft - title.length(), ' ') << "|\n";
    cout << "+" << string(width, '=') << "+\n";
}

// ====== MENU KHUNG ĐẸP ======
inline void drawMenuBox(const vector<string>& items, const string& title = "MENU") {
    int width = 35;

    // ===== KHUNG TRÊN =====
    setColor(11);
    cout << "┌" << string(width, '-') << "┐\n";

    // ===== TIÊU ĐỀ =====
    int padLeft = (width - (int)title.length()) / 2;
    cout << "│"
         << string(padLeft, ' ')
         << title
         << string(width - padLeft - (int)title.length(), ' ')
         << "│\n";

    // ===== DƯỜNG NGANG =====
    cout << "├" << string(width, '-') << "┤\n";
    resetColor();

    // ===== NỘI DUNG =====
    setColor(10);
    for (auto& line : items) {
        cout << "│ " << left << setw(width - 1) << line << "│\n";
    }

    // ===== KHUNG DƯỚI =====
    resetColor();
    setColor(11);
    cout << "└" << string(width, '-') << "┘\n\n";
    resetColor();

    cout << "→ Nhap lua chon: ";
}
inline void drawHeader(const string& title, int width = 60) {
    setColor(11);
    cout << "╔" << string(width, '-') << "╗\n";

    int left = (width - title.length()) / 2;
    cout << "║" << string(left, ' ') << title
         << string(width - left - title.length(), ' ') << "║\n";

    cout << "╚" << string(width, '-') << "╝\n\n";
    resetColor();
}
inline void drawSubMenu(const string& title, const vector<string>& items) {
    // KHÔNG clearScreen
    setColor(11);

    // Viền trên
    cout << "┌" << string(38, '-') << "┐\n";

    // Tiêu đề canh giữa
    int pad = (38 - title.length()) / 2;
    cout << "│" << string(pad, ' ') << title
         << string(38 - pad - title.length(), ' ') << "│\n";

    cout << "├" << string(38, '-') << "┤\n";
    resetColor();

    // Danh sách lựa chọn
    setColor(10);
    for (int i = 0; i < items.size(); i++) {
        string line = to_string(i) + ". " + items[i];
        cout << "│ " << left << setw(37) << line << "│\n";
    }
    resetColor();

    // Viền dưới
    setColor(11);
    cout << "└" << string(38, '-') << "┘\n";
    resetColor();
}
inline void notifySuccess(const string& msg) {
    setColor(10);
    cout << "\n✔ " << msg << "\n";
    resetColor();
}

inline void notifyError(const string& msg) {
    setColor(12);
    cout << "\n✘ " << msg << "\n";
    resetColor();
}
inline void drawInfoBox(const vector<string>& lines, int width = 60) {
    setColor(11);
    cout << "╔" << string(width, '-') << "╗\n";
    resetColor();

    for (auto& line : lines) {
        cout << "║ " << left << setw(width - 1) << line << "║\n";
    }

    setColor(11);
    cout << "╚" << string(width, '-') << "╝\n";
    resetColor();
}
inline void drawListHeader(const string& title) {
    setColor(14);
    cout << "\n=== " << title << " ===\n\n";
    resetColor();
}
inline void pauseScreen() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.clear();
    cin.sync();  // xoá toàn bộ ký tự còn trong buffer
    cin.get();   // chờ Enter thật
}
inline void hieuungloading() {
    for (int i = 0; i <= 100; i += 5) {  // them vao cho dep
        cout << MAGENTA << "\rDang tai... " << i << "%";
        Sleep(50);
    }
}
inline void drawSachHeader() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(8, '-')
         << "+" << string(32, '-')
         << "+" << string(20, '-')
         << "+" << string(8, '-')
         << "+\n";

    string title = "DANH SACH SACH HIEN CO";
    int width = 4 + 8 + 32 + 20 + 8 + 5 - 1;  // tổng chiều dài hàng
    int pad = (width - title.size()) / 2;

    cout << "|" << string(width, ' ') << "|\n";
    cout << "|" << string(pad, ' ')
         << title
         << string(width - pad - title.size(), ' ')
         << "|\n";
    cout << "|" << string(width, ' ') << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(8, '-')
         << "+" << string(32, '-')
         << "+" << string(20, '-')
         << "+" << string(8, '-')
         << "+\n";

    cout << "| " << left << setw(3) << "STT"
         << "| " << left << setw(7) << "MA"
         << "| " << left << setw(31) << "TEN SACH"
         << "| " << left << setw(19) << "TAC GIA"
         << "| " << left << setw(7) << "SLG"
         << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(8, '-')
         << "+" << string(32, '-')
         << "+" << string(20, '-')
         << "+" << string(8, '-')
         << "+\n";
    resetColor();
}

inline void drawSachRow(int stt, string ma, string ten, string tg, int sl) {
    setColor(10);

    if (ten.size() > 31) ten = ten.substr(0, 28) + "...";
    if (tg.size() > 19) tg = tg.substr(0, 16) + "...";

    cout << "| " << left << setw(3) << stt
         << "| " << left << setw(7) << ma
         << "| " << left << setw(31) << ten
         << "| " << left << setw(19) << tg
         << "| " << right << setw(7) << sl
         << "|\n";

    resetColor();
}

inline void drawSachFooter() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(8, '-')
         << "+" << string(32, '-')
         << "+" << string(20, '-')
         << "+" << string(8, '-')
         << "+\n";
    resetColor();
}
inline void drawDGHeader() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(12, '-')
         << "+" << string(25, '-')
         << "+" << string(10, '-')
         << "+" << string(15, '-')
         << "+\n";

    string title = "DANH SACH DOC GIA";
    int width = 4 + 12 + 25 + 10 + 15 + 5 - 1;  // chieu dai
    int pad = (width - title.size()) / 2;

    cout << "|" << string(width, ' ') << "|\n";
    cout << "|" << string(pad, ' ')
         << title
         << string(width - pad - title.size(), ' ')
         << "|\n";
    cout << "|" << string(width, ' ') << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(12, '-')
         << "+" << string(25, '-')
         << "+" << string(10, '-')
         << "+" << string(15, '-')
         << "+\n";

    cout << "| " << left << setw(3) << "STT"
         << "| " << left << setw(11) << "MA DG"
         << "| " << left << setw(24) << "TEN DOC GIA"
         << "| " << left << setw(9) << "TUOI"
         << "| " << left << setw(14) << "GIOI TINH"
         << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(12, '-')
         << "+" << string(25, '-')
         << "+" << string(10, '-')
         << "+" << string(15, '-')
         << "+\n";
    resetColor();
}

inline void drawDGFooter() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(12, '-')
         << "+" << string(25, '-')
         << "+" << string(10, '-')
         << "+" << string(15, '-')
         << "+\n";
    resetColor();
}

inline void drawDGRow(int stt, string madg, string ten, int tuoi, string gioitinh) {
    setColor(10);
    if (ten.size() > 24) ten = ten.substr(0, 21) + "...";

    cout << "| " << left << setw(3) << stt
         << "| " << left << setw(11) << madg
         << "| " << left << setw(24) << ten
         << "| " << left << setw(9) << tuoi
         << "| " << left << setw(14) << gioitinh
         << "|\n";

    resetColor();
}
//============================================================
inline void drawMuonHeader() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(10, '-')
         << "+" << string(10, '-')
         << "+" << string(30, '-')
         << "+" << string(10, '-')
         << "+\n";

    string title = "DANH SACH MUON TRA";
    int width = 4 + 10 + 10 + 30 + 10 + 5 - 1;
    int pad = (width - title.size()) / 2;

    cout << "|" << string(width, ' ') << "|\n";
    cout << "|" << string(pad, ' ')
         << title
         << string(width - pad - title.size(), ' ')
         << "|\n";
    cout << "|" << string(width, ' ') << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(10, '-')
         << "+" << string(10, '-')
         << "+" << string(30, '-')
         << "+" << string(10, '-')
         << "+\n";

    cout << "| " << left << setw(3) << "STT"
         << "| " << left << setw(9) << "MA DG"
         << "| " << left << setw(9) << "MA SACH"
         << "| " << left << setw(29) << "TEN SACH"
         << "| " << left << setw(9) << "TRANGTHAI"
         << "|\n";

    cout << "+" << string(4, '-')
         << "+" << string(10, '-')
         << "+" << string(10, '-')
         << "+" << string(30, '-')
         << "+" << string(10, '-')
         << "+\n";
    resetColor();
}

inline void drawMuonFooter() {
    setColor(11);
    cout << "+" << string(4, '-')
         << "+" << string(10, '-')
         << "+" << string(10, '-')
         << "+" << string(30, '-')
         << "+" << string(10, '-')
         << "+\n";
    resetColor();
}
//==============================================================
inline void drawHeaderSachDaMuon() {
    setColor(11);
    cout << "+" << string(62, '-') << "+\n";
    cout << "|                     CAC SACH BAN DA MUON                     |\n";
    cout << "+" << string(62, '-') << "+\n";
    cout << "| " << left << setw(10) << "MA SACH"
         << "| " << left << setw(35) << "TEN SACH"
         << "| " << left << setw(12) << "TRANG THAI"
         << "|\n";
    cout << "+" << string(62, '-') << "+\n";
    resetColor();
}
inline void drawFooterSachDaMuon() {
    setColor(11);
    cout << "+" << string(62, '-') << "+\n";
    resetColor();
}