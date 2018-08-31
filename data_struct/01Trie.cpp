const int N = 300001;
struct _Trie {
    struct node {
        node * nxt[2];
        int value;
    } * trie;

    int top;

    static const int size = 32 * ::N;

    node tries[size];

    _Trie(){init();}

    inline node * new_node() {
        return &tries[top++];
    }

    void init(){
        memset(tries, 0, sizeof(node) * (top + 1));
        top = 0;
        trie = new_node();
    }

    inline void insert(int x) {
        node * t = trie;
        for (int i = 30; ~i; --i) {
            int c = x >> i & 1;
            if (t->nxt[c] == nullptr)
                t->nxt[c] = new_node();
            t = t->nxt[c];
            t->value++;
        }
    }

    inline int find_xor_min_and_del(int x) {
        node * t = trie;
        int res = 0;
        for (int i = 30; ~i; --i) {
            int c = (x >> i) & 1;
            if ((t->nxt[c] == nullptr) || t->nxt[c]->value == 0) {
                c ^= 1;
                res ^= (1 << i);
            }
            t = t->nxt[c];
            t->value--;
        }
        return res;
    }

    inline int find_xor_min(int x) {
        node * t = trie;
        int res = 0;
        for (int i = 30; ~i; --i) {
            int c = (x >> i) & 1;
            if ((t->nxt[c] == nullptr) || t->nxt[c]->value == 0) {
                c ^= 1;
                res ^= (1 << i);
            }
            t = t->nxt[c];
        }
        return res;
    }

    inline int find_xor_max_and_del(int x) {
        node * t = trie;
        int res = 0;
        for (int i = 30; ~i; --i) {
            int c = (x >> i) & 1;
            if (t->nxt[c ^ 1] == nullptr || t->nxt[c ^ 1]->value == 0) {
                c ^= 1;
            } else
                res ^= (1 << i);
            t = t->nxt[c];
            t->value--;
        }
        return res;
    }

    inline int find_xor_max(int x) {
        node * t = trie;
        int res = 0;
        for (int i = 30; ~i; --i) {
            int c = (x >> i) & 1;
            if (t->nxt[c ^ 1] == nullptr || t->nxt[c ^ 1]->value == 0) {
                c ^= 1;
            } else
                res ^= (1 << i);
            t = t->nxt[c];
        }
        return res;
    }

};
