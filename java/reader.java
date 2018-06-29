import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    private boolean oj = System.getProperty("ONLINE_JUDGE") != null;

    void solve() {
        
    }

    private BufferedReader reader;
    private StringTokenizer read_token;
    private PrintWriter out;
    void run() {
        reader = new BufferedReader(new InputStreamReader(System.in), 32768);
        read_token = null;
        long st = System.currentTimeMillis();
        solve();
        out = new PrintWriter(System.out);
        tr(System.currentTimeMillis() - st);
        out.close();
    }
    private void tr(Object...o) {
        if (!oj)
            System.err.println(Arrays.deepToString(o));
    }
    String ns() {
        while (read_token == null || !read_token.hasMoreTokens()) {
            try {
                read_token = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return read_token.nextToken();
    }
    int ni() {
            return Integer.parseInt(ns());
        }
    long nl() {
            return Long.parseLong(ns());
        }
    public static void main(String[] args) {
        new Main().run();
    }
}