#include "ExpressionEvaluator.h"
#include "core/ExpressionEvaluator.h"
#include <QString>
#include <cmath>
#include <iostream>

int totalTests = 0;
int failedTests = 0;

void assertEqual(const QString& expr, double expected, double tol = 1e-3) {
    ++totalTests;
    try {
        double result = ExpressionEvaluator::evalute_expression(expr);
        if (std::abs(result - expected) > tol) {
            ++failedTests;
            std::cerr << "[FAILED] " << expr.toStdString()
                      << " = " << result << ", expected " << expected << "\n";
        } else {
            std::cout << "[PASS]   " << expr.toStdString() << " = " << result << "\n";
        }
    } catch (const std::exception& e) {
        ++failedTests;
        std::cerr << "[FAILED] " << expr.toStdString() << " threw exception: " << e.what() << "\n";
    }
}

void assertThrows(const QString& expr) {
    ++totalTests;
    try {
        double result = ExpressionEvaluator::evalute_expression(expr);
        ++failedTests;
        std::cerr << "[FAILED] " << expr.toStdString() << " should throw, but got " << result << "\n";
    } catch (...) {
        std::cout << "[PASS]   " << expr.toStdString() << " threw as expected\n";
    }
}

int main() {
    std::cout << "==== ExpressionEvaluator Unit Tests ====\n";

    // 基本运算
    assertEqual("1 + 2", 3);
    assertEqual("5 - 3", 2);
    assertEqual("2 * 4", 8);
    assertEqual("8 / 2", 4);

    // 运算优先级
    assertEqual("2 + 3 * 4", 14);
    assertEqual("(2 + 3) * 4", 20);
    assertEqual("10 - 2 - 3", 5);

    // 一元负号
    assertEqual("-5", -5);
    assertEqual("-(2 + 3)", -5);
    assertEqual("4 + -2", 2);

    // 函数调用
    assertEqual("sin(3.1415926 / 2)", 1.0);
    assertEqual("cos(0)", 1.0);
    assertEqual("sqrt(16)", 4.0);
    assertEqual("log(1)", 0.0);

    // 嵌套表达式
    assertEqual("((2+3)*(4+1))", 25.0);
    assertEqual("sqrt(4 + sqrt(16))", 2.828);

    // 边界值
    assertEqual("0", 0.0);
    assertEqual("0.00001 + 1", 1.00001);
    assertEqual("999999 + 1", 1000000.0);

    // 异常表达式
    assertThrows("2 +");
    assertThrows("((3+2)");
    assertThrows("abc(3)");
    assertThrows("2 + * 3");
    assertThrows("3 / 0");
    assertThrows("10 / (5 - 5)");

    // 深层嵌套括号
    assertEqual("(((((((1+2)))))))", 3);
    assertEqual("(((((3+5)*2)-4)/2)+1)", 7);

    // 函数嵌套
    assertEqual("sqrt(sin(3.1415926/2) + cos(0))", sqrt(1 + 1)); ///< sqrt(2)
    assertEqual("sqrt(sqrt(16))", 2.0);

    // 一元负号 + 函数
    assertEqual("-sin(3.1415926)", -sin(3.1415926)); ///< ≈ 0
    assertEqual("-sqrt(9)", -3.0);
    assertEqual("sqrt(-3 * -3)", 3.0);

    // 多重负号
    assertEqual("--2", 2.0);
    assertEqual("---2", -2.0);
    assertEqual("4 + --1", 5.0);

    // 大数和小数处理
    assertEqual("1.0000000001 + 1", 2.0000000001);

    // 小数点容错
    assertEqual(".5 + .5", 1.0);
    assertEqual("5.", 5.0);
    assertEqual("0.1 + 0.2", 0.3); ///< 注意浮点精度

    // 多除法组合
    assertEqual("100 / 2 / 5", 10.0);
    assertEqual("8 / 2 * (2 + 2)", 16.0); ///< 测试“知名迷惑”表达式

    assertEqual("sin(0)^2 + cos(0)^2", 1.0);
    assertEqual("log(exp(3))", 3.0);

    assertThrows("sqrt(-1)"); ///< 应为复数，但不支持时抛出
    assertThrows("sin"); ///< 函数缺参
    assertThrows("sin()"); ///< 函数空参
    assertThrows("()"); ///< 空括号
    assertThrows("..2 + 1"); ///< 非法小数点
    assertThrows("1 + 2 3"); ///< 缺少运算符

    std::cout << "========================================\n";
    std::cout << "Tests run: " << totalTests << ", Passed: " << (totalTests - failedTests)
              << ", Failed: " << failedTests << "\n";

    return failedTests == 0 ? 0 : 1;
}
