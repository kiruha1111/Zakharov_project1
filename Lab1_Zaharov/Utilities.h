#pragma once
#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <unordered_set>
#include <unordered_map>


template <typename Stream>
class redirect_stream_wrapper
{
    Stream& stream;
    std::streambuf* const old_buf;
public:
    redirect_stream_wrapper(Stream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_stream_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(Stream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};


inline std::string input_string()
{
    std::string str;
    std::getline(std::cin, str);
    std::cerr << str << std::endl;
    return str;
}


inline bool checking(std::string number) {
    for (int i = 0; i < number.length(); i++) {
        if (isdigit(number[i]) || number[i] == '-') continue;
        else return false;
    }
    if (number.length() == 0 || number == "-") return false;
    return true;
}


template <typename N>
N GetCorrectNumber(N min, N max) {
    std::string input;
    while (std::getline(std::cin, input).fail() || checking(input) == false || std::stoi(input) < min || std::stoi(input) > max) {
        std::cout << std::endl << "Error! Try again ";
    }
    //std::cerr << std::stoi(input) << std::endl;
    return std::stoi(input);
}


template <typename T>
std::unordered_set<int> GetKeys(const std::unordered_map<int, T>& container)
{
    std::unordered_set<int> keys;
    for (auto& [id, element] : container)
        keys.insert(id);
    return keys;
}


inline int SwitchNumber(std::vector<int>& conteiner)
{
    for (int i = 0; i < conteiner.size(); i++)
    {
        std::cout << i + 1 << ". " << conteiner[i] << std::endl;
    }
    int answer = GetCorrectNumber(1, (int)conteiner.size());
    return conteiner[answer - 1];
}