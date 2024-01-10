#include <iostream>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;
FILE *f;

struct Forest{
    int weight, root;
};

struct Tree{
    int left, right, parent, symbol;
    Tree() {
        symbol = -1;
    }
};
Forest forest[256];
Tree tree[530];
map <unsigned char, string>  codes;

void getmin(Forest used[], int sze, int &p1, int &p2) {
    p1 = 0, p2 = 0;
    for (int i = 0; i < sze + 1; i++) {
        if (used[p1].weight > used[i].weight) {
            p1 = i;
        }
    }
    if (p2 == p1){
        p2 = 1;
    }
    for (int i = 0; i < sze + 1; i++) {
        if (used[p2].weight > used[i].weight && i != p1) {
            p2 = i;
        }
    }
}
void encode(int pos, string str, vector <pair<int, unsigned char> > &alphabet) {
    if (tree[pos].left == -1 && tree[pos].right == -1) {
        unsigned char letter = alphabet[pos].second;
        codes[letter] = str;
        tree[pos].symbol = letter;
        //cout << tree[pos].left << ' ' << tree[pos].right << ' ' << tree[pos].parent << ' ' << tree[pos].symbol << endl;
        //cout <<letter <<' '<< codes[letter] << endl;
        return;
    }
    encode(tree[pos].left, str + "0", alphabet);
    encode(tree[pos].right, str + "1", alphabet);
}

int32_t main(int argc, char *argv[]) {
    if (!strcmp("encode", argv[1])) {
        f = fopen(argv[2], "rb");
        freopen(argv[3], "w", stdout);
        int freq[256];
        memset (freq, 0, sizeof freq);
        unsigned char ch;
        while (fscanf(f, "%c", &ch) != -1) {
            freq[ch]++;
            //cout << 2 << ' ';
        }
        /*
        //freq
        for (int i = 0; i < 256; i++) {
            cout << freq[i] << ' ';
        }
        */
        fclose(f);

        int size_forest = 0, size_tree = 0;
        for (int i = 0; i < 256; i++) {
            if (freq[i] > 0){
                forest[size_forest].weight = freq[i];
                forest[size_forest].root = size_forest;
                tree[forest[size_forest].root].right = -1;
                tree[forest[size_forest].root].left = -1;
                tree[forest[size_forest].root].parent = -1;
                size_forest++;
            }
        }
        /*
        //FOREST
        for (int i = 0; i < size_forest; i++) {
           cout << forest[i].weight << ' ' << forest[i].root << endl;
        }
        */
        int p1, p2;
        size_forest--;
        size_tree = size_forest;
        while (size_forest > 0) {
            getmin(forest, size_forest, p1, p2);
            //cout << p1 << ' ' << p2 << endl;
            size_tree++;
            tree[size_tree].left = forest[p1].root;
            tree[size_tree].right = forest[p2].root;
            tree[size_tree].parent = -1;
            tree[forest[p1].root].parent = size_tree;
            tree[forest[p2].root].parent = size_tree;
            forest[p1].weight = forest[p1].weight + forest[p2].weight;
            forest[p1].root = size_tree;
            forest[p2] = forest[size_forest];
            size_forest--;
            /*
            cout <<"POSITIONS: "<< p1 << ' ' << p2 << " SIZE FORREST: " << size_forest<< endl;
            cout <<"NEW VENKA " tree[size_tree].left << ' ' << tree[size_tree].right << ' ' << tree[size_tree].parent << endl << endl;
            cout << forest[p1].weight << ' ' << forest[p2].weight << endl;
            for (int i = 0; i <= size_tree; i++) {
            cout << tree[i].left << ' ' << tree[i].right << ' ' << tree[i].parent << endl;
            }
            cout << endl;

            cout << "NEW FORREST: " << endl;
            for (int i = 0; i <= size_forest; i++) {
            cout << forest[i].weight << ' ' << forest[i].root << endl;
            }
            cout << endl;
            */
        }
        size_tree++;
        tree[size_tree].left = forest[0].root;
        tree[size_tree].right = forest[0].root;
        tree[size_tree].parent = -1;
        cout << size_tree << endl;

        vector <pair <int, unsigned char> > alphabet;
        for(int i = 0; i < 257; i++) {
            if (freq[i] > 0) {
                pair<int, unsigned char> c;
                c.first = freq[i];
                c.second = i;
                alphabet.push_back(c);
            }
        }

        /*
        //ALPHABET
        for (int i = 0; i < alphabet.size(); i++) {
           cout << alphabet[i].first << ' ' << alphabet[i].second<<endl;
        }
        */

        string s;
        encode(size_tree - 1, s, alphabet);
        for (int i = 0; i < size_tree; i++) {
            cout << tree[i].left << ' ' << tree[i].right << ' ' << tree[i].parent << ' ' << tree[i].symbol << endl;
        }

        /*
        cout << "CODES:" << endl;
        for (auto it = codes.begin(); it != codes.end()--; it++) {
            cout << it -> first << ' ' << it -> second << endl;
        }
         */

        f = fopen(argv[2], "rb");
        unsigned char byte = 0;
        int k = 0;
        cout << endl;
        int d;
        while (fscanf(f, "%c", &ch) != -1) {
            //cout << ch;
            for (int i = 0; i < codes[ch].size(); i++) {
                byte = byte << 1;
                byte += codes[ch][i] - '0';
                //cout << codes[ch][i] - '0';
                k += 1;
                if (k == 8) {
                    cout << byte;
                    //d = byte;
                    //cout << d << ' ' << byte << ' ' << endl;
                    k = 0;
                }
            }
        }
        if (k != 0) {
            byte << (8 - k);
            cout << byte;
        }
        fclose(f);
    } else {
        f = fopen(argv[2], "rb");
        freopen(argv[3], "w", stdout);
        unsigned char ch;
        int p = 5;
        int size_tree;
        fscanf(f,"%d", &p);
        size_tree = p;
        // cout << size_tree << endl;
        for (int i = 0; i < size_tree; i++) {
            fscanf(f, "%d %d %d %d\n", &tree[i].left, &tree[i].right, &tree[i].parent, &tree[i].symbol);
        }
        /*
        // TREE:
        for (int i = 0; i < size_tree; i++) {
            cout << tree[i].left << ' ' << tree[i].right << ' ' << tree[i].parent << ' ' << tree[i].symbol << endl;
        }
         */
        int pos  = size_tree - 1;
        while (fscanf(f, "%c", &ch) != -1) {

            //int d = ch;
            //cout << d << ' ' << ch << endl;
            int k = 7;
            while (k >= 0) {
                bool b = (bool((ch >> k)  &  1u));
                //cout << b;
                if (b == 0) {
                    pos = tree[pos].left;
                } else if (b == 1) {
                    pos = tree[pos].right;
                }
                if (tree[pos].left == -1 && tree[pos].right == -1) {
                    char sym =tree[pos].symbol;
                    cout  << sym;
                    pos = size_tree - 1;
                }
                k -= 1;
            }
        }

        fclose(f);

    }

}