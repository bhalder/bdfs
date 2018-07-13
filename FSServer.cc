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
        return grpc::Status::OK;
    }

    ::grpc::Status SendDisconnect(::grpc::ServerContext* context, const ::bdfs::disconnect_req* request, ::bdfs::disconnect_resp* response) {
        std::cout << "Received a disconnection request" << std::endl;
        return grpc::Status::OK;
    }

};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  FSServerImpl service;

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
