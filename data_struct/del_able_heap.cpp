struct del_able_heap {
    priority_queue<int> a, b;
    inline void push(int x) { a.push(x); }
    inline void erase(int x) { b.push(x); }
    inline void maintain() { while(!b.empty()&&a.top()==b.top())a.pop(),b.pop(); }
    inline void pop() {maintain();a.pop();}
    inline int size() {return a.size()-b.size();}
    inline int top() {maintain();return a.top();}
};
