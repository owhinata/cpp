#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

using Money = int;

struct MacBookAirVendingMachine {
  Money invested;
};

MacBookAirVendingMachine InvestMoney(
        const MacBookAirVendingMachine& state,
        Money money) {
  return MacBookAirVendingMachine { state.invested + money };
}

std::tuple<Money, MacBookAirVendingMachine>
PayBack(const MacBookAirVendingMachine& state) {
  return std::make_tuple(state.invested, MacBookAirVendingMachine {});
}

std::tuple<std::string, MacBookAirVendingMachine>
Sell(const MacBookAirVendingMachine& state) {
  static constexpr Money Price = 120000;
  if (state.invested < Price) {
    return std::make_tuple("money shortage", state);
  }
  return std::make_tuple("MacBook Air 13-inch sold!",
    MacBookAirVendingMachine { state.invested - Price });
}

int main(int argc, char* argv[]) {
  Money invest = std::max(0, argc < 2 ? 0 : atoi(argv[1]));
  MacBookAirVendingMachine vm {};
  vm = InvestMoney(vm, invest);
  std::string res;
  std::tie(res, vm) = Sell(vm);
  std::cout << res << std::endl;
  Money payback;
  std::tie(payback, vm) = PayBack(vm);
  std::cout << "payback: " << payback << std::endl;
}
