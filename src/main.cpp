#include <iostream>
#include <algorithm>
#include <filesystem>
#include <locale>
#include <fstream>
#include <regex>
#include <functional>

#include "vigenere_cipher.hpp"

template<typename ReturnType>
auto validate_input(const std::string &message, const std::regex &pattern, const std::function<ReturnType(const std::string &)> &converter) {
	std::string input;
	
	do {
		std::cout << message;
		std::getline(std::cin, input);
	} while (!std::regex_match(input, pattern));

	return converter(input);
}

int main() {
	const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	const std::regex numbers_pattern("^[0-9]$|^[1-3][0-9]$|^48$");
	const std::regex letters_pattern("^[a-z]+$", std::regex::icase);

	const auto num_converter = [](const std::string& s) { return std::stoi(s); };
	const auto str_converter = [](const std::string& s) {return s; };

	auto vigenere_key = validate_input<std::string>("\ninput key word for a Vigenere cipher (letters only, no space):\t", letters_pattern, str_converter);

	namespace fs = std::filesystem;
	fs::path file_path = "example.txt";

	std::ifstream input_file(file_path);

	if (!input_file.is_open()) return -1;

	std::string line;
	while (std::getline(input_file, line)) {

		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

		if (line.empty()) continue;

		std::cout << "\n\nmessage: " << line << '\n';

		if (!std::regex_match(line, letters_pattern)) {
			std::cout << "wrong format!\n";
			continue;
		}

		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		std::transform(vigenere_key.begin(), vigenere_key.end(), vigenere_key.begin(), ::toupper);

		auto encoded = vigenere_cipher::encode(line, vigenere_key, alphabet);
		auto decoded = vigenere_cipher::decode(encoded, vigenere_key, alphabet);

		std::cout << "\nVigenere Cipher: " << encoded;
		std::cout << "\nDecoded:\t" << decoded;
	}

	input_file.close();

	return 0;
}
