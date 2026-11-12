

//Перевернуть порядок слов в строке, оставив символы внутри каждого слова на своих местах
// (например, I love you, C++! ⇒ C++ you love, I!).
//Разделители между словами должны быть сохранены в исходном порядке и количестве.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

const std::string SIGNS = ",.!?;:";

// 1. Функция парсинга строки 
std::vector<std::string> parseSentence(const std::string& s, std::vector<int>& indexes) {
    std::vector<std::string> sentence = {};
    size_t start = 0;
    int i = 0;

    while (start < s.length()) {
        // Ищем и сохраняем пробелы между словами
        size_t space_end = s.find_first_not_of(" ", start);
        if (space_end == std::string::npos) {
            std::string spaces = s.substr(start);
            if (!spaces.empty()) {
                sentence.push_back(spaces);
            }
            break;
        }

        if (space_end > start) {
            std::string spaces = s.substr(start, space_end - start);
            sentence.push_back(spaces);
            i++;
        }

        // Ищем слово
        size_t word_end = s.find(" ", space_end);
        if (word_end == std::string::npos) {
            word_end = s.length();
        }

        std::string sub = s.substr(space_end, word_end - space_end);
        std::string sign = "";

        // Отделяем знаки препинания
        while (!sub.empty() && SIGNS.find(sub.back()) != std::string::npos) {
            sign += sub.back();
            sub.pop_back();
        }
        std::reverse(sign.begin(), sign.end());

        // Добавляем слово и запоминаем его индекс
        sentence.push_back(sub);
        indexes.push_back(i);
        i++;

        // Добавляем знаки препинания отдельным элементом, если они были
        if (!sign.empty()) {
            sentence.push_back(sign);
            i++;
        }

        start = word_end;
    }
    return sentence;
}

// 2. Функция переворота слов по индексам
std::string reverseWords(std::vector<std::string>& sentence, const std::vector<int>& indexes) {
    std::vector<std::string> temp_words;
    for (int idx : indexes) {
        temp_words.push_back(sentence[idx]);
    }
    std::reverse(temp_words.begin(), temp_words.end());

    for (size_t j = 0; j < indexes.size(); ++j) {
        sentence[indexes[j]] = temp_words[j];
    }

    std::string line;
    for (const std::string item : sentence) {
        line += item;
    }

    return line;
}

bool IsEmptyFile(std::ifstream& fin) {
    // return file.peek() == EOF;
    return fin.peek() == std::ifstream::traits_type::eof();
}

std::string ReadLineFile(const std::string& filename) {
    std::ifstream fin{filename};
    std::string line;
    
    if (!fin.is_open()) {
        throw std::string("Error: could not open file \"" + filename + "\"!!!");
    }

    if (IsEmptyFile(fin)) { // EOF
        throw std::string ("Error: file \"" + filename + "\" is empty");
    }

    std::getline(fin, line);
    std::cout << "String: " << line << std::endl;

    return line;    

}

void WriteLineFile(const std::string& filename, const std::string& line) {
    std::ofstream fout{ filename };
    
    if (!fout.is_open()) {
       throw std::string("Error: could not open file \"" + filename + "\"!!!");
    }

    fout << line;

    fout.close();   
}



void Log(std::ofstream& fout, const std::string& msg) {
    fout << " [INFO] " << msg << "\n";
}

void LogError(std::ofstream& fout, const std::string& msg) {
    fout << " [ERROR] " << msg << "\n";
}


int main() {
    const std::string input_file = "input.txt";
    const std::string output_file = "output.txt";
    const std::string logger_file = "logger.txt";
    
    std::string line;
    std::vector<int> indexes = {};

    std::ofstream logs_fout{ logger_file };


    try {

        if (!logs_fout.is_open()) {
            throw std::string("Error: could not open file \"" + logger_file +"\"!!!");
        }

        Log(logs_fout, ("Opening file, and reading \"" + input_file + "\"\n"));
        line = ReadLineFile(input_file);
        Log(logs_fout, ("The file was succesefully read, and text was received\n"));
        Log(logs_fout, ("Process of rearranginng words"));
        std::vector<std::string> sentence = parseSentence(line, indexes);
        Log(logs_fout, ("Words was rearranged succesefully\n"));
        line = reverseWords(sentence, indexes);
        Log(logs_fout, ("Try to write down the result in \"" + output_file + "\"\n"));
        WriteLineFile(output_file, line);
        std::cout << "Result has been written to " << std::quoted(output_file);
        Log(logs_fout, ("The result was succesefully writen down in \"" + output_file + "\"\n"));
    }
    catch (const std::string& msg) {
        LogError(logs_fout, msg);
        std::cout << msg << '\n';
    }
    //catch (...) {
    //    std::cout << "Unknown error";
    //}

    logs_fout.close();


    return 0;
}   