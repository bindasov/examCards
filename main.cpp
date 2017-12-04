#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct Bin {
    const int a4height = 287; // А4 297 мм, пусть поле сверху будет 10 мм
    int space = a4height; // свободное место на листе
    std::vector<int> cards;
};

std::vector<std::pair<int, int> > ReadFromFile(const std::string fileName) {
    int tmp = 0, id = 1;
    std::vector<std::pair<int, int> > cards;
    
    std::ifstream fin(fileName);
    while (!fin.eof()) {
        fin >> tmp;
        cards.push_back(std::make_pair(id, tmp));
        id++;
    }
    fin.close();
    return cards;
}

void WriteToFile(std::vector<Bin> bins, const std::string outputName) {
    std::ofstream fout(outputName);
    for (int i=0; i<bins.size(); i++) {
        fout << "Лист " << i+1 << ": ";
        for (int j=0; j<bins[i].cards.size(); j++) {
            fout << bins[i].cards[j];
            if (j==bins[i].cards.size()-1) {
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

void BinPacking(std::vector<std::pair<int, int> >* cards, std::vector<Bin> *bins) {
    while (cards->size()!=0) {
        
        int min = INT_MAX;
        for (int i=0; i<bins->size(); i++) {
            if (bins->at(i).space != bins->at(i).a4height &&
                bins->at(i).space < min &&
                bins->at(i).space > cards->begin()->second) {
                min = i;
            }
        }
        if (min != INT_MAX) {
            bins->at(min).cards.push_back(cards->begin()->first);
            bins->at(min).space-=cards->begin()->second;
        }
        else {
            bins->push_back(Bin());
            bins->at(bins->size()-1).cards.push_back(cards->at(0).first);
            bins->at(bins->size()-1).space-=cards->begin()->second;
        }
        cards->erase(cards->begin());
    }
};

int main(int argc, const char * argv[]) {
    const std::string fileName = argv[1];
    const std::string outputName = argv[2];
    
    std::vector<std::pair<int, int> > cards = ReadFromFile(fileName);
    
    std::sort(cards.begin(), cards.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    }); //O(nlogn)

    double sum = 0;
    for (int i=0; i<cards.size(); i++) {
        sum += cards[i].second;
    }
    
    std::vector<Bin> bins;
    BinPacking(&cards, &bins);
    
    // Минимальное необходимое количество листов - сумма высот всех билетов (с учетом полей под ними) / размер листа А4 (без поля сверху)
    std::cout << "Минимальное необходимое количество листов: " << sum/bins[0].a4height << std::endl;
    
    WriteToFile(bins, outputName);
    
    return 0;
}
