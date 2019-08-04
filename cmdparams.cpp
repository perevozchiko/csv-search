#include <cstring>
#include "cmdparams.h"
#include "constants.h"
#include <string>

CmdParams::CmdParams(int argc, char* argv[])
{
    appName = argv[0];
    if (argc > 1)
    {
        parseParams(argc, argv);
    }
    else
    {
        showUsage();
        return;
    }

    if (inputFileName.empty())
    {
        noErrors = false;
        std::cerr << "\nОшибка: не указано имя входного файла. Задайте имя файла с помощью параметра \"-in <имя_входного_файла>\"\n\n";
    }
    if (columnName.empty())
    {
        noErrors = false;
        std::cerr << "\nОшибка: не указано имя столбца в которой необходимо искать. Задайте имя колонки с помощью параметра \"-col <имя_столбца>\"\n\n";
    }
    if (expression.empty())
    {
        noErrors = false;
        std::cerr << "\nОшибка: не указано выражение для поиска. Задайте выражение с помощью параметра \"-exp <выражение_для_поиска>\"\n\n";
    }
}

CmdParams::~CmdParams()
{

}

void CmdParams::showErrNoValue(std::string option)
{
    std::cerr << "\nОшибка: не введено значение для параметра \"" << option << "\"" << std::endl << std::endl;
}

bool CmdParams::isValidOption(std::string option)
{
    if (option == "-col" ||
            option == "-exp" ||
            option == "-enc" ||
            option == "-out" ||
            option == "-in" ||
            option == "-help"||
            option == "-h")
    {
        return  true;
    }

    return false;
}

void CmdParams::setParams(std::string option, std::string value)
{

    if (option == "-col")
    {
        setColumnName(value);
    }
    else if (option == "-in")
    {
        setInputFileName(value);
    }
    else if (option == "-out")
    {
        setOutputFileName(value);
    }
    else if(option == "-enc")
    {
        setEncoding(value);
    }
    else if (option == "-exp")
    {
        setExpression(value);
    }
    else if (option == "-help" || option == "-h")
    {
        showUsage();
    }
}

void CmdParams::parseParams(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string option;
        std::string value;

        if (argv[i][0] == '-' && strlen(argv[i]) > 1)
        {
            option = argv[i];
            int nextArg = i + 1;

            if (nextArg < argc)
            {
                value = argv[nextArg];
                i++;
            }
        }
        else
        {
            noErrors = false;
            std::cerr << "\nОшибка: \"" << argv[i] << "\"" << " - не является параметром\n\n";
            showUsage();
            return;
        }

        if (isValidOption(option))
        {
            if (value.empty() && option != "-help" && option != "-h")
            {
                showErrNoValue(option);
            }
            else
            {
                setParams(option, value);
            }
        }
        else
        {
            noErrors = false;
            std::cerr << "\nОшибка: \"" << option << "\"" << " - неизвестный параметр\n\n";
            showUsage();
            return;
        }
    }
}

void CmdParams::showUsage()
{
    noErrors = false;
    if(appName.empty())
    {
        appName = "<имя программы>";
    }

    std::cerr << "\nИспользование:\n\t"
              << appName << "\t-in <входной_файл> -exp <выражения_для_поиска>"
                            "\n\t\t\t-col <имя_столбца> [-enc <кодировка>]"
                            "\n\t\t\t[-out <выходной_файл>]"
              << std::endl << std::endl;

    std::cerr << "Параметры:"
                 "\n\t-in\tУстановить название входного файла (обязательный параметр)"
              << "\n\t-exp\tУстановить выражения для поиска (обязательный параметр)"
              << "\n\t-col\tУстановить имя в колонке в которой необходимо искать (обязательный параметр)"
              << "\n\t-enc\tУстановить кодировку, значение по умолчанию \"" << defaultEncoding << "\""
              << "\n\t-out\tУстановить имя выходного файла, значение по умолчанию \"" << defaultOutPutFile << "\""
              << std::endl << std::endl;
}

std::string CmdParams::getEncoding() const
{
    return encoding;
}

void CmdParams::setEncoding(const std::string &value)
{
    encoding = value;
}

std::string CmdParams::getOutputFileName() const
{
    return outputFileName;
}

void CmdParams::setOutputFileName(const std::string &value)
{
    outputFileName = value;
}

bool CmdParams::isValid()
{
    return noErrors;
}

std::string CmdParams::getColumnName() const
{
    return columnName;
}

void CmdParams::setColumnName(const std::string &value)
{
    columnName = value;
}

std::string CmdParams::getExpression() const
{
    return expression;
}

void CmdParams::setExpression(const std::string &value)
{
    expression = value;
}

std::string CmdParams::getInputFileName() const
{
    return inputFileName;
}

void CmdParams::setInputFileName(const std::string &value)
{
    inputFileName = value;
}


