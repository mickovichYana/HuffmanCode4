#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Структура для узла дерева Хаффмана
struct HuffmanNode {
    char ch; // Символ
    int freq; // Частота символа
    vector<HuffmanNode*> children; // Вектор потомков (до 4)

    HuffmanNode(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        children = vector<HuffmanNode*>(4, nullptr); // Инициализирую 4 потомка
    }
};


struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// Функция для обхода дерева Хаффмана и создания кодов
void encode(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // Если узел - лист, то добавляю его код в map
    if (root->children[0] == nullptr && root->children[1] == nullptr &&
        root->children[2] == nullptr && root->children[3] == nullptr) {
        huffmanCode[root->ch] = str;
    }

    // Рекурсивно обхожу всех потомков
    for (int i = 0; i < 4; ++i) {
        if (root->children[i] != nullptr) {
            encode(root->children[i], str + to_string(i), huffmanCode);
        }
    }
}

// Основная функция для построения дерева Хаффмана и кодирования
void buildHuffmanTree(string text, map<char, int>& freq, map<char, string>& huffmanCode) {
    
    for (char ch : text) {
        freq[ch]++;
    }
    // Создаю приоритетную очередь для хранения узлов дерева
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;

    // Создаю узлы для каждого символа и добавляю их в очередь
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Строю дерево Хаффмана
    while (pq.size() > 1) {
        // Создаю новый узел с 4 потомками
        HuffmanNode* node = new HuffmanNode('\0', 0);

        // Беру 4 узла с наименьшей частотой
        for (int i = 0; i < 4; ++i) {
            if (!pq.empty()) {
                node->children[i] = pq.top();
                node->freq += pq.top()->freq;
                pq.pop();
            }
        }

        // Добавляю новый узел в очередь
        pq.push(node);
    }

    // Получаю корень дерева
    HuffmanNode* root = pq.top();

    // Строю коды Хаффмана
    encode(root, "", huffmanCode);
}

int main() {
    string text = "ГОСТИНАЯ АННЫ ПАВЛОВНЫ НАЧАЛА ПОНЕМНОГУ "
        "НАПОЛНЯТЬСЯ ПРИЕХАЛА ВЫСШАЯ ЗНАТЬ "
        "ПЕТЕРБУРГА ЛЮДИ САМЫЕ РАЗНОРОДНЫЕ ПО ВОЗРАСТАМ И ХАРАКТЕРАМ НО ОДИНАКОВЫЕ ПО ОБЩЕСТВУ В КАКОМ ВСЕ ЖИЛИ ПРИЕХАЛА ДОЧЬ КНЯЗЯ ВАСИЛИЯ КРАСАВИЦА ЭЛЕН ЗАЕХАВШАЯ ЗА ОТЦОМ "
        "ЧТОБЫ С НИМ ВМЕСТЕ ЕХАТЬ НА ПРАЗДНИК ПОСЛАННИКА ОНА БЫЛА В ШИФРЕ И БАЛЬНОМ ПЛАТЬЕ ПРИЕХАЛА И МОЛОДАЯ МАЛЕНЬКАЯ КНЯГИНЯ БОЛКОНСКАЯ ПРОШЛУЮ ЗИМУ ВЫШЕДШАЯ ЗАМУЖ И ТЕПЕРЬ " 
        "НЕ ВЫЕЗЖАВШАЯ В БОЛЬШОЙ СВЕТ ПО ПРИЧИНЕ СВОЕЙ БЕРЕМЕННОСТИ НО ЕЗДИВШАЯ ЕЩЕ НА НЕБОЛЬШИЕ ВЕЧЕРА ПРИЕХАЛ КНЯЗЬ ИППОЛИТ СЫН КНЯЗЯ ВАСИЛИЯ С МОРТЕМАРОМ КОТОРОГО ОН ПРЕДСТАВИЛ "
        "ПРИЕХАЛ И АББАТ МОРИО И МНОГИЕ ДРУГИЕ";

    map<char, int> freq;
    map<char, string> huffmanCode;
    buildHuffmanTree(text, freq, huffmanCode);
    cout << "Коды Хаффмана:\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}