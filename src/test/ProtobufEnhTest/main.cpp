#include <iostream>
#include <ZmqWrapper/ZmqWrapper.h>
#include <CpuTemperatureMsg/CpuTemperatureMsg.pb.h>

int main()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::SUBSCRIBE, "CPUTEMPERATURE");

    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
        if(res < 0){
            continue;
        }

        // raptor::protobuf::CpuTemperatureMsg cpuTemperatureMsg;
        // cpuTemperatureMsg.ParseFromString(msg);
        // std::cout << "temp: " << cpuTemperatureMsg.cputemperature() << std::endl;

        raptor::protobuf::CpuTemperatureMsg cpu_temperature_msg;
        cpu_temperature_msg.ParseFromString(msg);


        // Reflection APIを使用して動的にフィールドにアクセスし、値を取得して表示
        const google::protobuf::Descriptor* descriptor = cpu_temperature_msg.GetDescriptor();
        const google::protobuf::Reflection* reflection = cpu_temperature_msg.GetReflection();

        // viewName1フィールドの値を取得して表示
        const google::protobuf::FieldDescriptor* viewname1_field_descriptor = descriptor->FindFieldByName("viewName1");
        if (viewname1_field_descriptor) {
            std::string viewname1_value = reflection->GetString(cpu_temperature_msg, viewname1_field_descriptor);
            std::cout << "viewName1 value: " << viewname1_value << std::endl;
        } else {
            std::cout << "viewName1 field not found" << std::endl;
        }

        // cpuTemperatureフィールドの値を取得して表示
        const google::protobuf::FieldDescriptor* cputemperature_field_descriptor = descriptor->FindFieldByName("cpuTemperature");
        if (cputemperature_field_descriptor) {
            int32_t cputemperature_value = reflection->GetInt32(cpu_temperature_msg, cputemperature_field_descriptor);
            std::cout << "cpuTemperature value: " << cputemperature_value << std::endl;
        } else {
            std::cout << "cpuTemperature field not found" << std::endl;
        }

    }

    return 0;
}
