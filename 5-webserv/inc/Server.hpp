#ifndef Server_hpp
# define Server_hpp

#include <queue>
#include <cstdlib>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <map>

#include <Request.hpp>

# define MAX_SIZE 1024
# define POLLSIZE 200

struct locationBlock {
  std::string _locationName;
  std::string _allowedMethods;
  std::string _index;
  bool        _directoryListing;
};

struct serverBlock {
  std::string _serverName;
  std::string _root;
  std::string _statusCode;
  std::string _responseCode;
  std::string _errorPage;
  size_t      _maxBodySize;
  int         _port;
  
  std::map<std::string, locationBlock> _locations;
  
  int start(void);
  int getSocket() const;

  int _skfd;
  // std::queue<Request> _requests;
  struct sockaddr_in _addr;
  int  _bind( void );
};

class Server {
  public:
    Server();
    Server(std::string &filename);
    Server(const Server &cp);
    Server &operator=(const Server &oth);
    ~Server();

    void        start();
    void        reorder_fds(size_t &actual_fds);
    std::string readSocketData(int socket);
    int         newConnection(int fd);
    void         closeConnection(struct pollfd *poll, int &actual_size);
  
  private:

    std::vector<serverBlock>  serverBlocks;
    int           _itPoll;
    struct pollfd _fds[POLLSIZE];
    std::map<int, int> _clFd;
    std::map<int, serverBlock> _servers;

    bool  parseConfig(std::string &filename);
    bool  parseLocation(std::ifstream &file, serverBlock &current, std::string &line);
    void  phpCGI(std::string &uri);
};

std::string substrBetweenChars(const std::string &input, char left, char right);

#endif