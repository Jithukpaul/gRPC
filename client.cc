#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "pingpong.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using pingpong::ping;
using pingpong::pong;
using pingpong::handl;
using namespace std;

class pingpongClient{
	public:
		pingpongClient(std::shared_ptr<Channel> channel)
		: stub_(handl::NewStub(channel)){}
		string pingpong(string& msg){
			ping request;
			request.set_text(msg);
			pong reply;
			ClientContext context;
			Status status= stub_->pingpong(&context,request,&reply);
			if(status.ok()){
				return reply.text();
			}
			else{
				cout<<status.error_code()<<":"<<status.error_message()
				<<endl;
				return 0;
			}
		}
		private:
			std::unique_ptr<handl::Stub> stub_;
};
int main(){
	pingpongClient pingpon(grpc::CreateChannel("localhost:50053",
		grpc::InsecureChannelCredentials()));
	while(1){
	string m;
	getline(cin,m);//if(m=="ping")cout<<".";
	//string msg="ping";
	string reply=pingpon.pingpong(m);
	cout<<reply<<endl;}
}
