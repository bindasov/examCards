#ifndef cardsPacking_hpp
#define cardsPacking_hpp

#include <vector>
#include <string>
#include <array>

class examCards {
    struct Bin {
        unsigned space; // свободное место на листе
        std::vector<int> height; // набор высот билетов на листе
    };
    std::vector<std::pair<int, int> > cards; // набор билеты (пара "номер - высота")
    std::vector<Bin> bins; // набор листов А4 типа Bin
    std::vector<std::vector<int> > binsv; // набор листов А4 для вывода
public:
    examCards();
    ~examCards();
    std::vector<std::pair<int, int> > prepareCards(std::vector<std::pair<int, int> > cards, const unsigned a4height, const unsigned ulField); // первоначальная обработка экзаменационных билетов
    std::vector<std::vector<int> > BinPacking(std::vector<std::pair<int, int> > crds, const unsigned a4height, const unsigned ulField, const unsigned field); // алгоритм "упаковки"
    std::vector<std::vector<int> > binsConverter(std::vector<Bin> bins); // подготовка результата на вывод
};


#endif /* cardsPacking_hpp */
