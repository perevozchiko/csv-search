#include "parser.h"

Parser::Parser(const std::ifstream &_inputFile) :
    inputFile(_inputFile)
{

}

bool Parser::find(const std::string columnName, const std::string exp)
{
    /*
* Получить хедер из входного файла
* Сравнить есть ли колонка из хедера (в виде энама название и тип) с колонкой входной если нет то вывести что нет такой колонки
* проверить входное выражение соответствует ли тип колонки если нет то вывести что не соотвествует тип колонки
* получить строку если в ней совпадает выражение из соответствующей колонки то добавляем в файл выходной
*
*/
    getHeader();
}

std::vector<Parser::Column> Parser::getHeader()
{

}

