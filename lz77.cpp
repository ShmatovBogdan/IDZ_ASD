#include <iostream>
#include <vector>
#include <string>

struct LZ77 { int offset, length; char next; };

std::vector<LZ77> encodeLZ77(const std::string& text, int window = 5) {
	std::vector<LZ77> result;
	int n = text.size();
	for (int i = 0; i < n; ) {
		int bestOffset = 0, bestLength = 0;
		for (int j = std::max(0, i - window); j < i; j++) {
			int l = 0;
			while (i + l < n && text[j + l] == text[i + l]) l++;
			if (l > bestLength) { bestLength = l; bestOffset = i - j; }
		}
		char nextChar = (i + bestLength < n) ? text[i + bestLength] : '\0';
		result.push_back({ bestOffset, bestLength, nextChar });
		i += bestLength + 1;
	}
	return result;
}

std::string decodeLZ77(const std::vector<LZ77>& encoded) {
	std::string text;
	for (auto& x : encoded) {
		int start = text.size() - x.offset;
		for (int i = 0; i < x.length; i++) text += text[start + i];
		if (x.next != '\0') text += x.next;
	}
	return text;
}

int main() {
	std::string text;
	std::cout << "Enter text for LZ77: ";
	getline(std::cin, text);

	auto encoded = encodeLZ77(text);
	std::cout << "Text encodings (LZ77):\n";
	for (auto& x : encoded)
		std::cout << '(' << x.offset << ',' << x.length << ',' << x.next << ") ";
	std::cout << std::endl;


	std::string decoded = decodeLZ77(encoded);
	std::cout << "Decoding text: " << decoded << std::endl;
	return 0;
}
