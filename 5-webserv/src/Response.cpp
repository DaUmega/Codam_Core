#include <Response.hpp>
#include <cstdlib>

ResponseHandler::ResponseHandler(serverBlock &input, std::string &location) : _copyBlock(input)
{
    _statusCode = input._responseCode;
    _uploadLocation = location.substr(location.find_first_of("/") + 1);
    initialize();
}

ResponseHandler::~ResponseHandler() {}

void    ResponseHandler::initialize() {
    _version = "HTTP/1.1";
    _header = "Content-Type: text/plain";
    _statusCodes["100"] = "Continue";
    _statusCodes["101"] = "Switching Protocols";
    _statusCodes["102"] = "Processing";
    _statusCodes["103"] = "Early Hints";
    _statusCodes["200"] = "OK";
    _statusCodes["201"] = "Created";
    _statusCodes["202"] = "Accepted";
    _statusCodes["203"] = "Non-Authoritative Information";
    _statusCodes["204"] = "No Content";
    _statusCodes["205"] = "Reset Content";
    _statusCodes["206"] = "Partial Content";
    _statusCodes["207"] = "Multi-Status";
    _statusCodes["208"] = "Already Reported";
    _statusCodes["226"] = "IM Used";
    _statusCodes["300"] = "Multiple Choices";
    _statusCodes["301"] = "Moved Permanently";
    _statusCodes["302"] = "Found";
    _statusCodes["303"] = "See Other";
    _statusCodes["304"] = "Not Modified";
    _statusCodes["305"] = "Use Proxy";
    _statusCodes["306"] = "Switch Proxy";
    _statusCodes["307"] = "Temporary Redirect";
    _statusCodes["308"] = "Permanent Redirect";
    _statusCodes["400"] = "Bad Request";
    _statusCodes["401"] = "Unauthorized";
    _statusCodes["402"] = "Payment Required";
    _statusCodes["403"] = "Forbidden";
    _statusCodes["404"] = "Not Found";
    _statusCodes["405"] = "Method Not Allowed";
    _statusCodes["406"] = "Not Acceptable";
    _statusCodes["407"] = "Proxy Authentication Required";
    _statusCodes["408"] = "Request Timeout";
    _statusCodes["409"] = "Conflict";
    _statusCodes["410"] = "Gone";
    _statusCodes["411"] = "Length Required";
    _statusCodes["412"] = "Precondition Failed";
    _statusCodes["413"] = "Payload Too Large";
    _statusCodes["414"] = "URI Too Long";
    _statusCodes["415"] = "Unsupported Media Type";
    _statusCodes["416"] = "Range Not Satisfiable";
    _statusCodes["417"] = "Expectation Failed";
    _statusCodes["418"] = "I'm a teapot";
    _statusCodes["421"] = "Misdirected Request";
    _statusCodes["422"] = "Unprocessable Entity";
    _statusCodes["423"] = "Locked";
    _statusCodes["424"] = "Failed Dependency";
    _statusCodes["425"] = "Too Early";
    _statusCodes["426"] = "Upgrade Required";
    _statusCodes["428"] = "Precondition Required";
    _statusCodes["429"] = "Too Many Requests";
    _statusCodes["431"] = "Request Header Fields Too Large";
    _statusCodes["451"] = "Unavailable For Legal Reasons";
    _statusCodes["500"] = "Internal Server Error";
    _statusCodes["501"] = "Not Implemented";
    _statusCodes["502"] = "Bad Gateway";
    _statusCodes["503"] = "Service Unavailable";
    _statusCodes["504"] = "Gateway Timeout";
    _statusCodes["505"] = "HTTP Version Not Supported";
    _statusCodes["506"] = "Variant Also Negotiates";
    _statusCodes["507"] = "Insufficient Storage";
    _statusCodes["508"] = "Loop Detected";
    _statusCodes["510"] = "Not Extended";
    _statusCodes["511"] = "Network Authentication Required";
    const char *uploads = (_copyBlock._root + "/" + _uploadLocation).c_str();
    mkdir(uploads, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

std::string ResponseHandler::generateResponse(RequestHandler &req) {
    std::string ret;
    std::ostringstream oss;

    _uri = req.uri;
    int slashLocation;
    if (_uri.find("http://") != std::string::npos)
    {
        _uri = _uri.substr(_uri.find('/', 7));
        if (_uri.find('/', 1) != std::string::npos)
            _uri = _uri.substr(0, _uri.find('/') - 1);
    }
    slashLocation = _uri.find("/");
    if (_uri.find('.') != std::string::npos)
    {
        int beforeFileLocation = _uri.find_last_of('/', _uri.find('.'));
        _location = _uri.substr(slashLocation, beforeFileLocation);
    }
    else if (_uri == "/")
        _location = "/";
    else
        _location = _uri.substr(slashLocation, _uri.find("/", 1));

    if (req._copyBlock._responseCode != "100") {
        _body = _statusCode + " " + _statusCodes[_statusCode] + "\r\n";
    }
    else if (not (_copyBlock._locations[_location]._allowedMethods.empty())
        && not (_copyBlock._locations[_location]._allowedMethods.find(req.method) != std::string::npos))
    {
        _statusCode = "405";
        _body = _statusCode + " " + _statusCodes[_statusCode];
    }
    else if (req.method == "GET")
        get();
    else if (req.method == "POST") {
        if (not post(req)) {
            _statusCode = "500";
            _body = "Upload failed";
        }
        else {
            _statusCode = "200";
            _body = "Upload successful";
        }
    }
    else if (req.method == "DELETE") {
        if (deleteReq(req)) {
            _statusCode = "404";
            _body = _statusCode + " " + _statusCodes[_statusCode];
        }
        else {
            _statusCode = "200";
            _body = "Delete successful";
        }
    }

    oss << _body.size();

    ret += _version + " " + _statusCode + " " + _statusCodes[_statusCode] + "\r\n";
    std::cout << "Server Response: " << ret;
    ret += _header + "\r\n";
    ret += "Content-Length: " + oss.str() + "\r\n";
    ret += "Connection: keep alive\r\n";
    ret += "\r\n" + _body;
    return ret;
}

// private methods
void    ResponseHandler::readHTML(const std::string &fileLocation) {
    std::string line;
    std::ostringstream oss;
    std::ifstream file(fileLocation.c_str());

    if (not file.good()) {
        _statusCode = "404";
        std::ifstream errors(_copyBlock._errorPage.c_str());
        if (not errors.good())
            _body = "404 Page Not Found";
        else {
            while (std::getline(errors, line))
                oss << line << "\n";
            _body = oss.str();
        }
    }
    else if (_statusCode == "301" && not _copyBlock._locations[_location]._index.empty()) {
        _header = "Location: http://" + _copyBlock._serverName.substr(0, _copyBlock._serverName.find_first_of(" "))
            + ":" + std::to_string(_copyBlock._port) + _uri + _copyBlock._locations[_location]._index;
        _body = "";
    }
    else {
        _statusCode = "200";
        while (std::getline(file, line))
            oss << line << "\n";
        _body = oss.str();
    }
}

void    ResponseHandler::get() {
    if (_uri == "/favicon.ico/" || _uri == "/_errors/main.css/")
        _uri = "/";

    if (_uri.find(".php") != std::string::npos && _uri.find(".php") == _uri.length() - 4)
    {
        phpCGI();
        // _body = "cgi executed";
        return;
    }

    if (not isDirectory(_copyBlock._root + _uri))
        _statusCode = "200";
    else if (_copyBlock._locations[_location]._directoryListing == false && _uri[_uri.length() - 1] != '/')
        _uri = _uri + "/";
    else if (_copyBlock._locations[_location]._directoryListing == true)
        getDirectoryListing(_copyBlock._root + _uri);

    if (_statusCode == "100") {
        _header = "Content-Type: text/html";
        _statusCode = "301";
        if (_copyBlock._locations[_location]._index.empty())
            readHTML(_copyBlock._root + _uri + "index.html");
        else
            readHTML(_copyBlock._root + _uri + _copyBlock._locations[_location]._index);
    }
    else if (_statusCode == "200") {
        _header = "Content-Type: text/html";
        if (_copyBlock._locations[_location]._directoryListing == false
            || (_copyBlock._locations[_location]._directoryListing == true && not isDirectory(_copyBlock._root + _uri)))
            readHTML(_copyBlock._root + _uri);
    }
    else if (_statusCode == "404") {
        _header = "Content-Type: text/html";
        readHTML(_copyBlock._errorPage);
    }
    else
        _body = _statusCode + " " + _statusCodes[_statusCode] + "\r\n";
}

static std::string getFilename(std::string body) {
    std::string filename = body.substr(body.find("filename=") + 9);
    filename = filename.substr(0, filename.find_first_of("\n") - 1);
    // trim trailing quotes
    filename = filename.substr(1, filename.find_last_of("\"") - 1);

    return (filename);
}

bool    ResponseHandler::post(RequestHandler &req) {
    std::size_t filePositon;
    std::string fileContent;
    filePositon = req.body.find("\r\n\r\n");
    fileContent = req.body.substr(filePositon + 4);
    fileContent = fileContent.substr(0, fileContent.find("-") - 2);

    std::string upload_file_location = _copyBlock._root + "/" + _uploadLocation + getFilename(req.body);

    std::ofstream file_recieve;
    file_recieve.open(upload_file_location.c_str(), std::ios::binary);
    if (not file_recieve.good())
        return (false);

    file_recieve << fileContent;
    file_recieve.close();

    return (true);
}

bool    ResponseHandler::deleteReq(RequestHandler &req) {
    std::string fileLocation = _copyBlock._root + "/" + _uploadLocation + req.uri.substr(req.uri.find_last_of("/") + 1);
    return std::remove(fileLocation.c_str());
}

bool    ResponseHandler::isDirectory(const std::string &location) {
    DIR* dir = opendir(location.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    else
        return false;
}

void    ResponseHandler::getDirectoryListing(const std::string &location)
{
    struct dirent *entry;
    _header = "Content-Type: text/html";
    _statusCode = "200";
    std::string temp = location;
    if (temp[temp.length() - 1] == '/')
        temp = temp.substr(0, temp.length() - 1);
    DIR* dir = opendir(temp.c_str());

    if (dir) {
        _body = "<html><body>\n";
        while ((entry = readdir(dir))) {
            std::string name = entry->d_name;
            std::string link = temp + "/" + name;
            if (link.find("www") != std::string::npos)
                link = link.substr(link.find("www") + 3);
            _body += "<a href=\"" + link + "\">" + name + "</a><br>\n";
        }
        _body += "</body></html>";
        closedir(dir);
    }
    else
        _statusCode= "404";
}

void    ResponseHandler::phpCGI()
{
    std::string phpPath = "/usr/bin/php";
    std::string www = "/www";
    char    cwd[FILENAME_MAX];
    getcwd(cwd, sizeof(cwd));

    std::string exec_path = cwd + www + _uri;
    char    *args[] = {const_cast<char*>(phpPath.c_str()), const_cast<char*>(exec_path.c_str()), NULL};

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        _statusCode = "500";
        _body = "Internal error.";
        return ;
    }

    int d_fd = 0;
    pid_t fork_pid = fork();
    if (fork_pid == -1) {
        _statusCode = "500"; // internal error
        close(pipe_fd[1]);
    }
    // child process
    if (fork_pid == 0) {
        close(pipe_fd[0]);
        d_fd = dup2(pipe_fd[1], STDOUT_FILENO);

        execve(phpPath.c_str(), args, NULL); // execve will exit(0) on succes.
        close(pipe_fd[1]);
        exit(500); // this will only be reached when execve fails.
    }
    // parrent process
    else {
        int	child_state;

        child_state = 0;
        waitpid(fork_pid, &child_state, WUNTRACED);
        if (child_state == 0) {
            close(pipe_fd[1]);
            _statusCode = "200";

            char    buffer[254];
            int read_ret;
            std::ostringstream oss;
            while(true) {
                read_ret = read(pipe_fd[0], buffer, sizeof(buffer));
                if (read_ret == 0)
                    break ;
                else if (read_ret == -1) {
                    _statusCode = "500";
                    _body = "Internal error.";
                    return ;
                }
                else
                    oss << buffer;
            }
            _header = "Content-Type: text/html";
            _body = oss.str();
            close(pipe_fd[0]);
        }
        else {
            _statusCode = "500";
            _body = "Internal error.";
        }
    }
}
