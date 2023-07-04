#include <iostream>
#include <atomic>
#include <string>
#include <signal.h>

#include "httplib.h"

static httplib::Server server;

inline void SignalHandler(int s) noexcept { 
    (void)s; 
    std::cout << "Closing server..." << std::endl;
    server.stop(); 
}

int main()
{
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = SignalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    server.Get("/test", [](const httplib::Request &req, httplib::Response &res){
        std::cout << req.path << " -> " << req.content_length_ << std::endl;
        static std::atomic<int> _countOfVisitors {0};

        constexpr const auto contentType = "text/plain";
        const std::string visitorWeb = "Number of visitors: " + std::to_string(++_countOfVisitors);        
        res.set_content(visitorWeb.c_str(), contentType);
    });

    server.Get("/", [](const httplib::Request &req, httplib::Response &res){
        constexpr const auto contentType = "text/plain";
        const std::string visitorWeb = "Default site";
        res.set_content(visitorWeb.c_str(), contentType);
    });

    server.stop();

    {
        const auto result = server.listen("0.0.0.0", 8088);        
        std::cout << "Started listening on port 8088 -> " << (result ? "true" : "false") << std::endl;
    }

    return 0;
}