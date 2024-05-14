#pragma once

#include <string>

struct vigenere_cipher {

	[[ nodiscard ]]
	static constexpr auto encode(const std::string& original_message, const std::string& key_word, const std::string& alphabet) {
		std::string result; result.reserve(original_message.size());
		auto alphabet_size = alphabet.size();
		auto key = generate_key(original_message, key_word);

		for (int i = 0; i < original_message.size(); ++i) {
			auto encoded_letter = (original_message[i] + key[i]) % alphabet_size;
			result.push_back(encoded_letter + 'A');
		}

		return result;
	}

	[[ nodiscard ]]
	static constexpr auto decode(const std::string& encoded_message, const std::string& key_word, const std::string& alphabet) {
		std::string result; result.reserve(encoded_message.size());
		auto alphabet_size = alphabet.size();
		auto key = generate_key(encoded_message, key_word);

		for (int i = 0; i < encoded_message.size(); ++i) {
			auto decoded_letter = (encoded_message[i] - key[i] + alphabet_size) % alphabet_size;
			result.push_back(decoded_letter + 'A');
		}

		return result;
	}

private:
	static constexpr auto generate_key(const std::string& original_message, const std::string& key_word) -> std::string {
		std::string result;
		result.reserve(original_message.size());

		for (int i = 0; i < original_message.size(); ++i)
			result.push_back(key_word[i % key_word.size()]);

		return result;
	}
};
