#include <Server.hpp>
#include <Response.hpp>

# define ERROR -1

Server::Server() {}

Server::Server(std::string &filename) {
  if (!parseConfig(filename))
    throw std::runtime_error("Config File Error(s).\n");
}

Server::Server(const Server &cp) {
  *this = cp;
}

Server &Server::operator=(const Server &other) {
  if (this == &other) {
		return *this;
	}
  
  return *this;
}

Server::~Server() {
  for (size_t i = 0; i < serverBlocks.size(); i++)
  {  
    if (serverBlocks[i]._skfd > 0)
      close(serverBlocks[i]._skfd);
  }
}

std::string Server::readSocketData(int clientSocket) {
  std::vector<char> buffer(MAX_SIZE);

  std::string message;
  ssize_t bytesRead;
  do {
    bytesRead = recv(clientSocket, &buffer[0], MAX_SIZE, 0);
    if (bytesRead > 0) {
      message += std::string(&buffer[0], bytesRead);
    }
  } while (bytesRead == MAX_SIZE);

  return message;
}

int serverBlock::getSocket() const {
  return _skfd;
}

int serverBlock::_bind() {
  memset(&_addr, 0, sizeof(_addr));
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(_port);// _conf.getPort()
  return bind(_skfd, reinterpret_cast<struct sockaddr*>(&_addr), sizeof(_addr));
}

int serverBlock::start() {
  _skfd = socket(AF_INET, SOCK_STREAM, 0);
  if (_skfd == -1)
    throw std::exception();
  fcntl(_skfd, F_SETFL, O_NONBLOCK);
  int reuseAddr = 1;
  if (setsockopt(_skfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) < 0) {
      close(_skfd);
      throw std::runtime_error("Failed to set socket options");
  }
  if (_bind() < 0)
    throw std::runtime_error("Bind failed");
  if (listen(_skfd, POLLSIZE) < 0)
    throw std::runtime_error("Listen failed");

  std::cout << "Listening on port " << _port << std::endl;
  return (_skfd);
}

int Server::newConnection(int fd) {
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(struct sockaddr_in);
  int new_conn = accept(fd, reinterpret_cast<struct sockaddr*>(&addr), &addr_len);
  if (new_conn < 0)
  {
    if (errno != EWOULDBLOCK) {
      std::cout << "Accept error decide how to handle it" << std::endl;
      std::cout << strerror(errno) << std::endl;
      return (-2);
    }
    return (ERROR);
  }

  // non blocking
  if (fcntl(new_conn, F_SETFL, O_NONBLOCK) == ERROR)
  {
    std::cout << "Fcntl error" << std::endl;
    close(new_conn);
    exit(EXIT_FAILURE);
  }

  int enable = 1;
  if (setsockopt(new_conn, SOL_SOCKET, SO_NOSIGPIPE, &enable, sizeof(int)) == ERROR)
  {
    std::cout << "Setsockopt error" << std::endl;
    close(new_conn);
    exit(EXIT_FAILURE);
  }
  return (new_conn);
}

void Server::reorder_fds(size_t &actual_fds) {
  for (size_t i = 0; i < actual_fds; i++) {
    if (_fds[i].fd == 0) {
      size_t size = actual_fds;
      for (size_t j = i + 1; j <= size; j++, i++) {
        if (_fds[j].fd != 0){
          *(&_fds[i]) = _fds[j];
          memset(&_fds[j], 0, sizeof(_fds[0]));
        }
      }
    }
  }
}

void Server::closeConnection(struct pollfd *poll, int &actual_fds) {
  std::cout << "Closing conn " << poll->fd << "\n";
  _clFd.erase(poll->fd);
  if (close(poll->fd) == ERROR)
    std::cout << "Closing error: " << strerror(errno) << std::endl;
  memset(poll, 0, sizeof(_fds[0]));
  _itPoll--;
  size_t t = actual_fds;
  reorder_fds(t);
}

void  Server::start()
{
  memset(_fds, 0 , sizeof(_fds));

  for (size_t i = 0; i < serverBlocks.size(); i++)
  {
    _fds[i].fd = serverBlocks[i].start();
    _fds[i].events = POLLIN;
    _servers[serverBlocks[i].getSocket()] = serverBlocks[i];
  }

  int fd = 0, cl_fd;
  _itPoll = serverBlocks.size();
  while (1)
  {
    fd = poll(_fds, POLLSIZE, 1000);
    if (fd < 0)
      throw std::runtime_error("Poll failed");
    else if (fd == 0)
      continue;
    for (int i = 0; i < _itPoll; i++)
    {
      if(_fds[i].revents == 0)
        continue;
      if(_fds[i].revents != POLLIN)
      {
        closeConnection(&_fds[i], _itPoll);
        continue;
      }
      if (_servers.count(_fds[i].fd))
      {
        do
        {
          usleep(10000);
          cl_fd = newConnection(_fds[i].fd);
          if (cl_fd == -2) {
            std::cout << "Accept error" << std::endl;
            break;
          }
          if (cl_fd != ERROR) {
            _clFd[cl_fd] = _fds[i].fd;
            _fds[_itPoll].fd = cl_fd;
            _fds[_itPoll++].events = POLLIN;
            std::cout << "Accepted new conn " << cl_fd << "..." << std::endl;
          }
        } while (cl_fd > ERROR);
      }
      else {
        std::vector<char> buffer(MAX_SIZE);

        std::string raw_request;
        ssize_t bytesRead;
        do {
          bytesRead = recv(_fds[i].fd, &buffer[0], MAX_SIZE, 0);
          if (bytesRead == ERROR) {
            std::cout << "Recv error on " << _fds[i].fd << " I-> " << i << std::endl;
            // send error
            std::cout << strerror(errno) << std::endl;
            closeConnection(&_fds[i], _itPoll);
            break ;
          }
          else if (bytesRead > 0) {
            raw_request += std::string(&buffer[0], bytesRead);
          }
        } while (bytesRead == MAX_SIZE);
        if (bytesRead == ERROR) {
          std::cout << "Get error on " << _fds[i].fd << " I-> " << i << std::endl;
          continue;
        }
        RequestHandler req(_servers[_clFd[_fds[i].fd]], raw_request);
        if (_servers[_clFd[_fds[i].fd]]._responseCode != "500")
          _servers[_clFd[_fds[i].fd]]._responseCode = req.requestlineChecker();

        //  Send response
        std::string uploadLocation = "/_uploads/"; //don't remove slashes
        ResponseHandler ret(_servers[_clFd[_fds[i].fd]], uploadLocation);
        std::string response = ret.generateResponse(req);
        if (send(_fds[i].fd, response.c_str(), response.length(), 0) < 0) {
          std::cout << "Send error" << std::endl;
          closeConnection(&_fds[i], _itPoll);
          continue;
        }
      }
    }
  }
}

