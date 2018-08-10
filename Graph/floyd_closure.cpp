        for (int i = 1; i <= n; ++i) {
            a[i].reset();
            a[i][i] = 1;
        }
        for (int i = 1, k, v; i <= n; ++i) {
            for (scanf("%d", &k); k--; ) {
                scanf("%d", &v);
                a[i][v] = 1; // a[i] -> a[j] = 1
            }
        }
        for (int j = 1; j <= n; ++j) {
            for (int i = 1; i <= n; ++i) {
                if (a[i][j]) {
                    a[i] |= a[j];
                }
            }
        }
