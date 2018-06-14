struct Trie_tree {
    static const int trie_sz = 26;
    struct Trie {
        Trie *nxt[trie_sz];
        int value;
    } *trie;

    Trie tries[102];

    Trie_tree(){}

    int top;

    void init() {
        top = 0;
        trie = new_Trie();
    }

    inline Trie* new_Trie() {
        return &tries[top++];
    }

    inline int get_trie_index(const char c) {
        return (int) (c - 'a');
    }

    inline void insert(const char *s, int len = 0) {
        if (len == 0)
            len = strlen(s);
        Trie *t = trie;
        for (int i = 0; i < len; ++i) {
            int c = get_trie_index(s[i]);
            if (t->nxt[c] == nullptr) {
                t->nxt[c] = new_Trie();
                t = t->nxt[c];
            } else
                t = t->nxt[c];
        }
        t->value = len;
    }

    bool path_in_trie(const char *s) {
        Trie *t = trie;
        for (int i = 0; s[i]; ++i) {
            int c = get_trie_index(s[i]);
            if (t->nxt[c] == nullptr)
                return false;
            t = t->nxt[c];
        }
        return true;
    }

    bool contains_in_trie(const char *s) {
        Trie *t = trie;
        for (int i = 0; s[i]; ++i) {
            int c = get_trie_index(s[i]);
            if (t->nxt[c] == nullptr)
                return false;
            t = t->nxt[c];
        }
        return t->value != 0;
    }
};