bool  Server::parseConfig(std::string &filename)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
    throw std::runtime_error("file cannot be opened.");
  
  int   nestingLevel = 0;
  bool  server = false;
  serverBlock current;
  std::string line;
  std::size_t position;
  bool  parseStatus;
  current._port = 0;
  while (std::getline(file, line))
  {
    // Remove leading and tailing whitespaces
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

    // Skip empty lines and comments
    if (line.empty() || line[0] == '#')
      continue;
    
    parseStatus = false;
    if (line.find("{") != std::string::npos)
      nestingLevel++;
    if (line.find("server {") != std::string::npos)
    {
      if (server)
        break;
      server = true;
      if (nestingLevel == 1)
        current = serverBlock();
    }
    else if (line.find("}") != std::string::npos)
    {
      nestingLevel--;
      if (!server)
        break;
      if (nestingLevel == 0)
      {
        server = false;
        if (current._port == 0 || current._root.empty()
          || current._errorPage.empty() || current._locations.empty())
          break;
        current._responseCode = "100";
        parseStatus = true;
        serverBlocks.push_back(current);
      }
    }
    else if (server)
    {
      if (line.find("server_name") != std::string::npos)
        current._serverName = substrBetweenChars(line, ' ', ';');
      else if (line.find("listen") != std::string::npos)
      {
        int temp;
        position = line.find_first_of(" ");
        temp = std::atoi(line.substr(position + 1).c_str());
        if (temp > 65535 || temp < 1)
          break;
        current._port = temp;
      }
      else if (line.find("root") != std::string::npos)
        current._root = substrBetweenChars(line, ' ', ';');
      else if (line.find("location") != std::string::npos)
      {
        server = true;
        if (!parseLocation(file, current, line))
          break;
        nestingLevel--;
      }
      else if (line.find("error_page") != std::string::npos)
      {
        std::string temp = substrBetweenChars(line, ' ', ';');
        std::size_t space = temp.find_first_of(" ");
        if (space != std::string::npos)
        {
          current._statusCode = temp.substr(0, space);
          current._errorPage = temp.substr(space + 1);
        }
      }
      else if (line.find("client_max_body_size") != std::string::npos)
        current._maxBodySize = std::strtoul(substrBetweenChars(line, ' ', ';').c_str(), NULL, 10);

      if (current._root[current._root.length() - 1] == '/')
        current._root = current._root.substr(0, current._root.length() - 1);
    }
  }
  file.close();
  return parseStatus;
}

std::string substrBetweenChars(const std::string &input, char left, char right)
{
  std::size_t start = input.find(left);
  std::size_t end = input.find(right);
  if (start == std::string::npos || end == std::string::npos)
    return "";
  return input.substr(start + 1, end - start - 1);
}

bool  Server::parseLocation(std::ifstream &file, serverBlock &current, std::string &line)
{
  int position = line.find_first_of(" ");
  std::string temp = line.substr(position + 1);
  locationBlock dir = locationBlock();
  std::size_t bracketPos = temp.find("{");
  if (bracketPos != std::string::npos)
    temp = temp.substr(0, bracketPos);
  temp.erase(temp.find_last_of(" "));
  current._locations[temp] = dir;
  current._locations[temp]._locationName = temp;
  current._locations[temp]._directoryListing = false;
  while (std::getline(file, line) && line.find("}") == std::string::npos)
  {
    // Remove leading and tailing whitespaces
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
    line.erase(line.find_last_not_of(";") + 1);

    // Skip empty lines and comments
    if (line.empty() || line[0] == '#')
      continue;
    position = line.find(' ');
    std::string option = line.substr(0, position);
    std::string value = line.substr(position + 1);
    if (option == "index")
      current._locations[temp]._index = value;
    else if (option == "allow_methods" || option == "limit_except")
      current._locations[temp]._allowedMethods = value;
    else if (option == "autoindex" && value == "on")
     current._locations[temp]._directoryListing = true;
  }
  if (current._locations[temp]._index.empty())
    return false;
  else if (current._locations[temp]._allowedMethods.empty())
   current._locations[temp]._allowedMethods = "GET POST DELETE";
  return true;
}
