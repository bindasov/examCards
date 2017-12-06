#ifndef cardsPacking_hpp
#define cardsPacking_hpp

#include <vector>
#include <fstream>
#include <string>

class examCards {
    struct Bin {
        unsigned a4height = 297;
        unsigned space = a4height;
        std::vector<int> height;
    };
    unsigned upperField; // верхнее поле
    unsigned field; // место для разреза
    std::vector<std::pair<int, int> > cards;
    std::vector<Bin> bins;
    std::vector<std::vector<int> > binsv;
public:
    examCards();
    ~examCards();
    std::vector<std::pair<int, int> > prepareCards(std::vector<std::pair<int, int> > cards);
    std::vector<std::vector<int> > BinPacking(std::vector<std::pair<int, int> > crds);
    std::vector<std::vector<int> > binsConverter(std::vector<Bin> bins);
};


#endif /* cardsPacking_hpp */
