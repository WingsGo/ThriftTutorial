//
// Created by wangcong on 2019/9/10.
//

#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/Calculator.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;

class EnsureClose {
private:
    std::shared_ptr<TTransport>* _transport = nullptr;
public:
    explicit EnsureClose(std::shared_ptr<TTransport>& transport) : _transport(&transport) {}
    ~EnsureClose() {
        if (_transport != nullptr) {
            (*_transport)->close();
        }
    }
};

int main(int argc, char** argv) {
    std::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    CalculatorClient client(protocol);

    try {
        EnsureClose ensureClose(transport);
        transport->open();
        client.ping();
        std::cout << "ping()" << std::endl;

        std::cout << "1 + 1 = " << client.add(1, 1) << std::endl;

        Work work;
        work.op = Operation::DIVIDE;
        work.num1 = 1;
        work.num2 = 0;

        try {
            client.calculate(1, work);
            std::cout << "Whoa? We can divide by zero!" << std::endl;
        } catch (const InvalidOperation& op) {
            std::cout << "InvalidOperation: " << op.why << std::endl;
        }

        work.op = Operation::SUBTRACT;
        work.num1 = 15;
        work.num2 = 10;
        int32_t diff = client.calculate(1, work);
        std::cout << "15 - 10 = " << diff << std::endl;

        SharedStruct ss;
        client.getStruct(ss, 1);
        std::cout << "Received Log: " << ss << std::endl;
    } catch (const TException& tx) {
        std::cout << "ERROR: " << tx.what() << std::endl;
    }

    return 0;
}
