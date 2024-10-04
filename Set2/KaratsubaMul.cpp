#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

struct Number {
    std::string digits;
    size_t len;
    Number() { std::cin >> digits; len = digits.size();}

    explicit Number(std::string str) : digits(std::move(str)) {}

    Number operator *(const Number& other) {
        int len1 = digits.length();
        int len2 = other.digits.length();
        if (len1 == 0 || len2 == 0) {
            return Number("0");
        }
        if (len1 <= 9 && len2 <= 9) {
            return Number(std::to_string(std::stoll(digits) * std::stoll(other.digits)));
        }
        if (len1 <= 5) {
            Number tmp = Number("0");
            for (int i = 0; i < stoll(digits); ++i) {
                tmp = tmp + other;
            }
            return tmp;
        }
        if (len2 <= 5) {
            Number tmp = Number("0");
            for (int i = 0; i < stoll(other.digits); ++i) {
                tmp = tmp + *this;
            }
            return tmp;
        }
        int mid = std::min(len1, len2) / 2;

        Number a(digits.substr(0, len1 - mid));
        Number b(digits.substr(len1 - mid, mid));
        Number c(other.digits.substr(0, len2 - mid));
        Number d(other.digits.substr(len2 - mid, mid));

        Number A = a * c;
        Number B = b * d;
        Number C = (a + b) * (c + d);
        Number D = C - A - B;

        for (int i = 0; i < 2 * mid; i++) {
            A.digits += '0';
        }
        for (int i = 0; i < mid; i++) {
            D.digits += '0';
        }
        return A + D + B;
    }
    Number operator +(const Number& other) {
        int len1 = digits.length();
        int len2 = other.digits.length();
        int carry = 0;
        std::string result;

        int i = len1 - 1;
        int j = len2 - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            if (i >= 0) {
                sum += digits[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += other.digits[j] - '0';
                j--;
            }

            carry = sum / 10;
            result += std::to_string(sum % 10);
        }

        std::reverse(result.begin(), result.end());
        return Number(result);
    }

    Number operator -(const Number& other) {
        std::string num1 = digits;
        std::string num2 = other.digits;

        num1 = std::string(std::max(num1.length(), num2.length()) - num1.length(), '0') + num1;
        num2 = std::string(std::max(num1.length(), num2.length()) - num2.length(), '0') + num2;

        int fl = 0;
        std::string ans;

        for (int i = std::max(num1.length(), num2.length()) - 1; i >= 0; i--) {
            int digit1 = num1[i] - '0';
            int digit2 = num2[i] - '0';
            int diff = digit1 - digit2 - fl;
            if (diff < 0) {
                diff += 10;
                fl = 1;
            } else {
                fl = 0;
            }

            ans += std::to_string(diff);
        }
        std::reverse(ans.begin(), ans.end());
        ans = ans.erase(0, ans.find_first_not_of('0'));
        return Number(ans);
    }
};


int KaratsubaMultiplication() {
    Number num1;
    Number num2;
    Number result = num1 * num2;
    std::cout << result.digits << std::endl;
    return 0;
}