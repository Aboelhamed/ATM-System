# 🏦 ATM System (C++ Console Application)

## 📌 Overview

This project is a simple **ATM System** implemented in **C++** using file handling.
It simulates basic banking operations such as withdrawing, depositing, and checking account balance.

The system reads and writes client data from a file and allows users to interact through a console-based menu.

---

## 🚀 Features

* 🔐 Login باستخدام **Account Number & Pin Code**
* 💵 Quick Withdraw (سحب سريع بمبالغ محددة)
* 💰 Normal Withdraw (سحب مبلغ مخصص)
* ➕ Deposit (إيداع)
* 📊 Check Balance (عرض الرصيد)
* 🔄 تحديث البيانات داخل الملف بعد كل عملية

---

## 📂 File Structure

Client data is stored in a text file:

```
clients data file.txt
```

Each line يمثل عميل واحد بالصيغة:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
```

### Example:

```
12345#//#1111#//#Ali#//#01000000000#//#5000
```

---

## ⚙️ How It Works

1. البرنامج بيقرأ البيانات من الملف باستخدام:

   * `LoadClientDataFromFile()`

2. بيحوّل كل سطر إلى struct:

   * `ConvertLineStringToRecord()`

3. بعد أي عملية (Withdraw / Deposit):

   * يتم تحديث `CurrentClient`
   * ثم حفظ كل البيانات مرة أخرى باستخدام:

     * `SaveClientData()`

---

## 🛠️ Technologies Used

* C++
* File Handling (`fstream`)
* STL (`vector`, `string`)
* Console UI

---

## ▶️ How to Run

1. تأكد إن الملف موجود في المسار:

```
..\Bank system\clients data file.txt
```

أو غيّر المسار في الكود:

```cpp
static const string FileName = "D:\\clients.txt";
```

2. Compile & Run:

```
g++ main.cpp -o atm
atm.exe
```

---

## ⚠️ Important Notes

* لازم كل سطر في الملف يكون بنفس الفورمات
* أي سطر ناقص أو فيه بيانات غلط ممكن يسبب crash
* النظام لا يدعم التعديل المباشر داخل الملف، بل:

  * قراءة → تعديل → إعادة كتابة

---

## 🧠 Future Improvements

* 🔒 تشفير Pin Code
* 🧾 Transaction History (Logs)
* 👥 Multi-user system مع صلاحيات
* 🧱 تحويل المشروع إلى OOP
* 🌐 واجهة GUI بدل Console

---

## 👨‍💻 Author

Developed by: **Aboelhamed Elsayed**

---

## ⭐ Notes

This project is great for practicing:

* File handling
* Data parsing
* Structs and vectors
* Real-world system simulation

---
