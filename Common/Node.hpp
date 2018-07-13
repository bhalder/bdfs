#include <string>

#ifndef _NODE_H_
#define _NODE_H_

class Node {
    private:
        uint64_t node_id;
        string node_name;
        string node_ip;
        string node_cluster;

    public:
        Node(string node_name,
             string node_cluster=NULL) {
            this.node_name = node_name;
            this.node_ip = 
        }
             
}

#endif
