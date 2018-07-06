inline void solve_chain(int x, int y, int val) {
    while (bl[x] != bl[y]){
        if (dep[bl[x]] < dep[bl[y]])
            swap(x, y);
        change(pos[bl[x]], pos[x], val, 1, n, 1);
        x = fa[bl[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    change(pos[x], pos[y], val, 1, n, 1);
}