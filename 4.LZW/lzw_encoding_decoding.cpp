// Idea of LZW
// Encoding replaces repeated patterns with dictionary codes.
// Decoding does the reverse: it uses the same logic to rebuild the original string while reconstructing the dictionary on the fly.

// #LZW Encoding & Decoding steps:

// 1. Initialize the dictionary with all single-character strings (ASCII 0-255).
// 2. Set an empty string w (current sequence).
// 3. Loop over each character c in the input text:
//      a) Concatenate w+c.
//      b) If w+c exists in the dictionary, set w = w+c (extend current sequence).
//      c) Else:
//           i) Output the code for w.
//           ii) Add w+c to the dictionary with a new code.
//           iii) Set w = c (start new sequence).
// 4. After loop, if w is non-empty, output its code.
// 5. Store the encoded output as a sequence of integers (codes).

// 6. For decoding, initialize the dictionary again with single-character strings (0-255).
// 7. Read the first code, set w = dictionary[code], output w.
// 8. Loop over remaining codes:
//      a) If code exists in dictionary, set entry = dictionary[code].
//      b) Else (special case), set entry = w + first character of w.
//      c) Output entry.
//      d) Add w + first character of entry to dictionary.
//      e) Set w = entry (move to next sequence).
// 9. Repeat until all codes are decoded to reconstruct the original text.

#include <bits/stdc++.h>
using namespace std;

// LZW Encoding function

// LZW Encoding function
vector<int> LZW_Encode(const string &text)
{
    // Initialize dictionary with all single characters
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++)
    {
        dictionary[string(1, i)] = i;
    }

    // for (auto x : dictionary)
    // {
    //     cout << x.first << " " << x.second << endl;
    // }

    string w = "";
    vector<int> encoded;
    int dictSize = 256;

    for (char c : text)
    {
        string wc = w + c;
        if (dictionary.count(wc))
        {
            w = wc;
        }
        else
        {
            // Output code for w
            encoded.push_back(dictionary[w]);
            // Add wc to dictionary
            dictionary[wc] = dictSize++;
            w = string(1, c);
        }
    }

    if (!w.empty())
        encoded.push_back(dictionary[w]);
    return encoded;
}


// LZW Decoding function

// Look up the code in dictionary.
// Write its string to output.
// Add new combo (previous word + first letter of current word) to dictionary.
// Repeat.

string LZW_Decode(const vector<int> &encoded) {
    unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    int dictSize = 256;
    string w(1, encoded[0]);  // first character
    string decoded = w;

    for (size_t i = 1; i < encoded.size(); i++) {
        int k = encoded[i];
        string entry;

        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictSize) {
            // Special case: handle w+firstChar
            entry = w + w[0];
        } else {
            throw runtime_error("Bad compressed k");
        }

        decoded += entry;

        // Add new sequence to dictionary
        dictionary[dictSize++] = w + entry[0];
        // previous string + first character of current entry.

        w = entry;
    }

    return decoded;
}


int main()
{
    string text = "ABABABA";
    cout << "Orginal Text : " << text << "\n";

    // Encoding

    vector<int> encoded = LZW_Encode(text);
    cout << "Encoded Output : ";
    for (int code : encoded)
        cout << code << " ";
    cout << endl;

    // Decoding

    string decoded = LZW_Decode(encoded);
    cout << "Decoded Text : " << decoded << "\n";

    return 0;
}