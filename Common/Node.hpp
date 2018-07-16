#include <string>

#ifndef _NODE_H_
#define _NODE_H_

namespace bdfs {
namespace common {

class Node {
    private:

    uint64_t node_id;
    string node_name;
    string node_ip;
    string cluster;

    public:

    Node(string node_name,
         string node_cluster=NULL) {
        this.node_name = node_name;
        // TODO : Add a function under utils to find out the IP address. 
        this.node_ip = "localhost";
        cluster = "default";
    }

    uint64_t get_id() {
       return node_id;    
    }

    string get_name() {
        return node_name;
    }

    string get_ip() {
        return ip;
    }

    string get_cluster() {
        return cluster;
    }
}

} // namespace common
} // namespace node

#endif
