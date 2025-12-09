#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

struct Node {
    char symbol{};
    double freq{};
    std::string code{};
};

bool cmp(const Node& a, const Node& b) { return a.freq > b.freq; }

/* Функція розділення списку символів */
int divide(std::vector<Node>& a, int l, int r) {
    double leftSum = 0, rightSum = 0;
    for (int i = l; i <= r; i++) rightSum += a[i].freq;

    for (int i = l; i <= r; i++) {
        leftSum += a[i].freq;
        rightSum -= a[i].freq;
        if (leftSum >= rightSum) return i;
    }
    return l;
}

/* Рекурсивне призначення кодів */
void shannonFano(std::vector<Node>& a, int l, int r) {
    if (l >= r) return;

    int mid = divide(a, l, r);

    for (int i = l; i <= mid; i++) a[i].code += "0";
    for (int i = mid + 1; i <= r; i++) a[i].code += "1";

    shannonFano(a, l, mid);
    shannonFano(a, mid + 1, r);
}

/* Побудова таблиці кодів */
std::map<char, std::string> buildCodes(const std::string& text) {
    std::map<char, int> freq;
    for (char c : text) freq[c]++;

    std::vector<Node> nodes;
    for (auto& p : freq)
        nodes.push_back({ p.first, (double)p.second, "" });

    sort(nodes.begin(), nodes.end(), cmp);

    shannonFano(nodes, 0, nodes.size() - 1);

    std::map<char, std::string> codes;
    for (auto& n : nodes)
        codes[n.symbol] = n.code;

    return codes;
}

/* Кодування */
std::string encode(const std::string& text, std::map<char, std::string>& codes) {
    std::string res = "";
    for (char c : text)
        res += codes[c];
    return res;
}

/* Декодування */
std::string decode(const std::string& bits, std::map<char, std::string>& codes) {
    std::map<std::string, char> inv;
    for (auto& p : codes) inv[p.second] = p.first;

    std::string res = "", cur = "";
    for (char b : bits) {
        cur += b;
        if (inv.count(cur)) {
            res += inv[cur];
            cur = "";
        }
    }
    return res;
}

int main() {
    std::string text;
    std::cout << "=== Shannon-Fano algorithm ===\n\n";
    std::cout << "Enter text: ";

    getline(std::cin, text);

    auto codes = buildCodes(text);

    std::cout << "\nCodes:\n";
    for (auto& p : codes)
        std::cout << p.first << ": " << p.second << "\n";

    std::string encoded = encode(text, codes);
    std::cout << "\nEncoded: " << encoded << "\n";

    std::string decoded = decode(encoded, codes);
    std::cout << "Decoded: " << decoded << "\n";

    return 0;
}
