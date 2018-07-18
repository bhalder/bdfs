#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace bdfs {
namespace datanode_state {

    class DatanodeState {
        string datanode_name;
        vector<int> some_numbers;

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
