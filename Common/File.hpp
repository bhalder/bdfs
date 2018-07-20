#include <string>
#include <map>
#include <vector>
#include "../Datanode/DatanodeState.hpp"

namespace bdfs {
namespace file {
    class File {
        string filename;

        /* Only 0th bit used. 0 = directory type, 1 = regular type */
        uint32_t flags;
        uint64_t block_count;

        /* Various blocks for the file. Vector is chosen because
           increment in blocknumbers is always linear and continuous */
        vector<bdfs::datanode_state DatanodeState> blocks;

        /* The parent should always be a directory */
        File parent;        

        /* All the children of the file (only applicable for directories) */
        vector<File> children;
    }
} // namespace file
} // namespace bdfs
