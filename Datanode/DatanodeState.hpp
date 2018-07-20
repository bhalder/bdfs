#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../Common/Block.hpp"

using namespace std;

namespace bdfs {
namespace datanode_state {

    class DatanodeState {
        string datanode_name;
        vector<int> some_numbers;
        vector<bdfs::block Block> blocks;

        /* Map of block_id to the location where the block is locally stored */
        map<uint64_t, string> block_local; 

        public :
        DatanodeState(string name) {
            datanode_name = name;
        }

        string get_name() {
            return datanode_name;
        }

        vector<int> get_some_numbers() {
            return some_numbers;
        }
    };
} // namespace datanode_state
} // namespace bdfs
