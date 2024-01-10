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

struct Tree{
    int left, right, parent, symbol;
    Tree() {
        symbol = -1;
    }
};
Tree tree[530];

int main()
{
    f = fopen("/Users/arpo/Desktop/razarhive/outputarh", "rb");
    freopen("/Users/arpo/Desktop/1.txt", "w", stdout);
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
