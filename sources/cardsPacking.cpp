#include "cardsPacking.hpp"

examCards::examCards() {
    upperField = 10;
    field = 10;
}

examCards::~examCards() {
}

std::vector<std::pair<int, int> > examCards::prepareCards(std::vector<std::pair<int, int> > cards) {
    for (int i=0; i<cards.size(); i++) {
        if ((cards[i].second+upperField+field)>287) throw std::logic_error("Размер билета больше размера листа");
        cards[i].second+=field; // учитываем место для разреза или поле снизу
    }
    std::sort(cards.begin(), cards.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    }); //O(nlogn)
    return cards;
}

std::vector<std::vector<int> > examCards::BinPacking(std::vector<std::pair<int, int> > crds) {
    while (!crds.empty()) {
        int min = INT_MAX;
        
        /* Ищем наиболее заполненный лист, в который помещается данный билет */
        for (int i=0; i<bins.size(); i++) {
            if (bins[i].space != (bins[i].a4height-upperField) &&
                bins[i].space < min &&
                bins[i].space > crds.begin()->second) {
                min = i;
            }
        }
        
        /* Если нашли, то "кладем" билет в этот лист */
        if (min != INT_MAX) {
            bins[min].height.push_back(crds.begin()->first);
            bins[min].space-=crds.begin()->second;
        }

        /* Иначе создаем новый пустой и "кладем" в него */
        else {
            bins.push_back(Bin()); // создаем новый лист
            bins[bins.size()-1].space-=upperField; // учитываем поле сверху
            bins[bins.size()-1].height.push_back(crds.begin()->first);
            bins[bins.size()-1].space-=crds.begin()->second;
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
