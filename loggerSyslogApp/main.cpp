#include "ComAPI.hpp"
#include "controllableProcess/ControllableProcessPlugin.hpp"
#include "controllableProcess/ControllableProcess.hpp"
#include "logger/LoggerPlugin.hpp"
#include "logger/Logger.hpp"
 #include <unistd.h>
#include <iostream>

using namespace commonApi;


int main()
{
    auto api = ComAPI::create();
    std::cout << "this is test " <<std::endl;
    
    bool runFlag(true); 
    //使用commonapi daemon 的Plugin
    setenv("COMMON_API_HTTP_HEARTBEAT_BIND_ADDRESS", "ip:%h:30000", 1);

    auto controllableProcess = controllableprocess::ControllableProcess::create(api);
    auto logInstance = logger::Logger::create(api, "gc test", LOG_INFO);

    while(1)
    {
        logInstance->write(LOG_ERR, "***************sync sent data**********\n", 100);
        logInstance->writeAsync(LOG_INFO, "***************Async sent data**********\n", 90);
        sleep(1);
    }


    controllableProcess->notifyReady();

    controllableProcess->setHeartbeatCb(
        [&controllableProcess]()
        {
            controllableProcess->heartbeatAck();
        }
    );

    controllableProcess->setTerminateCb(
        [&runFlag]()
        {
            std::cout << "clean resource" << std::endl;
            runFlag = false;
        }
    );

    while(runFlag)
    {
        api->waitAndHandleEvents();
    }
    return 0;
}
