#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

// โเใชโใเ  คซ๏ ใงซ  คฅเฅข   ไไฌ ญ 
struct HuffmanNode {
    char ch; // จฌขฎซ
    int freq; //  แโฎโ  แจฌขฎซ 
    vector<HuffmanNode*> children; // ฅชโฎเ ฏฎโฎฌชฎข (คฎ 4)

    HuffmanNode(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        children = vector<HuffmanNode*>(4, nullptr); // ญจๆจ ซจงจเใ๎ 4 ฏฎโฎฌช 
    }
};


struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// ใญชๆจ๏ คซ๏ ฎกๅฎค  คฅเฅข   ไไฌ ญ  จ แฎงค ญจ๏ ชฎคฎข
void encode(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // แซจ ใงฅซ - ซจแโ, โฎ คฎก ขซ๏๎ ฅฃฎ ชฎค ข map
    if (root->children[0] == nullptr && root->children[1] == nullptr &&
        root->children[2] == nullptr && root->children[3] == nullptr) {
        huffmanCode[root->ch] = str;
    }

    // ฅชใเแจขญฎ ฎกๅฎฆใ ขแฅๅ ฏฎโฎฌชฎข
    for (int i = 0; i < 4; ++i) {
        if (root->children[i] != nullptr) {
            encode(root->children[i], str + to_string(i), huffmanCode);
        }
    }
}

// แญฎขญ ๏ ไใญชๆจ๏ คซ๏ ฏฎแโเฎฅญจ๏ คฅเฅข   ไไฌ ญ  จ ชฎคจเฎข ญจ๏
void buildHuffmanTree(string text, map<char, int>& freq, map<char, string>& huffmanCode) {
    
    for (char ch : text) {
        freq[ch]++;
    }
    // ฎงค ๎ ฏเจฎเจโฅโญใ๎ ฎ็ฅเฅค์ คซ๏ ๅเ ญฅญจ๏ ใงซฎข คฅเฅข 
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;

    // ฎงค ๎ ใงซ๋ คซ๏ ช ฆคฎฃฎ แจฌขฎซ  จ คฎก ขซ๏๎ จๅ ข ฎ็ฅเฅค์
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // โเฎ๎ คฅเฅขฎ  ไไฌ ญ 
    while (pq.size() > 1) {
        // ฎงค ๎ ญฎข๋ฉ ใงฅซ แ 4 ฏฎโฎฌช ฌจ
        HuffmanNode* node = new HuffmanNode('\0', 0);

        // ฅเใ 4 ใงซ  แ ญ จฌฅญ์่ฅฉ ็ แโฎโฎฉ
        for (int i = 0; i < 4; ++i) {
            if (!pq.empty()) {
                node->children[i] = pq.top();
                node->freq += pq.top()->freq;
                pq.pop();
            }
        }

        // ฎก ขซ๏๎ ญฎข๋ฉ ใงฅซ ข ฎ็ฅเฅค์
        pq.push(node);
    }

    // ฎซใ็ ๎ ชฎเฅญ์ คฅเฅข 
    HuffmanNode* root = pq.top();

    // โเฎ๎ ชฎค๋  ไไฌ ญ 
    encode(root, "", huffmanCode);
}

int main() {
    string text = "     "
        "    "
        "                         "
        "                           " 
        "                          "
        "      ";

    map<char, int> freq;
    map<char, string> huffmanCode;
    buildHuffmanTree(text, freq, huffmanCode);
    cout << "ฎค๋  ไไฌ ญ :\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}