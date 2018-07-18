# BDFS - Barun Distributed File System


The BDFS is influenced by GFS and HDFS. The main goal of this implementation is to document the evolution of a distributed filesystem from scratch and enable new programmers to run and play with a toy DFS which is production ready.

The code in this project is written with readability and understandability in mind. Performance is only secondary consideration. We hope to have a fully functional system which can scale upto 10,000 Nodes (because 10,000 nodes sounds cool. :p). The motivating application is a simple map reduce "grep" application.  

# The BDFS has three main components - 

- FS-Server
- Data Nodes
- Client Library

The FS-Server is the metadata layer of BDFS. We want to ensure that the metadata is small enough to fit within memory. We will be mostly C++ datastructures - vector/map/set. It is the one which provides the abstraction of a filesystem to the user. The user accesses the “File System” using a client library (in C++) which they have linked into their applications. It must be ensured, that the client library is appropriately initialized to be able to access to correct instance of the BDFS. The actual data pertaining to the files are stored in blocks across data nodes. The blocks are replicated across various data-nodes by the FS-Server. 

It must be noted that BDFS is does not provide all the features of a POSIX compliant file system. BDFS does provide few useful APIs to the client. 

```
bdfs_init()
bdfs_open()
bdfs_close()
bdfs_read()
bdfs_write()
```

# RPCs 
The FS-Server never initiates a connection. It is passive and responds to any messages that the DataNode or the Client may send. 

## DataNode to FS-Server

```
node_connect()
REQUEST : 
ip_address : string
name : string
id - if_any (new nodes will have this blank) : uint64

RESPONSE :
id : uint64
keepalive_duration : uint32


node_disconnect()
REQUEST : 
ip_address : string
id : uint64
name : string
block_list : block_t

RESPONSE : 


node_heartbeat()
REQUEST : 
id : uint64
keepalive_count : uint64

RESPONSE :
keepalive_count_ack : uint64
replication_request
block_list : block_t

node_get_replicas() - TBD
REQUEST :
RESPONSE :

node_block_summary()
REQUEST :
id : uint64
block_list : block_t

RESPONSE :

```

## Client to FS-Server
```
init_connection() : Connects to a known port number
REQUEST :
ip_address_client : string

RESPONSE


open_file() : 
REQUEST :
filename : string (fully qualified filename)

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


close_file()
REQUEST
filename : string (fully qualified filename)
RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


find_file()
REQUEST
filename : string (fully qualified filename)

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


get_datanode()
REQUEST
filename : string (fully qualified filename)

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


get_data_replicas()
REQUEST
filename : string (fully qualified filename)

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


write_file()
REQUEST
filename : string (fully qualified filename)
data : string

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string


read_file()
REQUEST
filename : string (fully qualified filename)

RESPONSE
result : enum (SUCCESS or FAILURE)
message : string
```

## Client to DataNode - TBD

## DataNode to DataNode - TBD

The datanode and fsserver, both communicate in datanode_protocol (Details TBD)

The client and fsserver communicate in client_protocol (Details TBD). Only thing that is pending is to pass the replication information from the namenode to various data transfers between client and datanodes without active involvement of namenode. Possibly that can be resolved using 

The fsserver to datanode communication happens as a responses to keepalive and other messages initiated by the datanode. 

# License
## The project is available under MIT license.
The code in this project is free for download and updates. 
