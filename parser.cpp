#include "parser.h"
#include <algorithm>
#include <iostream>

Parser::Parser(std::ifstream &_inputFile) :
    inputFile(_inputFile)
{

}

bool Parser::find(const std::string inputColumnName, const std::string exp)
{
    getHeader();

    if (!noError)
    {
        return 0;
    }
    Type expType;

    if (isInt(exp))
    {
        expType = Type::Integer;
    }
    else if (isFloat(exp))
    {
        expType = Type::Float;
    }
    else if (isDate(exp))
    {
        expType = Type::Date;
    }
    else
    {
        expType = Type::String;
    }

    IndexesColumn.clear();
    for (unsigned int i = 0; i < header.size(); i++)
    {
        Column column = header[i];
        if (column.columnName == inputColumnName && column.typeName == expType)
        {
            IndexesColumn.push_back(i);
        }
    }
    if (IndexesColumn.empty())
    {
        return false;
    }
    coincidence.clear();
    while(inputFile)
    {
        std::string rowLine;
        std::getline(inputFile, rowLine);
        std::vector<std::string>csvRows = getCsvRow(rowLine);
        for(unsigned int i : IndexesColumn)
        {
            if(csvRows[i] == exp)
            {
                coincidence.push_back(rowLine);
            }
        }
    }
    if (coincidence.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Parser::getHeader()
{
    std::string lineCsv;
    std::getline(inputFile, lineCsv);
    std::vector<std::string>fields;
    fields = getCsvRow(lineCsv);
    for (size_t i = 0; i < fields.size(); i++)
    {
        Column column;
        std::string str = fields[i];
        int space = static_cast<int>(std::count(str.begin(), str.end(), ' '));
        if (space == 1)
        {
            size_t spacePos = str.find(' ');
            column.columnName = str.substr(0, spacePos);
            std::string typeField = str.substr(spacePos+1);
            if (convertStringToType(typeField) != Type::Undefined)
            {
                column.typeName = convertStringToType(typeField);
            }
            else
            {
                noError = true;
                std::cerr << "\nОшибка: неправильный тип у колонки входного файла\n\n";
                break;
            }
        }
        else
        {
            noError = true;
            std::cerr << "\nОшибка: неправильное имя у колонки входного файла\n\n";
            break;
        }
        header.push_back(column);
    }
}

std::vector<std::string> Parser::getCsvRow(std::string lineCsv)
{
    std::vector<std::string> fields {""};
    Status status = Status::unQuotedField;
    size_t i = 0;
    for (char ch : lineCsv)
    {
        switch (status)
        {
        case Status::unQuotedField:
        {
            switch (ch)
            {
            case ';':
            {
                fields.push_back("");
                i++;
                break;
            }
            case '"':
            {
                status = Status::qoutedField;
                break;
            }
            default:
                fields[i].push_back(ch);
                break;
            }
            break;
        }

        case Status::qoutedField:
        {
            switch (ch)
            {
            case '"':
            {
                status = Status::qoutedQuote;
                break;
            }
            default:
            {
                fields[i].push_back(ch);
                break;
            }
            }
            break;
        }

        case Status::qoutedQuote:
        {
            switch (ch)
            {
            case ';':
            {
                fields.push_back("");
                i++;
                status = Status::unQuotedField;
                break;
            }
            case '"':
            {
                fields[i].push_back('"');
                status = Status::qoutedField;
            }
            }
            break;
        }
        }
    }
    return fields;
}

Type Parser::convertStringToType(std::string strType)
{
    if(strType == "Float")
    {
        return Type::Float;
    }
    else if (strType == "Integer")
    {
        return  Type::Integer;
    }
    else if (strType == "Date")
    {
        return  Type::Date;
    }
    else if(strType == "String")
    {
        return Type::String;
    }
    return  Type::Undefined;
}

bool Parser::isDate(std::string str)
{
    if (str.size() != 10)
    {
        return false;
    }
    if (std::count(str.begin(), str.end(), '.') != 2)
    {
        return false;
    }

    int point = 0;
    std::string strDay;
    std::string strMon;
    std::string strYear;
    for(char ch : str)
    {
        if (ch == '.')
        {
            point++;
        }
        if (isdigit(ch) && point == 0 && strDay.size() < 2)
        {
            strDay += ch;
        }
        if (point == 1 && isdigit(ch) && strMon.size() < 2)
        {
            strMon += ch;
        }
        if (point == 2 && isdigit(ch) && strYear.size() < 4)
        {
            strYear += ch;
        }
    }
    if (strDay.size() == 2 && strMon.size() == 2 && strYear.size() == 4)
    {
        int day = std::stoi(strDay);
        int month = std::stoi(strMon);
        int year = std::stoi(strYear);
        if (checkData(day, month, year))
        {
            return  true;
        }

    }
    else
    {
        return false;
    }
    return false;
}

bool Parser::isInt(std::string str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }
    long long numInt = std::stoi(str);
    if (numInt > maxIntLength)
    {
        return false;
    }
    return true;
}

bool Parser::isFloat(std::string str)
{
    int comma = 0;
    if (!isdigit(str[0]))
    {
        return false;
    }

    for (char ch : str)
    {
        if (!isdigit(ch) && ch != ',')
        {
            return  false;
        }
        if (ch == ',')
        {
            comma++;
        }
    }
    if (comma != 1)
    {
        return false;
    }
    return true;
}

bool Parser::checkData(int day, int month, int year)
{
    bool isLeapYear = false;
    if (day < 1 || day > 31)
    {
        return  false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }

    if ((month == 2 or month == 4 or month == 6 or month == 9 or month == 11) && day == 31)
    {
        return false;
    }

    if (year > 1582)
    {
        if(year%100 == 0)
        {
            isLeapYear = (year%400 == 0);
        }
        else
        {
            isLeapYear = (year%4 == 0);
        }
    }

    if (!isLeapYear && day == 29)
    {
        return false;
    }
    return true;
}

std::vector<std::string> Parser::getCoincidence() const
{
    return coincidence;
}
