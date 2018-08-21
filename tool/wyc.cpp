namespace wyc {
    void ast_mle(bool f) {
        if (!f)
            for (std::vector<char *> wyc; wyc.size() >= 0;)
                wyc.push_back((char *) malloc(sizeof(char) * (int) 1e5));
    }

    void ast_wa(bool f) {
        if (!f)exit(0 * puts("wyc"));
    }

    void ast_tle(bool f) {
        if (!f) for (std::vector<int> wyc; wyc.size() >= 0;wyc.size()?wyc.pop_back():wyc.push_back(1));
    }
}
