#include <iostream>
#include <stdexcept>
#include <string>

using Money = int;

struct MoneyShortage : public std::runtime_error {
  MoneyShortage() : std::runtime_error("money shortage") {}
};

class MacBookAirVendingMachine {
  static constexpr Money Price = 120000;
  Money invested_money_ = 0;

 public:
  void InvestMoney(Money money) {
    invested_money_ += money;
  }

  Money PayBack() {
    const Money ret = invested_money_;
    invested_money_ = 0;
    return ret;
  }

  std::string Sell() {
    if (invested_money_ < Price) {
      throw MoneyShortage();
    }
    invested_money_ -= Price;
    return "MacBook Air 13-inch sold!";
  }
};

constexpr Money MacBookAirVendingMachine::Price;

int main(int argc, char* argv[]) {
  Money invest = std::max(0, argc < 2 ? 0 : atoi(argv[1]));
  try {
    MacBookAirVendingMachine vm;
    vm.InvestMoney(invest);
    std::cout << vm.Sell() << std::endl;
    std::cout << "payback: " << vm.PayBack() << std::endl;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
