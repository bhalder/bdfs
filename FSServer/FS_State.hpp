#include <string>
#include <vector>
#include "../Datanode/DatanodeState.hpp"

#ifndef _FS_STATE_H_
#define _FS_STATE_H_

class FS_State {
    private:
	    string ip;
        int32_t port;
        vector <bdfs::datanode_state DatanodeState> datanodes;
        
 
    public:

}

#endif
