// Copyright 2021 NNTU-CS

int main() {
    static int get_priority(char element) {
        if (element == '(') {
            return 0;
        } else if (element == ')') {
            return 1;
        } else if ((element == '+') || (element == '-')) {
            return 2;
        } else if ((element == '*') || (element == '/')) {
            return 3;
        } else {
            throw "Unknown Symbol!";
        }
    }
    return 0;
}
