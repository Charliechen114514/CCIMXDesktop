#ifndef PARSEEXCEPTIONS_H
#define PARSEEXCEPTIONS_H
#include <QString>
#include <stdexcept>
class DivideZeroException : public std::runtime_error {
public:
    DivideZeroException()
        : std::runtime_error("") {
    }
    const char* what() const override {
        return "Divide Zero is not permitted!";
    }
};

class UnSupportedSymbol : public std::runtime_error {
public:
    UnSupportedSymbol(const QString symbol)
        : std::runtime_error(
              ("Meeting unsolved symbol: " + symbol).toStdString()) {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

class InvalidNumber : public std::runtime_error {
public:
    InvalidNumber()
        : std::runtime_error(
              "Meeting InvalidNumber!") {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

class UnSymmetryExpression : public std::runtime_error {
public:
    UnSymmetryExpression()
        : std::runtime_error(
              "UnSymmetry Expression!") {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

class GeneralParseError : public std::runtime_error {
public:
    GeneralParseError()
        : std::runtime_error(
              "Some Parse Error!") {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

class UnSupportiveFunction : public std::runtime_error {
public:
    UnSupportiveFunction(const QString symbol)
        : std::runtime_error(
              ("Meeting unsolved function: " + symbol).toStdString()) {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

class BadSqrtValue : public std::runtime_error {
public:
    BadSqrtValue()
        : std::runtime_error(
              "value sqrt is less then 0, which is not allowed!") {
    }
    const char* what() const override {
        return std::runtime_error::what();
    }
};

#endif // PARSEEXCEPTIONS_H
