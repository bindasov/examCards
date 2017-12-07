#ifndef cardsPacking_hpp
#define cardsPacking_hpp

#include <vector>
#include <fstream>
#include <string>

class examCards {
    struct Bin {
        unsigned a4height = 297; // высота листа А4
        unsigned space = a4height; // свободное место на листе
        std::vector<int> height; // набор высот билетов на листе
    };
    unsigned upperField; // верхнее поле
    unsigned field; // место для разреза
    std::vector<std::pair<int, int> > cards; // набор билеты (пара "номер - высота")
    std::vector<Bin> bins; // набор листов А4 типа Bin
    std::vector<std::vector<int> > binsv; // набор листов А4 для вывода
public:
    examCards();
    ~examCards();
    std::vector<std::pair<int, int> > prepareCards(std::vector<std::pair<int, int> > cards); // первоначальная обработка экзаменационных билетов
    std::vector<std::vector<int> > BinPacking(std::vector<std::pair<int, int> > crds); // алгоритм "упаковки"
    std::vector<std::vector<int> > binsConverter(std::vector<Bin> bins); // подготовка результата на вывод
};


#endif /* cardsPacking_hpp */
