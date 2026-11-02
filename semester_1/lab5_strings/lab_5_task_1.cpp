

//Перевернуть порядок слов в строке, оставив символы внутри каждого слова на своих местах
// (например, I love you, C++! ⇒ C++ you love, I!).
//Разделители между словами должны быть сохранены в исходном порядке и количестве.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
void reverseWords(std::vector<std::string>& sentence, const std::vector<int>& indexes) {
    std::vector<std::string> temp_words;
    for (int idx : indexes) {
        temp_words.push_back(sentence[idx]);
    }
    std::reverse(temp_words.begin(), temp_words.end());

    for (size_t j = 0; j < indexes.size(); ++j) {
        sentence[indexes[j]] = temp_words[j];
    }
}

// 3. Функция вывода результата
void printResult(const std::vector<std::string>& sentence) {
    for (const auto& item : sentence) {
        std::cout << item;
    }
    std::cout << std::endl;
}

int main() {
    std::string s = "I love you, C++!";
    std::vector<int> indexes = {};

    std::vector<std::string> sentence = parseSentence(s, indexes);
    reverseWords(sentence, indexes);
    printResult(sentence);

    return 0;
}