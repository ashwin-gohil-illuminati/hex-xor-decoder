![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Malware Analysis](https://img.shields.io/badge/Malware%20Analysis-Foundation-red?style=for-the-badge)
![Reverse Engineering](https://img.shields.io/badge/Reverse%20Engineering-Triage-success?style=for-the-badge)

# Raw Byte & Cryptography Triage Tool

A custom C++ utility built to parse raw binary data directly from disk, format it into a standard 16-byte reverse-engineering hex view, and demonstrate symmetric XOR cryptography. This tool serves as the foundational stepping stone for understanding how malware obfuscates strings and how analysts read raw machine code.

---

## 🧬 Core Concepts Demonstrated

This tool implements several bedrock concepts required for malware analysis and reverse engineering:

* **Raw Binary I/O:** Safely extracting bytes from a file using `std::ios::binary` to prevent OS-level character corruption.
* **Hexadecimal Formatting:** Converting raw decimal bytes into standard 2-digit uppercase Hex for readability, enforcing a strict 16-byte width structure (`offset % 16 == 0`) used by professional disassemblers.
* **Bitwise Symmetrical Cryptography (XOR):** Utilizing the XOR operator (`^`) with a static key (`0x5A`) to encode plain text. The utility proves the symmetric nature of XOR by applying the exact same key to the encoded data to successfully recover the original plaintext.

---

## ⚙️ Workflow & Execution

1. Read raw target file (`hexdumpdata.txt`).
2. Generate an unmodified, 16-column Base-16 hexadecimal dump.
3. Apply the XOR bitwise operation against a 1-byte key.
4. Output the obfuscated hex values.
5. Re-apply the XOR key to the obfuscated values to prove successful decryption.

### 💻 Compilation

Compiled using MinGW (GCC) for Windows environments:
```bash
g++ HexDumpUtility.cpp -o HexDumpUtility.exe
```


## 🖥️ Terminal Output

<img width="561" height="359" alt="Screenshot_2026-06-10_12-19-48" src="https://github.com/user-attachments/assets/6e39c861-5788-4e19-9639-be7329eae531" />



