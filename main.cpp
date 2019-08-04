#include <iostream>
#include "cmdparams.h"
#include <typeinfo>
#include <vector>
#include <fstream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[])
{
    CmdParams params(argc, argv);

    if (params.isValid())
    {
        std::ifstream InputFile(params.getInputFileName());
        if(!InputFile)
        {
            std::cerr << "\nОшибка: невозможно открыть входной файл по указанному пути \"" << params.getInputFileName() << "\"\n\n";
            return 0;
        }

        if (InputFile.peek() == std::ifstream::traits_type::eof())
        {
            std::cerr << "\nОшибка: файл пустой \"" << params.getInputFileName() << "\"\n\n";
            InputFile.close();
            return 0;
        }

        Parser parser(InputFile);
        if (parser.find(params.getColumnName(), params.getExpression()))
        {
            InputFile.close();
            std::string outputFileName = params.getOutputFileName();
            if(outputFileName.substr(outputFileName.size()-4, 4) != ".csv")
            {
                outputFileName += ".csv";
            }
            std::ofstream outFile(outputFileName);
            if(!outFile)
            {
                std::cerr << "\nОшибка: невозможно открыть выходной файл по указанному пути \"" << outputFileName << "\"\n\n";
                return 0;
            }

            //TODO Запись в  выходной файл

            outFile.close();
        }
        else
        {
            std::cerr << "\nНе найдено выражение: \"" << params.getExpression() << "\" \n"
                      << "в столбце: \"" << params.getColumnName() << "\" \n"
                      << "в файле: \"" << params.getInputFileName() << "\" \n\n";
            InputFile.close();
            return 0;
        }
    }
    return 0;
}
