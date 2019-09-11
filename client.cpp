//
// Created by wangcong on 2019/9/10.
//

#include "gen-cpp/Serv.h"
#include "gen-cpp/student_constants.h"
#include "gen-cpp/student_types.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <memory>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using std::shared_ptr;

int main(int argc, char** argv) {
    shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    transport->open();

    Student s;
    s.sno = 123;
    s.sname = "wangcong";
    s.ssex = 1;
    s.sage = 18;

    ServClient client(protocol);
    printf("sno = %d, sname = %s, ssex = %d, sage = %d\n", s.sno, s.sname.c_str(), s.ssex, s.sage);
    client.put(s);
    std::string strname = "";
    client.scall(strname, s);
    printf("icall = %d, scall = %s\n", client.icall(s), strname.c_str());
    transport->close();
    return 0;
}
