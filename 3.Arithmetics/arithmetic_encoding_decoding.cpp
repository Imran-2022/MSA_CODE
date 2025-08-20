// #Arithmetic Coding Steps :
//
// 1. Define node struct: prob, range_from, range_to.
// 2. Input characters with probabilities.
// 3. Build cumulative ranges [from, to) for each symbol.
// 4. Encoding:
//    - Start with [0,1).
//    - For each symbol: update interval to that symbol’s subrange.
//    - Final code = any value inside last interval.
// 5. Decoding:
//    - Start with code in [0,1).
//    - Find symbol whose range contains code.
//    - Output symbol.
//    - Rescale code into that subrange.
//    - Repeat until all symbols are decoded.
// 6. main():
//    - Input probability table.
//    - Show symbol table.
//    - Input text.
//    - Encode → produce code word.
//    - Decode → reconstruct original text.
//    - Print results.



#include <bits/stdc++.h>
using namespace std;

// 1. Define node struct to store probability and cumulative range
struct Node {
    double prob;        // probability of character
    double range_from;  // start of cumulative range
    double range_to;    // end of cumulative range
};

// 2. Arithmetic Encoding Function
double encode(const string &s, const unordered_map<char, Node> &dict) {
    double low = 0.0, high = 1.0, range = 1.0;

    cout << "\nEncoding Steps:\n";
    cout << "Symbol\tLow\tHigh\tRange\n";

    for (char c : s) {
        // Update interval for current character
        double new_high = low + range * dict.at(c).range_to;
        double new_low  = low + range * dict.at(c).range_from;
        range = new_high - new_low;
        low = new_low;
        high = new_high;

        cout << c << "\t" << low << "\t" << high << "\t" << range << "\n";
    }

    // 3. Any number inside final interval is a valid code
    return (low + high) / 2.0; // pick midpoint
}

// 4. Arithmetic Decoding Function
string decode(double code, int len, const vector<pair<char, Node>> &dict) {
    string result = "";

    cout << "\nDecoding Steps:\n";
    cout << "Code\tSymbol\tRange_from\tRange_to\n";

    for (int i = 0; i < len; i++) {
        // Find which character contains current code
        for (auto &p : dict) {
            char c = p.first;
            Node n = p.second;

            if (code >= n.range_from && code < n.range_to) {
                result.push_back(c);
                cout << code << "\t" << c << "\t" << n.range_from << "\t\t" << n.range_to << "\n";

                // 5. Rescale code into subrange for next character
                code = (code - n.range_from) / (n.range_to - n.range_from);
                break;
            }
        }
    }

    return result;
}

int main() {
    // 6. Input number of characters
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    unordered_map<char, Node> dict;           // map for fast lookup during encoding
    vector<pair<char, Node>> dict_order;      // preserve input order for decoding

    double cumulative = 0.0;                  // cumulative sum of probabilities

    // 7. Input characters and their probabilities
    cout << "Enter character and its probability (e.g., A 0.3):\n";
    for (int i = 0; i < n; i++) {
        char c;
        double p;
        cin >> c >> p;

        Node node;
        node.prob = p;
        node.range_from = cumulative;
        node.range_to = cumulative + p;
        cumulative = node.range_to;

        dict[c] = node;
        dict_order.push_back({c, node});
    }

    // 8. Print symbol table
    cout << "\nSymbol Table:\n";
    cout << "Symbol\tProb\tRange_from\tRange_to\n";
    cout << "---------------------------------------\n";
    for (auto &p : dict_order) {
        cout << p.first << "\t" << p.second.prob << "\t" << p.second.range_from
             << "\t\t" << p.second.range_to << "\n";
    }

    // 9. Input string to encode
    string text;
    cout << "\nEnter text to encode: ";
    cin >> text;

    // 10. Encode the string
    double code = encode(text, dict);
    cout << "\nFinal Code for \"" << text << "\" is: " << code << "\n";

    // 11. Decode the code back to string
    string decoded = decode(code, text.size(), dict_order);
    cout << "\nDecoded Text: " << decoded << "\n";

    return 0;
}



// Enter number of characters: 3
// A 0.3
// B 0.5
// C 0.2
// Enter text to encode: ABCA