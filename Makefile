

protos: ./protos/*.proto
	protoc -I protos --cpp_out=proto-out protos/types.proto
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/types.pb.o proto-out/types.pb.cc
	protoc -I protos --cpp_out=proto-out protos/datanode.proto
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/datanode.pb.o proto-out/datanode.pb.cc
	protoc -I protos --grpc_out=proto-out --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` protos/datanode.proto
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/datanode.grpc.pb.o proto-out/datanode.grpc.pb.cc

#out/datanode.pb.o: protos
#out/datanode.grpc.pb.o: protos

datanode: out/datanode.pb.o out/datanode.grpc.pb.o 
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/Datanode.o Datanode/Datanode.cc -Iproto-out
	g++ out/datanode.pb.o out/datanode.grpc.pb.o out/types.pb.o  out/Datanode.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o out/Datanode

fsserver: out/datanode.pb.o out/datanode.grpc.pb.o
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/FSServer.o FSServer/FSServer.cc -Iproto-out
	g++ out/datanode.pb.o out/datanode.grpc.pb.o out/types.pb.o out/FSServer.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o out/FSServer

all: protos datanode fsserver

.PHONY: protos clean all

clean:
	rm -rf out/* proto-out/*
