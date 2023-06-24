#include <Server.hpp>
#include <Response.hpp>

int main(int ac, char **av) {
  if (ac != 2 && ac != 1)
    std::cout << "Incorrect amount of arguments.\n";
  else {
    std::string config;
    if (ac == 1)
      config = "./config/nginx.conf";
    else
      config = av[1];
    try
    {
      Server servers(config);
      servers.start();
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
}
