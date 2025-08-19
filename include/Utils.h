#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

#define LOG(x) std::cout << x << std::endl;

inline bool ReadFileToMemory(const std::string& filePath, std::vector<BYTE>& outBuffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return false;

    file.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    outBuffer.resize(size);
    file.read(reinterpret_cast<char*>(outBuffer.data()), size);
    return true;
}
