// Copyright 2021 NNTU-CS

#include <string>
#include "gtest/gtest.h"

std::string infixToPostfix(const std::string&);
int eval(const std::string&);

TEST(lab3, test1_1) {
    const std::string in = "(2+2)*2";
    const std::string exp = "2 2 + 2 *";
    const std::string out = infixToPostfix(in);
    EXPECT_TRUE(out == exp);
}

TEST(lab3, test1_2) {
    const std::string exp = "2 2 + 2 *";
    int out = evaluatePostfix(exp);
    EXPECT_EQ(out, 8);
}

TEST(lab3, test2_1) {
    const std::string in = "(2-1)*(6+2)";
    const std::string exp = "2 1 - 6 2 + *";
    const std::string out = infixToPostfix(in);
    EXPECT_TRUE(out == exp);
}

TEST(lab3, test2_2) {
    const std::string exp = "2 1 - 6 2 + *";
    int out = evaluatePostfix(exp);
    EXPECT_EQ(out, 8);
}

TEST(lab3, test3_1) {
    const std::string in = "(5+2)/6-(4+3)*5";
    const std::string exp = "5 2 + 6 / 4 3 + 5 * -";
    const std::string out = infixToPostfix(in);
    EXPECT_TRUE(out == exp);
}

TEST(lab3, test3_2) {
    const std::string exp = "5 2 + 6 / 4 3 + 5 * -";
    int out = evaluatePostfix(exp);
    EXPECT_EQ(out, -34);
}

TEST(lab3, test4_1) {
    const std::string in = "8*(3+7)/2-(3+7)*9";
    const std::string exp = "8 3 7 + * 2 / 3 7 + 9 * -";
    const std::string out = infixToPostfix(in);
    EXPECT_TRUE(out == exp);
}

TEST(lab3, test4_2) {
    const std::string exp = "8 3 7 + * 2 / 3 7 + 9 * -";
    int out = evaluatePostfix(exp);
    EXPECT_EQ(-50, out);
}
