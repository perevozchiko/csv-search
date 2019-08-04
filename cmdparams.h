#ifndef CMDPARAMS_H
#define CMDPARAMS_H
#include <string>
#include <iostream>
#include "constants.h"

class CmdParams
{
public:
    CmdParams(int argc, char* argv[]);
    ~CmdParams();
    void showUsage();

    std::string getEncoding() const;
    void setEncoding(const std::string &value);

    std::string getOutputFileName() const;
    void setOutputFileName(const std::string &value);

    bool isValid();

    std::string getColumnName() const;
    void setColumnName(const std::string &value);

    std::string getExpression() const;
    void setExpression(const std::string &value);

    std::string getInputFileName() const;
    void setInputFileName(const std::string &value);

private:
    std::string encoding{defaultEncoding};
    std::string outputFileName{defaultOutPutFile};
    std::string columnName;
    std::string expression;
    std::string inputFileName;
    std::string appName;
    bool noErrors{true};
    void parseParams(int argc, char* argv[]);
    void errorCountArguments(int count);
    void showErrNoValue(std::string option);
    bool isValidOption(std::string option);
    void setParams(std::string option, std::string value);

};

#endif // CMDPARAMS_H
