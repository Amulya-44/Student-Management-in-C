# 📚 Student Management System (Binary File Edition v2.0)

A lightweight, terminal-based **Student Management System** developed in C for managing academic records. This application provides basic CRUD operations, dynamic sorting, automated academic grade/status evaluations, and binary file persistence.

## 📸 Screenshots

<img width="979" height="835" alt="image" src="https://github.com/user-attachments/assets/effadbae-76c8-40a5-9b26-dcdbaaab6fa0" />

<img width="1239" height="786" alt="image" src="https://github.com/user-attachments/assets/1a7cbf27-ca98-40dd-a01e-d0efd7d483a4" />

<img width="1161" height="522" alt="image" src="https://github.com/user-attachments/assets/bc792961-a0b6-4b1c-b603-2db86e2de006" />

<img width="1034" height="709" alt="image" src="https://github.com/user-attachments/assets/7d372b7f-426f-4699-9635-3b3cb364e166" />

## 📌 Project Overview

This application serves as a First Semester C Programming project designed to demonstrate core concepts:

* **Structured Data Types (`struct`)**: Nested structures for storing personal profiles and subject marks.
* **Binary File Handling**: Persistent storage in `student.bin` using `fread` and `fwrite`.
* **Data Validation**: Duplicate Student ID checks for both single inputs and batch additions.
* **Automated Calculations**: Dynamic sum, percentage, and pass/fail evaluation based on preset criteria (`PASS_MARK = 40`).

## ✨ Key Features

* **Add Student Records**: Input multiple student profiles at once with automatic ID uniqueness checks.
* **View All Records**: Displays a formatted table listing student IDs, names, contact info, total marks, and percentages.
* **Update Records**: Edit specific fields (Name, Email, Phone, or Subject Marks) while skipping unchanged details.
* **Delete Records**: Remove specific students by ID without affecting other stored data.
* **Search Profile**: Look up a student by ID to generate a full academic profile card.
* **Sort Leaderboard**: Ranks all records in descending order based on total marks obtained.
* **Pass / Fail Analytics Report**: Categorizes students into passing and failing tables, listing specific failed subjects for failing students.
* **Delete ALL Records**: Protected bulk delete feature secured with master passkey authentication (`*delete*`).

## 🛠️ Data Structure

```c
struct marks {
    int phy;    // Physics
    int maths;  // Mathematics
    int cpro;   // C Programming
    int fee;    // Fundamentals of Electrical & Electronics
    int edrg;   // Engineering Drawing
    float per;  // Percentage score
    int t;      // Total marks achieved
};

struct student {
    char name[50];
    char email[50];
    int s_id;
    char ph_no[11];
    struct marks m;
};
```

## 🚀 How to Run

### Prerequisites

* Any standard C compiler (GCC, Clang, MSVC, or MinGW).

### Compilation

Run the following command in your terminal:

```bash
gcc -o student_mgmt main.c
```

### Execution

**Linux / macOS:**

```bash
./student_mgmt
```

**Windows:**

```bash
student_mgmt.exe
```

## ⚠️ Program Limitations

* **Fixed Capacity (`MAX = 100`)**: Statically limited to holding a maximum of 100 records in memory during operations.
* **Input Formatting (`scanf`)**: Standard `%s` reading means names, emails, or inputs containing spaces will disrupt line alignment.
* **Binary Portability**: Binary files created on one OS architecture may not read cleanly on another without recompilation.
* **Hardcoded Subject Setup**: Subject lists and passing criteria (`PASS_MARK = 40`) are defined directly within source code macro definitions.

## 🔮 Future Improvements

* [ ] Implement Dynamic Memory Allocation (`malloc`/`realloc`) to remove the static 100-student cap.
* [ ] Replace `scanf()` with `fgets()` to handle multi-word names containing spaces.
* [ ] Add dynamic subject configuration to support different academic departments.
* [ ] Add CSV export functionality to allow viewing records in spreadsheet software.
