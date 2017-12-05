#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class examCards {
    
    struct Bin {
        const unsigned a4height = 287; // А4 297 мм, пусть поле сверху будет 10 мм
        unsigned space = a4height; // свободное место на листе
        std::vector<int> cards;
    };
    
    std::vector<std::pair<int, int> > cards;
    std::vector<Bin> bins;
    double sum = 0;
    
public:
    
    void prepareCards(std::string fileName) {
        cards = ReadFromFile(fileName);
        std::sort(cards.begin(), cards.end(), [](auto &left, auto &right) {
            return left.second > right.second;
        }); //O(nlogn)
    }
    
    void countWidth() {
        for (int i=0; i<cards.size(); i++) {
            sum += cards[i].second;
        }
    }
    
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
        for (int i=0; i<cards.size(); i++) {
            if (cards[i].second>287) throw std::logic_error("Размер билета больше размера листа");
        }
        return cards;
    }
    
    void WriteToFile(const std::string outputName) {
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
    
    void countMin() {
        std::cout << "Минимальное необходимое количество листов: " << sum/bins[0].a4height << std::endl;
    }
    
    void BinPacking() {
        while (cards.size()!=0) {
            int min = INT_MAX;
            for (int i=0; i<bins.size(); i++) {
                if (bins[i].space != bins[i].a4height &&
                    bins[i].space < min &&
                    bins[i].space > cards.begin()->second) {
                    min = i;
                }
            }
            if (min != INT_MAX) {
                bins[min].cards.push_back(cards.begin()->first);
                bins[min].space-=cards.begin()->second;
            }
            else {
                bins.push_back(Bin());
                bins[bins.size()-1].cards.push_back(cards.begin()->first);
                bins[bins.size()-1].space-=cards.begin()->second;
            }
            cards.erase(cards.begin());
        }
    };
};

int main(int argc, const char * argv[]) {
    examCards ec;
    
    try {
        if (argc!=3) throw std::logic_error("Неверное количество аргументов");
        const std::string fileName = argv[1];
        const std::string outputName = argv[2];
        
        ec.prepareCards(fileName);
        ec.countWidth();
        ec.BinPacking();
        
        // Минимальное необходимое количество листов - сумма высот всех билетов (с учетом полей под ними) / размер листа А4 (без поля сверху)
        ec.countMin();
        
        ec.WriteToFile(outputName);
    }
    
    catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
