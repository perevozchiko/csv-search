#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include "constants.h"
#include <vector>

class Parser
{
public:
    Parser(const std::ifstream& _inputFile);
    bool find(const std::string columnName, const std::string exp);

private:
    struct Column
    {
        std::string columnName;
        Type typeName;
    };
    const std::ifstream& inputFile;
    //std::vector <Column> header;
    std::vector<Column> getHeader();
};

#endif // PARSER_H
