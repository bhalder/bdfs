#include <grpcpp/grpcpp.h>
#include "../proto-out/datanode.grpc.pb.h"
#include <unistd.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using bdfs::keepalive_req;
using bdfs::keepalive_resp;
using bdfs::connect_req;
using bdfs::connect_resp;
using bdfs::disconnect_req;
using bdfs::disconnect_resp;
using bdfs::datanode_protocol;

namespace bdfs {
class DataNode {
 public:
  DataNode(std::shared_ptr<Channel> channel)
      : stub_(datanode_protocol::NewStub(channel)) {
    keepalive_count = 0;
    keepalive_duration = 1; // Default 1 second.
  }


  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  bool SendConnect(char *nodename) {
    // Data we are sending to the server.
    connect_req request;

    // Container for the data we expect from the server.
    connect_resp reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SendConnect(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      /* Set the keepalive duration */
      if(reply.has_server_meta()) {
          keepalive_duration = reply.server_meta().keepalive_timeout();
      }
  
      return true;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return false;
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SendKeepAlive(char *nodename) {
    // Data we are sending to the server.
    keepalive_req request;
    ::bdfs::node_meta* p = new (::bdfs::node_meta);
    p->set__name(nodename);
    request.set_allocated_node(p);

    // Container for the data we expect from the server.
    keepalive_resp reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SendKeepalive(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return "WOW";
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SendDisconnect(char *nodename) {
    // Data we are sending to the server.
    disconnect_req request;

    // Container for the data we expect from the server.
    disconnect_resp reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SendDisconnect(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      /* Set the keepalive duration */
      return "WOW";
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 uint64_t get_keepalive_count() {
    return keepalive_count;
 }

 uint64_t increment_keepalive_count() {
    return keepalive_count++;
 }

 uint32_t set_keepalive_duration(uint32_t to) {
     keepalive_duration = to;
 }

 uint32_t get_keepalive_duration() {
    return keepalive_duration;
 }

 private:
  uint64_t keepalive_count;
  uint32_t keepalive_duration;
  std::unique_ptr<datanode_protocol::Stub> stub_;
};

} // namespace bdfs

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  if(argc != 2) {
      std::cout << "\nIncorrect usage. Use ./Datanode <node-name>" << std::endl;
      return 0;
  }

  bdfs::DataNode datanode(grpc::CreateChannel(
  "localhost:50051", grpc::InsecureChannelCredentials()));

  // CONNECT
  while(!datanode.SendConnect(argv[1])) {
    std::cout << "Connection request failed." << std::endl;
    sleep(3);
  }

  // KEEPALIVE - Operational state
  while(1) {
      std::cout << "Sending Keepalive " << std::endl;
      datanode.SendKeepAlive(argv[1]);
      datanode.increment_keepalive_count();
      sleep(datanode.get_keepalive_duration());
      if(datanode.get_keepalive_count() == 15) {
	break;
      }
  }

  // DISCONNECT
  datanode.SendDisconnect(argv[1]);

  return 0;
}

