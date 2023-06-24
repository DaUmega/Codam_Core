#ifndef Request_hpp
# define Request_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Server.hpp>

struct serverBlock;

class RequestHandler {
    private:
        std::string _rawRequest;
        std::vector<std::string> _requestLines;

        void        parse();
        bool        methodChecker();
        bool        uriChecker();
        bool        versionChecker();
        bool        contentTypeChecker(std::string value);
        bool        endChecker();
        bool        bodySizeChecker();
        std::string toLowerCase(const std::string &input);

    public:
        RequestHandler(serverBlock &input, std::string &raw_request);
        ~RequestHandler();

        std::string requestlineChecker();

        std::string returnCode;
        std::string method;
        std::string uri;
        std::string version;
        std::string contentType;
        std::string body;

        serverBlock &_copyBlock;
        std::map<std::string, std::string> reqValues;
};

#endif
