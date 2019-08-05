#ifndef TST_TESTDATE_H
#define TST_TESTDATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../parser.h"
#include "../../constants.h"
#include "../../cmdparams.h"
#include <istream>

using namespace testing;


struct inputExpression
{
    inputExpression(std::string _inputString, bool _result) :
        inputString(_inputString),
        result(_result)
    {}
    std::string inputString;
    bool result;
};

class testFuncIsDate : public ::testing::TestWithParam<inputExpression>
{};

INSTANTIATE_TEST_CASE_P(set, testFuncIsDate, ::testing::Values(

                            // Неправильные данные
                            inputExpression("00.00.0000", false)
                            , inputExpression("00.00.0001", false)
                            , inputExpression("01.00.0000", false)
                            , inputExpression("01.00.0001", false)
                            , inputExpression("32.01.0001", false)
                            , inputExpression("01.13.2000", false)
                            , inputExpression("29.02.1580", false)
                            , inputExpression("29.02.2019", false)
                            , inputExpression("29.02.1200", false)
                            , inputExpression("31.04.2222", false)
                            , inputExpression("12.022000", false)
                            , inputExpression("1202.2000", false)
                            , inputExpression("st.st.stri", false)
                            , inputExpression("2019.08.05", false)
                            , inputExpression("21,05.1985", false)
                            , inputExpression("12345678910", false)

                            // Правильные данные
                            , inputExpression("01.01.0001", true)
                            , inputExpression("31.12.9999", true)
                            , inputExpression("10.10.1000", true)
                            , inputExpression("31.01.9900", true)
                            , inputExpression("28.02.2019", true)
                            , inputExpression("31.03.2019", true)
                            , inputExpression("31.05.2999", true)
                            , inputExpression("31.07.3333", true)
                            , inputExpression("31.08.2019", true)
                            , inputExpression("31.08.2019", true)
                            , inputExpression("31.10.7890", true)
                            , inputExpression("31.12.3456", true)
                            , inputExpression("29.02.2016", true)
                            , inputExpression("29.02.1584", true)
                            , inputExpression("28.02.1200", true)
                            , inputExpression("29.02.2000", true)
                            ),);

TEST_P(testFuncIsDate, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f;
    Parser parse(f);
    bool actual = parse.isDate(param.inputString);
    bool expected = param.result;
    EXPECT_EQ(expected, actual);
}

class testFuncIsInt : public ::testing::TestWithParam<inputExpression>
{};

INSTANTIATE_TEST_CASE_P(set, testFuncIsInt, ::testing::Values(

                            // Неправильные данные
                            inputExpression("00.00.0000", false)
                            , inputExpression("12.022000", false)
                            , inputExpression("1202.2000", false)
                            , inputExpression("st.st.stri", false)
                            , inputExpression("2019.08.05", false)
                            , inputExpression("21,05.1985", false)
                            , inputExpression("9.", false)
                            , inputExpression("string", false)
                            , inputExpression("888888.", false)
                            , inputExpression(".2525252", false)
                            , inputExpression("", false)
                            , inputExpression(",", false)

                            // Правильные данные
                            , inputExpression("2000000000", true)
                            , inputExpression("0", true)
                            , inputExpression("1", true)
                            , inputExpression("1234", true)
                            ),);



TEST_P(testFuncIsInt, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f("fake");
    Parser parse(f);
    bool actual = parse.isInt(param.inputString);
    bool expected = param.result;
    EXPECT_EQ(expected, actual);
}

class testFuncIsFloat : public ::testing::TestWithParam<inputExpression>
{};

INSTANTIATE_TEST_CASE_P(set, testFuncIsFloat, ::testing::Values(

                            // Неправильные данные
                            inputExpression("0", false)
                            , inputExpression("12,02,2000", false)
                            , inputExpression("1202.2000", false)
                            , inputExpression("st.st,stri", false)
                            , inputExpression("201908,", false)
                            , inputExpression("211985", false)
                            , inputExpression("---", false)
                            , inputExpression("string", false)
                            , inputExpression("888888.", false)
                            , inputExpression(".2525252", false)
                            , inputExpression("", false)
                            , inputExpression(",", false)

                            // Правильные данные
                            , inputExpression("12345,01", true)
                            , inputExpression("0,123456", true)
                            , inputExpression("1,1", true)
                            , inputExpression("0,0", true)
                            ),);



