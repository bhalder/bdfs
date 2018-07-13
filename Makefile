
all:
	protoc -I protos --cpp_out=proto-out protos/datanode.proto
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/datanode.pb.o proto-out/datanode.pb.cc
	protoc -I protos --grpc_out=proto-out --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` protos/datanode.proto
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/datanode.grpc.pb.o proto-out/datanode.grpc.pb.cc
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/FSServer.o FSServer.cc -Iproto-out
	g++ out/datanode.pb.o out/datanode.grpc.pb.o out/FSServer.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o out/FSServer
	g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o out/Datanode.o Datanode.cc -Iproto-out
	g++ out/datanode.pb.o out/datanode.grpc.pb.o out/Datanode.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o out/Datanode

clean:
	rm -rf out/* proto-out/*
