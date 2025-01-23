#include <exception>
#define _CRT_SECURE_NO_WARNINGS
#include <boost/asio.hpp>
#include <ctime>
#include <fmt/core.h>
#include <string>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
  time_t now = time(0);
  return ctime(&now);
}

int main() {
  fmt::println("Start Boost Asio Server!");

  try {
    boost::asio::io_context io_context;
    const int port = 13;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

    while (true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      string msg = make_daytime_string();
      auto msg_buffer = boost::asio::buffer(msg);

      boost::system::error_code ignored_error;
      boost::asio::write(socket, msg_buffer, ignored_error);
    }

  } catch (exception &e) {
    fmt::println(e.what());
  }

  fmt::println("End Boost Asio Server!");

  return 0;
}