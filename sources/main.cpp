#include "cardsPacking.hpp"
#include <iostream>
#include <fstream>

std::array<int, 3> getSizes(const std::string sF) {
    std::array<int, 3> arrSizes;
    
    std::ifstream fin(sF);
    if(fin.is_open()) {
        for (int i = 0; i < arrSizes.size(); i++) {
            if (fin.fail()) throw std::logic_error("Неверный формат входных данных в файле с размерами полей");
            fin >> arrSizes[i];
        }
    }
    fin.close();
    return arrSizes;
}

std::vector<std::pair<int, int> > ReadFromFile(const std::string fN) {
    int tmp = 0, id = 1;
    std::vector<std::pair<int, int> > cards;
    
    std::ifstream fin(fN);
    while (!fin.eof()) {
        if (fin.fail()) throw std::logic_error("Неверный формат входных данных в файле с высотами билетов");
        fin >> tmp;
        cards.push_back(std::make_pair(id, tmp));
        id++;
    }
    fin.close();
    return cards;
}

void WriteToFile(std::vector<std::vector<int> > bV, std::string outN) {
    std::ofstream fout(outN);
    for (int i=0; i<bV.size(); i++) {
        fout << "Лист " << i+1 << ": ";
        for (int j=0; j<bV[i].size(); j++) {
            fout << bV[i][j];
            if (j==bV[i].size()-1) {
                fout << ";";
            }
            else {
                fout << ", ";
            }
        }
        fout << std::endl;
    }
    fout.close();
}

int main(int argc, const char * argv[]) {
    try {
        examCards ec(getSizes(argv[1]));
        std::vector<std::pair<int, int> > cards = ReadFromFile(argv[2]);
        std::vector<std::vector<int> > result = ec.BinPacking(ec.prepareCards(cards, getSizes(argv[1])));
        WriteToFile(result, argv[3]);
    }
    
    catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
