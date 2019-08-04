#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include "constants.h"
#include <vector>

class Parser
{
public:
    enum class Status
    {
        unQuotedField,
        qoutedField,
        qoutedQuote
    };
    Parser(std::ifstream& _inputFile);
    bool find(const std::string inputColumnName, const std::string exp);

    std::vector<std::string> getCoincidence() const;

private:
    struct Column
    {
        std::string columnName;
        Type typeName;
    };
    std::ifstream& inputFile;
    std::vector <Column> header;
    void getHeader();
    std::vector<unsigned int> IndexesColumn;
    std::vector<std::string> getCsvRow(std::string lineCsv);
    Type convertStringToType(std::string strType);
    bool noError{true};
    bool isDate(std::string str);
    bool isInt(std::string str);
    bool isFloat(std::string str);
    bool checkData(int day, int month, int year);
    std::vector<std::string> coincidence;
};

#endif // PARSER_H
