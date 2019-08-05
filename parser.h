#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include "constants.h"
#include <vector>

class Parser
{
public:
    explicit Parser(std::istream& _inputFile);
    enum class Status
    {
        unQuotedField,
        qoutedField,
        qoutedQuote
    };
    bool find(const std::string inputColumnName, const std::string exp);
    std::vector<std::string> getCoincidence() const;
    Type convertStringToType(std::string strType);
    bool isDate(std::string str);
    bool isInt(std::string str);
    bool isFloat(std::string str);
    bool checkData(int day, int month, int year);
    std::vector<std::string> getCsvRow(std::string lineCsv);

private:
    struct Column
    {
        std::string columnName;
        Type typeName;
    };
    std::istream& inputFile;
    std::vector <Column> header;
    void getHeader();
    std::vector<unsigned int> IndexesColumn;
    bool noError{true};
    std::vector<std::string> coincidence;
};

#endif // PARSER_H
