#include "cardsPacking.hpp"

examCards::examCards(std::array<int, 3> sizes) {
    ulField = sizes[1];
    field = sizes[2];
}

examCards::~examCards() {
}

std::vector<std::pair<int, int> > examCards::prepareCards(std::vector<std::pair<int, int> > cards, std::array<int, 3> sizes) {
    for (int i=0; i<cards.size(); i++) {
        //std::cout << cards[i].first << ":" << cards[i].second << std::endl;
        if ((cards[i].second+ulField*2)>sizes[0]) throw std::logic_error("Размер билета больше размера листа");
        if (cards.size()==1 && cards[i].second==0) throw std::logic_error("Пустой входной файл с высотами билетов");
        if (cards[i].second==0) throw std::logic_error("Нулевой размер билета недопустим");
    }
    std::sort(cards.begin(), cards.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    }); //O(nlogn)
//    for (int i=0; i<cards.size(); i++) {
//        std::cout << cards[i].first << ":" << cards[i].second << std::endl;
//    }
    return cards;
}

std::vector<std::vector<int> > examCards::BinPacking(std::vector<std::pair<int, int> > crds) {
    while (!crds.empty()) {
        int min = INT_MAX;
        
        /* Ищем наиболее заполненный лист, в который помещается данный билет */
        for (int i=0; i<bins.size(); i++) {
            if (bins[i].space != (bins[i].a4height-ulField*2) &&
                bins[i].space < min &&
                bins[i].space >= crds.begin()->second) {
                min = i;
            }
        }
        
        /* Если нашли, то "кладем" билет в этот лист */
        if (min != INT_MAX) {
            bins[min].height.push_back(crds.begin()->first);
            bins[min].space-=crds.begin()->second;
            if (bins[min].space >= field) bins[min].space-=field;
        }

        /* Иначе создаем новый пустой и "кладем" в него */
        else {
            bins.push_back(Bin()); // создаем новый лист
            bins[bins.size()-1].space-=ulField*2; // учитываем верхнее и нижнее поля
            bins[bins.size()-1].height.push_back(crds.begin()->first);
            bins[bins.size()-1].space-=crds.begin()->second;
            if (bins[bins.size()-1].space >= field) bins[bins.size()-1].space-=field;
        }
        crds.erase(crds.begin());
    }
    return binsConverter(bins);
}

std::vector<std::vector<int> > examCards::binsConverter(std::vector<Bin> bns) {
    binsv.resize(bns.size());
    for (int i=0; i<bins.size(); i++) {
        for (int j=0; j<bins[i].height.size(); j++) {
            binsv[i].push_back(bins[i].height[j]);
        }
    }
    return binsv;
}
