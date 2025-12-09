#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Symbol { char ch; double low, high; };

int main() {
	std::string text;
	std::cout << "Enter text for arithmetic coding: ";
	getline(std::cin, text);


	std::map<char, int> freq;
	for (char c : text) freq[c]++;

	std::map<char, double> low, high;
	double total = text.size(), sum = 0;
	for (auto& p : freq) {
		low[p.first] = sum / total;
		sum += p.second;
		high[p.first] = sum / total;
	}

	double lowRange = 0.0, highRange = 1.0;
	for (char c : text) {
		double range = highRange - lowRange;
		highRange = lowRange + range * high[c];
		lowRange = lowRange + range * low[c];
	}

	std::cout << "Coded number: " << (lowRange + highRange) / 2 << std::endl;
	return 0;
}
