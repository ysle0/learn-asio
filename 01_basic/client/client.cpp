#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <exception>
#include <fmt/core.h>
#include <iostream>

using boost::asio::ip::tcp;
using namespace std;

// this program is accessing a daytime service, so we need the user to specify the server.
int main(int argc, char *argv[]) {
  fmt::println("Start Boost Asio Client!");
  try {
    // all programs that use boost::asio need to have at least one I/O execution context,
    // such as io_context object.
    boost::asio::io_context io_context;
    // We need to turn the server name that was specified as a parameter to the application,
    // into a TCP endpoint. To do this we use an ip::tcp::resolver object.
    tcp::resolver resolver(io_context);

    // A resolver takes a host name and service name and turns them into a list of endpoints.
    // We perform a resolve call using the name of the server, specified in argv[1], and the
    // name of the service, in this case "daytime".
    string ip = argv[1];
    string port;

    // 127.0.0.1:13
    tcp::resolver::results_type endpoints = resolver.resolve(ip, "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while (true) {
      boost::array<char, 128> buffer;
      boost::system::error_code err;

      const size_t len = socket.read_some(boost::asio::buffer(buffer), err);
      if (err == boost::asio::error::eof)
        break;
      else if (err)
        throw boost::system::system_error(err);

      cout.write(buffer.data(), len);

      sleep(1500);
    }
  } catch (exception &e) {
    fmt::println("Exception: {}", e.what());
  }

  fmt::println("End Boost Asio Client!");
  return 0;
}
