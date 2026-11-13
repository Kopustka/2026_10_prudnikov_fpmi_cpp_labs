

//Перевернуть порядок слов в строке, оставив символы внутри каждого слова на своих местах
// (например, I love you, C++! ⇒ C++ you love, I!).
//Разделители между словами должны быть сохранены в исходном порядке и количестве.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <locale>

std::time_t Now() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

auto FormatTime(time_t time, bool is_utc_format) {
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

    return is_utc_format
        ? std::put_time(std::gmtime(&time), "%x %X")
        : std::put_time(std::localtime(&time), "%x %X");

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
}


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
    std::ifstream fin{ filename };
    std::string line;

    if (!fin.is_open()) {
        throw std::string("Error: could not open file \"" + filename + "\"!!!");
    }

    if (IsEmptyFile(fin)) { // EOF
        throw std::string("Error: file \"" + filename + "\" is empty");
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
    fout << FormatTime(Now(), false) << "|" << " [INFO] " << msg << "\n";
}

void LogError(std::ofstream& fout, const std::string& msg) {
    fout << FormatTime(Now(), false) << "|" << " [ERROR] " << msg << "\n";
}

void ProccesFile(const std::string& filename_input, const std::string& filename_output, std::ofstream& logs_fout) {
    std::ifstream fin{ filename_input };
    std::ofstream fout{ filename_output };



    if (!fin.is_open()) {
        throw std::string("Error: could not open file \"" + filename_input + "\"!!!");
    }

    if (IsEmptyFile(fin)) { // EOF
        throw std::string("Error: file \"" + filename_output + "\" is empty");
    }

    std::string line;

    Log(logs_fout, ("Opening file, and reading \"" + filename_input + "\""));
    while (std::getline(fin, line)) {

        if (line.find_first_not_of(" ") == std::string::npos) {
            Log(logs_fout, ("empty line skipped\n"));
            continue;
        }

        Log(logs_fout, ("The LINE was succesefully read, and text was received"));

        std::vector<int> indexes = {};

        Log(logs_fout, ("Process of rearranginng words"));
        std::vector<std::string> sentence = parseSentence(line, indexes);

        std::string result = reverseWords(sentence, indexes);
        Log(logs_fout, ("Words was rearranged succesefully\n"));

        Log(logs_fout, ("Try to write down the result in \"" + filename_output + "\""));
        fout << result << '/n';

        Log(logs_fout, ("The result was succesefully writen down in \"" + filename_output + "\""));
    }

    Log(logs_fout, ("Closing file"));
    fout.close();
}





int main() {
    const std::string input_file = "input.txt";
    const std::string output_file = "output.txt";
    const std::string logger_file = "logger.txt";

    std::string line;

    std::ofstream logs_fout{ logger_file };


    try {

        if (!logs_fout.is_open()) {
            throw std::string("Error: could not open file \"" + logger_file + "\"!!!");
        }
        ProccesFile(input_file, output_file, logs_fout);

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