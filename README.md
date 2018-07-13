# bdfs
Barun Distributed File System

The BDFS is influenced by GFS and HDFS. The main goal of this implementation is to document the evolution of a distributed filesystem from scratch and enable new programmers to run and play with a toy DFS which is production ready.

# The BDFS has three main components - 
- FS-Server
- Data Nodes
- Client Library

The FS-Server is the metadata layer of BDFS. It is the one which provides the abstraction of a filesystem to the user. The user accesses the “File System” using a client library (in C++) which they have linked into their applications. It must be ensured, that the client library is appropriately initialized to be able to access to correct instance of the BDFS. The actual data pertaining to the files are stored in blocks across data nodes. The blocks are replicated across various data-nodes by the FS-Server. It must be noted that BDFS is does not provide all the features of a POSIX compliant file system. BDFS does provide few useful APIs to the client. The Client APIs which will be supported are -

```
bdfs_init()
bdfs_open()
bdfs_close()
bdfs_read()
bdfs_write()
```

For the first version, a flat filesystem will be implemented, whereby all the files are under root “/”.  For the subsequent versions, a hierarchial version will be supported. The view of the hierarchial filesystem will be provided by the FS-Server

# RPCs 
The FS-Server never initiates a connection. It is passive and responds to any messages that the DataNode or the Client may send. 

## DataNode to FS-Server

```
node_connect()
node_disconnect()
node_heartbeat()
node_get_replicas()
```

## Client to FS-Server

```
init_connection() : Connects to a known port number
open_file() 
close_file()
find_file()
get_datanode()
get_data_replicas()
write_file()
```
