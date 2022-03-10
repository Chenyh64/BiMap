#include "BiMap.hpp"  

#include <iostream>

using namespace std;

namespace bimap {

void BiMap::update(int key, int value) { 
    mapping_[key] = offset_ + value; 
    mapping_[offset_ + value] = key;
    count++;
}

void BiMap::eraseByKey(int key) {
    mapping_[mapping_[key]] = -1;
    mapping_[key] = -1;
    count--;
}

void BiMap::eraseByValue(int value) {
    eraseByKey(mapping_[offset_ + value]);
}

int BiMap::getKeyByValue(int value) {
    return mapping_[offset_ + value];
}

int BiMap::getValueByKey(int key) {
    return mapping_[key] - offset_;
}


void BiMap::swapValueByKey(int key1, int key2) {
    int value1 = getValueByKey(key1);
    int value2 = getValueByKey(key2);
    update(key1, value2);
    update(key2, value1);
    count -= 2;
}

void BiMap::swapKeyByValue(int value1, int value2) {
    int key1 = getKeyByValue(value1);
    int key2 = getKeyByValue(value2);
    update(key1, value2);
    update(key2, value1);    
    count -= 2;
}


bool BiMap::hasKey(int key) {
    // return mapping_.find(key) != mapping_.end();
    return mapping_[key] != -1;
}

bool BiMap::hasValue(int value) {
    // return mapping_.find(offset_ + value) != mapping_.end();
    return mapping_[offset_ + value] != -1;
}

void BiMap::print() {
    for (int i = 0; i < offset_; i++) {
        if (mapping_[i] == -1) continue;
        printf("key: %d val: %d | ", i, mapping_[i]  - offset_ );
    }
    cout << endl;
}


bool BiMap::load_from_file(ifstream &mappingFile) {
    mappingFile >> offset_;
    mapping_ = vector<int>(2 * offset_, -1);

    int key = 0;
    int value;
    while (mappingFile >> value) {
        // NOTE: Currently we only consider 1-1 mapping.
        if (key >= offset_ || value >= offset_ || value < 0) {
            return false;
        }
        update(key, value);
        key += 1;
    }

    return true;
}


BiMap BiMap::reverse() {
    BiMap revMapping(offset_);
    for (int i = 0; i < offset_; i++) {
        if (mapping_[i] == -1) continue;
        revMapping.update(mapping_[i]  - offset_, i);
    }
    return revMapping; 
}

}  // namespace: bimap