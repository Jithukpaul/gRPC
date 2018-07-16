#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "pingpong.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using pingpong::ping;
using pingpong::pong;
using pingpong::handl;
using namespace std;
class pingpongServer final : public handl::Service{
	Status pingpong(ServerContext* context,const ping* request,
		pong* reply)override{

		//string m=
		req(request->text());
		reply ->set_text("pong");
		return Status::OK;
	}
	void req(string n){
	if(n=="ping"){
		cout<<n<<endl;
	 		//return "pong";
	 	}

	}
};
void RunServer(){
	string server_address("0.0.0.0:50053");
	pingpongServer service;
	ServerBuilder builder;
	builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	unique_ptr<Server>server(builder.BuildAndStart());
	cout<<"server Listening on:"<<server_address<<endl;
	server->Wait();
}
int main(){
	RunServer();
	return 0;
}