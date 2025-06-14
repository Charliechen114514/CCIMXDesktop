#ifndef PARSEEXCEPTIONS_H
#define PARSEEXCEPTIONS_H

#include <QString>
#include <stdexcept>

/**
 * @brief Exception thrown when a division by zero is attempted.
 */
class DivideZeroException : public std::runtime_error {
public:
    /**
     * @brief Constructs a DivideZeroException with a predefined message.
     */
    DivideZeroException()
        : std::runtime_error("") {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return "Divide Zero is not permitted!";
    }
};

/**
 * @brief Exception thrown when an unsupported symbol is encountered during parsing.
 */
class UnSupportedSymbol : public std::runtime_error {
public:
    /**
     * @brief Constructs the exception with the unsupported symbol.
     * @param symbol The unsupported symbol.
     */
    explicit UnSupportedSymbol(const QString symbol)
        : std::runtime_error(
              ("Meeting unsolved symbol: " + symbol).toStdString()) {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

/**
 * @brief Exception thrown when an invalid number is detected.
 */
class InvalidNumber : public std::runtime_error {
public:
    /**
     * @brief Constructs an InvalidNumber exception.
     */
    InvalidNumber()
        : std::runtime_error(
              "Meeting InvalidNumber!") {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

/**
 * @brief Exception thrown when an expression has unbalanced parentheses or structure.
 */
class UnSymmetryExpression : public std::runtime_error {
public:
    /**
     * @brief Constructs an UnSymmetryExpression exception.
     */
    UnSymmetryExpression()
        : std::runtime_error(
              "UnSymmetry Expression!") {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

/**
 * @brief General-purpose exception thrown during parse errors not covered by other exceptions.
 */
class GeneralParseError : public std::runtime_error {
public:
    /**
     * @brief Constructs a GeneralParseError exception.
     */
    GeneralParseError()
        : std::runtime_error(
              "Some Parse Error!") {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

/**
 * @brief Exception thrown when an unsupported function is encountered during parsing.
 */
class UnSupportiveFunction : public std::runtime_error {
public:
    /**
     * @brief Constructs the exception with the unsupported function name.
     * @param symbol The unsupported function name.
     */
    explicit UnSupportiveFunction(const QString symbol)
        : std::runtime_error(
              ("Meeting unsolved function: " + symbol).toStdString()) {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

/**
 * @brief Exception thrown when a square root operation receives a negative value.
 */
class BadSqrtValue : public std::runtime_error {
public:
    /**
     * @brief Constructs a BadSqrtValue exception.
     */
    BadSqrtValue()
        : std::runtime_error(
              "value sqrt is less then 0, which is not allowed!") {
    }

    /**
     * @brief Returns the error message.
     * @return C-style string with the error description.
     */
    const char* what() const noexcept override{
        return std::runtime_error::what();
    }
};

#endif // PARSEEXCEPTIONS_H
