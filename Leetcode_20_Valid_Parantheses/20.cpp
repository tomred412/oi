class Solution {
public:
    bool isValid(string s) {
        char stack[10000];
        int size = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            
            if (c == '(' || c == '{' || c == '[') {
                stack[size] = c;
                size++;
                continue;
            }
            if (c == ')') {
                if (size == 0) return false;
                if (stack[size - 1] != '(') return false;
                size--;
                continue;
            }
            if (c == '}') {
                if (size == 0) return false;
                if (stack[size - 1] != '{') return false;
                size--;
                continue;
            }
            if (c == ']') {
                if (size == 0) return false;
                if (stack[size - 1] != '[') return false;
                size--;
                continue;
            }

        }

        return (size == 0);
    }
};  
