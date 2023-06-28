#pragma once

#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdio>
#include <dirent.h>
#include <Server.hpp>

struct serverBlock;

class ResponseHandler {
    private:
        std::string _uri;
        std::string _version;
        std::string _body;
        std::string _statusCode;
        std::string _uploadLocation;
        std::string _header;
        std::string _location;
        std::map<std::string, std::string> _statusCodes;
        serverBlock &_copyBlock;

        void    initialize(void);
        void    readHTML(const std::string &fileLocation);
        void    get();
        bool    post(RequestHandler &req);
        bool    deleteReq(RequestHandler &req);
        bool    isDirectory(const std::string &location);
        void    getDirectoryListing(const std::string &location);
        void    phpCGI(RequestHandler &req);

    public:
        ResponseHandler(serverBlock &input, std::string &location);
        ~ResponseHandler();

        std::string generateResponse(RequestHandler &req);
};
