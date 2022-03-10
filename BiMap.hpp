#ifndef BIMAP_H
#define BIMAP_H
#pragma once

#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

namespace bimap {

// This class serves as a convenient wrapper for a bi-direction mapping between two value.
// Currently only support the mapping between two integer.
// TODO: Extend this class to support templates.
class BiMap  
{
	private:
		int offset_;
		// unordered_map<int, int> mapping_;
		vector<int> mapping_;
		int count = 0;

	public:

		BiMap() {};
		BiMap(int offset) : offset_(offset) { mapping_ = vector<int>(2 * offset_, -1); };
		~BiMap() {};

		void update(int key, int val);

		void eraseByKey(int key);

		void eraseByValue(int value);

		int getKeyByValue(int value);

		int getValueByKey(int key);

		void swapValueByKey(int key1, int key2);

		void swapKeyByValue(int value1, int value2);

		int size() { return count; }

		bool hasKey(int key);

		bool hasValue(int value);

		void print();

		bool load_from_file(ifstream &mappingFile);

		BiMap reverse();
};
#endif

}  // namespace: bimap