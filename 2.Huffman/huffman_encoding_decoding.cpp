// #Huffman Tree steps : 

// 1. Define huffman tree node. 
// 2. Min-heap comparator (so the smallest freq. comes first) 
// 3. DFS to generate codes from the tree. 
// 4. Decode function (walk bits down the tree; output when hitting a leaf. 
// 5. main() - set the input text. 
// 6. count character frequencies
// 7. build a min-heap of nodes (one per character) 
// 8. building the huffman tree ( combine two smallest unit one root remains)
// 9. Generate the code table (char - bitstring)
// 10. (optional) print codes for checking. 
// 11. Encode the text (concatenate codes)
// 12. Decode back to original using the tree. 

//----------------------------------------------------


#include<bits/stdc++.h>
using namespace std; 

// 1. Define huffman tree node. 

struct Node{
    char ch;
    int freq;
    Node *left,*right;
    Node(char c, int f){
        ch = c; 
        freq=f;
        left=right=nullptr;
    }
};

// 2. Min-heap comparator (so the smallest freq. comes first) 

struct Compare {
    bool operator()(Node* l, Node * r){
        return l->freq> r->freq;
    }
};

// 3. DFS to generate codes from the tree. 
// Generate Huffman Codes (recursive)

void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // If leaf node, store the code
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// 4. Decode function (walk bits down the tree; output when hitting a leaf. 
// Decode encoded string using Huffman Tree

string decode(Node* root, string encoded) {
    string decoded = "";
    Node* curr = root;

    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        // If leaf node
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root; // reset for next character
        }
    }
    return decoded;
}


int main(){

// 5. main() - set the input text. 

    string text = "ABCDABCDABBBB";   // Simple text message
    cout << "Original Text: " << text << "\n";

// 6. count character frequencies

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

// 7. build a min-heap of nodes (one per character - one char - one node ex - 2A. Node('A',2)) 

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

// 8. building the huffman tree ( combine two smallest unit one root remains)

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();

// 9. Generate the code table (char - bitstring)

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    
// 10. (optional) print codes for checking. 

    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " -> " << pair.second << "\n";
    }

// 11. Encode the text (concatenate codes)

    string encoded = "";
    for (char c : text) encoded += huffmanCode[c];
    cout << "\nEncoded Message: " << encoded << "\n";

// 12. Decode back to original using the tree. 

    string decoded = decode(root, encoded);
    cout << "\nDecoded Message: " << decoded << "\n";

    return 0;
}