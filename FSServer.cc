#include <grpcpp/grpcpp.h>
#include "datanode.grpc.pb.h"
#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class FSServerImpl final : public bdfs::datanode_protocol::Service{
   
    ::grpc::Status SendKeepalive(::grpc::ServerContext* context, const ::bdfs::keepalive_req* request, ::bdfs::keepalive_resp* response) {
	std::cout<<"Received Keepalive from :: " << request->node()._name() << std::endl;
	return grpc::Status::OK;
    }

    ::grpc::Status SendConnect(::grpc::ServerContext* context, const ::bdfs::connect_req* request, ::bdfs::connect_resp* response) {
        std::cout << "Received a connection request" << std::endl;
	::bdfs::fsserver_meta *server_meta = new ::bdfs::fsserver_meta();
        server_meta->set_keepalive_timeout(get_keepalive_timeout());
        response->set_allocated_server_meta(server_meta);
        return grpc::Status::OK;
    }

    ::grpc::Status SendDisconnect(::grpc::ServerContext* context, const ::bdfs::disconnect_req* request, ::bdfs::disconnect_resp* response) {
        std::cout << "Received a disconnection request" << std::endl;
        return grpc::Status::OK;
    }

    public:
    void set_keepalive_timeout(uint32_t to) {
	keepalive_timeout = to;	
    }
 
    uint32_t get_keepalive_timeout() {
        return keepalive_timeout;
    }

    private:
	uint32_t keepalive_timeout;
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  FSServerImpl service;
  service.set_keepalive_timeout(5);

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
