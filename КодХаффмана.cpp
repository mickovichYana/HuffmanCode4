#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

// ������� ��� 㧫� ��ॢ� ���䬠��
struct HuffmanNode {
    char ch; // ������
    int freq; // ����� ᨬ����
    vector<HuffmanNode*> children; // ����� ��⮬��� (�� 4)

    HuffmanNode(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        children = vector<HuffmanNode*>(4, nullptr); // ���樠������� 4 ��⮬��
    }
};


struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// �㭪�� ��� ��室� ��ॢ� ���䬠�� � ᮧ����� �����
void encode(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // �᫨ 㧥� - ����, � �������� ��� ��� � map
    if (root->children[0] == nullptr && root->children[1] == nullptr &&
        root->children[2] == nullptr && root->children[3] == nullptr) {
        huffmanCode[root->ch] = str;
    }

    // �����ᨢ�� ��宦� ��� ��⮬���
    for (int i = 0; i < 4; ++i) {
        if (root->children[i] != nullptr) {
            encode(root->children[i], str + to_string(i), huffmanCode);
        }
    }
}

// �᭮���� �㭪�� ��� ����஥��� ��ॢ� ���䬠�� � ����஢����
void buildHuffmanTree(string text, map<char, int>& freq, map<char, string>& huffmanCode) {
    
    for (char ch : text) {
        freq[ch]++;
    }
    // ������ �ਮ����� ��।� ��� �࠭���� 㧫�� ��ॢ�
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;

    // ������ 㧫� ��� ������� ᨬ���� � �������� �� � ��।�
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // ���� ��ॢ� ���䬠��
    while (pq.size() > 1) {
        // ������ ���� 㧥� � 4 ��⮬����
        HuffmanNode* node = new HuffmanNode('\0', 0);

        // ���� 4 㧫� � �������襩 ���⮩
        for (int i = 0; i < 4; ++i) {
            if (!pq.empty()) {
                node->children[i] = pq.top();
                node->freq += pq.top()->freq;
                pq.pop();
            }
        }

        // �������� ���� 㧥� � ��।�
        pq.push(node);
    }

    // ������ ��७� ��ॢ�
    HuffmanNode* root = pq.top();

    // ���� ���� ���䬠��
    encode(root, "", huffmanCode);
}

int main() {
    string text = "�������� ���� �������� ������ ��������� "
        "����������� �������� ������ ����� "
        "���������� ���� ����� ����������� �� ��������� � ���������� �� ���������� �� �������� � ����� ��� ���� �������� ���� ����� ������� ��������� ���� ��������� �� ����� "
        "����� � ��� ������ ����� �� �������� ���������� ��� ���� � ����� � ������� ������ �������� � ������� ��������� ������� ���������� ������� ���� �������� ����� � ������ " 
        "�� ���������� � ������� ���� �� ������� ����� ������������ �� �������� ��� �� ��������� ������ ������� ����� ������� ��� ����� ������� � ���������� �������� �� ���������� "
        "������� � ����� ����� � ������ ������";

    map<char, int> freq;
    map<char, string> huffmanCode;
    buildHuffmanTree(text, freq, huffmanCode);
    cout << "���� ���䬠��:\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}