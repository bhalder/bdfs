#include <vector>
#include "../Datanode/DatanodeState.hpp"

namespace bdfs {
namespace block {

    class Block {
        uint64_t block_id;
        uint32_t replica_count;
        vector<bdfs::datanode_state DatanodeState> datanodes;
        
    }    

} // namespace block
} // namesapce bdfs
