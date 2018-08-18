//
// Created by wavator on 2018/8/14.
//

#ifndef UNTITLED_LOCAL_DEBUG_H
#define UNTITLED_LOCAL_DEBUG_H

#endif //UNTITLED_LOCAL_DEBUG_H

namespace DEBUG
{
#include <bits/stdc++.h>
    using std::to_string;
    using namespace std;

    string to_string(char x)
    {
        int y = x;
        return to_string(y);
    }

    string to_string(string s) { return '"' + s + '"'; }

    string to_string(const char* s) { return to_string((string) s); }

    string to_string(bool b) { return (b ? "true" : "false"); }

    template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

    template <class A>
    string to_string(stack<A> s)
    {
        bool f = true;
        string res = "{";
        while(!s.empty())
        {
            if (!f)
            {
                res += ", ";
            }
            f = false;
            res += to_string(s.top());
            s.pop();
        }
        return res + "}";
    }

    template <typename T>
    string to_string(queue<T> a)
    {
        string res = "{";
        bool f = true;
        while(!a.empty()){
            if(!f){
                res+=", ";
            }
            f = false;
            res+=to_string(a.front());
            a.pop();
        }
        return res+"}";
    }

    template <class b>
    string to_string(priority_queue<b> q) {
        bool f = true;
        string res = "{";
        while(!q.empty())
        {
            if (!f)
            {
                res += ", ";
            }
            f = false;
            b x = q.top();
            res += to_string(x);
            q.pop();
        }
        return res + "}";
    }
    template <class b>
    string to_string(priority_queue<b,vector<b>,greater<b> > q) {
        bool f = true;
        string res = "{";
        while(!q.empty())
        {
            if (!f)
            {
                res += ", ";
            }
            f = false;
            b x = q.top();
            res += to_string(x);
            q.pop();
        }
        return res + "}";
    }
    template <typename A>
    string to_string(A v) {
        bool first = true;
        string res = "{";
        for (const auto &x : v) {
            if (!first) {
                res += ", ";
            }
            first = false;
            res += to_string(x);
        }
        res += "}";
        return res;
    }
    void debug_out() {cerr<<endl;}
    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << " " << to_string(H);
        debug_out(T...);
    }
    
    struct freopener {
        freopener() {
            freopen("test.in","r",stdin);
        }
    };
    static freopener __freopen__;

}

#define debug(...) DEBUG::cerr << "[" << #__VA_ARGS__ << "]:", DEBUG::debug_out(__VA_ARGS__), fflush(stderr)
