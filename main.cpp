#include <cstdio>
#include <iostream>
#include <string>

#include "exprtk.hpp"

int main(int argc, const char** argv) {
    std::string expression_str = argc > 1 ? argv[1] : "(x + 10) * log10(y)";

    typedef exprtk::symbol_table<double>    symbol_table_t;
    typedef exprtk::expression<double>      expression_t;
    typedef exprtk::parser<double>          parser_t;

    symbol_table_t symbol_table;

    std::vector<std::string> variable_list;

    exprtk::collect_variables(expression_str, variable_list);

    double input_values[variable_list.size()];

    for (int i = 0; i < variable_list.size(); i++) {
        std::cout << variable_list[i] << "=";
        std::cin >> input_values[i];
        std::cout << input_values[i] << std::endl;
        symbol_table.add_variable(variable_list[i], input_values[i]);
    }

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_str, expression);

    double result = expression.value();

    printf("Result: %10.2f\n", result);

    return 0;
}