TEST_P(testFuncIsFloat, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f("fake");
    Parser parse(f);
    bool actual = parse.isFloat(param.inputString);
    bool expected = param.result;
    EXPECT_EQ(expected, actual);
}

struct inputDate
{
    inputDate(int _day, int _month, int _year, bool _result) :
        day(_day),
        month(_month),
        year(_year),
        result(_result)
    {}
    int day;
    int month;
    int year;
    bool result;
};

class testCheckData : public ::testing::TestWithParam<inputDate>
{};

INSTANTIATE_TEST_CASE_P(set, testCheckData, ::testing::Values(

                            // Неправильные данные
                            inputDate(0, 0, 0, false)
                            , inputDate(30, 2, 2000, false)
                            , inputDate(0, 1, 2000, false)
                            , inputDate(23, 2, 0, false)
                            , inputDate(-30, 2, 2000, false)
                            , inputDate(30, 0, 2000, false)
                            , inputDate(30, 2, -2000, false)
                            , inputDate(28, 2, 99990, false)
                            , inputDate(33, 2, 2019, false)
                            , inputDate(12, 13, 2019, false)

                            // Правильные данные
                            , inputDate(1, 12, 2019, true)
                            , inputDate(1, 1, 1, true)
                            , inputDate(28, 2, 2019, true)
                            , inputDate(31, 12, 9999, true)
                            , inputDate(29, 2, 2016, true)
                            , inputDate(29, 2, 2000, true)

                            ),);

TEST_P(testCheckData, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f("fake");
    Parser parse(f);
    bool actual = parse.checkData(param.day, param.month, param.year);
    bool expected = param.result;
    EXPECT_EQ(expected, actual);
}

struct stringData
{
    stringData(std::string _strType, Type _result) :
       strType(_strType),
        result(_result)
    {}
    std::string strType;
    Type result;
};

class testConvertStrtingToType : public ::testing::TestWithParam<stringData>
{};

INSTANTIATE_TEST_CASE_P(set, testConvertStrtingToType, ::testing::Values(

                            // Неправильные данные
                            stringData("sfsdf", Type::Undefined)
                            , stringData("2342342@#@$", Type::Undefined)
                            , stringData("", Type::Undefined)
                            , stringData("0", Type::Undefined)
                            , stringData("Float ", Type::Undefined)
                            , stringData(" Float", Type::Undefined)

                            //Правильные данные
                            , stringData("Float", Type::Float)
                            , stringData("Integer", Type::Integer)
                            , stringData("Date", Type::Date)
                            , stringData("String", Type::String)
                            ),);

TEST_P(testConvertStrtingToType, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f("fake");
    Parser parse(f);
    Type actual = parse.convertStringToType(param.strType);
    Type expected = param.result;
    EXPECT_EQ(expected, actual);
}


struct csvRowData
{
    csvRowData(std::string _lineCsv, std::vector<std::string> _result) :
       lineCsv(_lineCsv),
        result(_result)
    {}
    std::string lineCsv;
    std::vector<std::string> result;
};

class testGetCsvRow : public ::testing::TestWithParam<csvRowData>
{};

INSTANTIATE_TEST_CASE_P(set, testGetCsvRow, ::testing::Values(

                            csvRowData("string;row;data", {"string", "row", "data"})
                            ),);

TEST_P(testGetCsvRow, testParserFunctions)
{
    const auto param = GetParam();
    //заглушка файл
    std::istringstream f("fake");
    Parser parse(f);
    std::vector<std::string> actual = parse.getCsvRow(param.lineCsv);
    std::vector<std::string> expected = param.result;
    EXPECT_EQ(expected, actual);
}




#endif // TST_TESTDATE_H
