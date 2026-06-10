#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>


/*
Compile instruction with use of MinGw
g++ HexDumpUtility.cpp -o HexDumpUtility.exe

wine HexDumpUtility.exe
or
./HexDumpUtility.exe 
*/


int main() {
    std::vector<unsigned char> buffer;
    // Open the file strictly in binary mode
    std::ifstream file("hexdumpdata.txt", std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open dummy.txt" << std::endl;
        return 1;
    }

    char byte;
    // Read the file byte by byte until the end
    int offset = 0; //Tracking memory address

    // --- ORIGINAL HEX DUMP ---
    std::cout << "\n[+] TARGET FILE: hexdumpdata.txt" << std::endl;
    std::cout << "[+] STATUS: RAW UNMODIFIED BYTES (PLAINTEXT)" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "Offset(h)  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    while (file.get(byte)) {
        // We cast to 'unsigned char' so values stay between 0 and 255.
        // If we don't, values above 127 will print as negative numbers.

        if (offset % 16 == 0) {
            std::cout << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << offset << "   ";
        }
        unsigned char rawByte = static_cast<unsigned char>(byte); // A char gives an integer so it is a decimal
        buffer.push_back(rawByte);
        // Print the actual byte in 2-digit uppercase Hex
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(rawByte) << " ";
        offset++;

        if (offset % 16 == 0) {
            std::cout << std::endl;
        }
    }

    if (offset % 16 != 0) {
        std::cout << std::endl;
    }

    file.close();

    // --- XOR ENCODED HEX DUMP ---
    std::cout << "\n--- ENCODED WITH XOR SYMMETRIC ENCODING (Key: 0x5A) ---" << std::endl;
    std::cout << "Offset(h)  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    offset = 0; // Reset offset for the second grid
    unsigned char xorKey = 0x5A;

     for (unsigned char rawByte : buffer) {
        if (offset % 16 == 0) {
            std::cout << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << offset << "   ";
        }
        
        // Applying the XOR key
        unsigned char encodedByte = rawByte ^ xorKey;
        
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(encodedByte) << " ";
        offset++;
        if (offset % 16 == 0) std::cout << std::endl;
    }
    if (offset % 16 != 0) std::cout << std::endl;


    // --- XOR DECODED HEX DUMP (SYMMETRIC DECRYPTION) ---
    std::cout << "\n[+] STATUS: DECRYPTED BYTES (XOR Key: 0x5A applied to Encoded Data)" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "Offset(h)  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    offset = 0; // Reset offset for the third grid

     for (unsigned char rawByte : buffer) {
        if (offset % 16 == 0) {
            std::cout << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << offset << "   ";
        }
        
        // 1. Encode the byte (Simulating reading the scrambled data)
        unsigned char encodedByte = rawByte ^ xorKey;
        
        // 2. Decode the byte using the exact same key
        unsigned char decodedByte = encodedByte ^ xorKey;
        
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(decodedByte) << " ";
        offset++;
        if (offset % 16 == 0) std::cout << std::endl;
    }
    if (offset % 16 != 0) std::cout << std::endl;

    return 0;
}