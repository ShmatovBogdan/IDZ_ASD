#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

struct Node {
	char ch;
	int freq;
	Node* left, * right;
	Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct compare { bool operator()(Node* a, Node* b) { return a->freq > b->freq; } };

void buildCodes(Node* root, std::string s, std::map<char, std::string>& codes) {
	if (!root) return;
	if (!root->left && !root->right) codes[root->ch] = s;
	buildCodes(root->left, s + "0", codes);
	buildCodes(root->right, s + "1", codes);
}

int main() {
	std::string text;
	std::cout << "Enter text for Huffman code: ";
	getline(std::cin, text);

	std::map<char, int> freq;
	for (char c : text) freq[c]++;

	std::priority_queue<Node*, std::vector<Node*>, compare> pq;
	for (auto& p : freq) pq.push(new Node(p.first, p.second));

	while (pq.size() > 1) {
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top(); pq.pop();
		Node* parent = new Node('\0', left->freq + right->freq);
		parent->left = left; parent->right = right;
		pq.push(parent);
	}

	Node* root = pq.top();
	std::map<char, std::string> codes;
	buildCodes(root, "", codes);

	std::cout << "Cody Huffman: \n";
	for (auto& p : codes) std::cout << p.first << ": " << p.second << std::endl;

	std::string encoded;
	for (char c : text) encoded += codes[c];
	std::cout << "Text encodings: " << encoded << std::endl;
	return 0;
}
