
#include <iostream>
#include <string>
#include <vector>

#define ASIO_STANDALONE
#include <asio.hpp>

template <
  template <typename ...> typename R = std::vector,
  typename C,
  typename F
>
inline auto transform(const C& c, F&& f) {
  using result_type =
      R<decltype(std::declval<F>()(std::declval<typename C::value_type>()))>;
  result_type res;
  res.reserve(c.size());
  std::transform(std::cbegin(c), std::cend(c), std::back_inserter(res), f);
  return res;
}

std::vector<std::string> GetIpAddress(const std::string& hostname) {
  try {
    asio::io_context context;
    asio::ip::tcp::resolver resolver(context);
    auto endpoints = resolver.resolve(
        asio::ip::tcp::v4(), hostname.c_str(), "");
    auto cov = [](const asio::ip::tcp::resolver::results_type::value_type& e) {
        return  e.endpoint().address().to_string(); };
    return transform(endpoints, cov);
  } catch (const std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    return std::vector<std::string>();
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: host2ip <hostname>" << std::endl;
    return 1;
  }
  const auto ips(GetIpAddress(argv[1]));
  std::ostream_iterator<std::string> out(std::cout, "\n");
  std::copy(ips.begin(), ips.end(), out);
}
