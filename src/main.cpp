#include <array>
#include <cstdlib>
#include <iostream>
#include <tracy/Tracy.hpp>
#include <unistd.h>

int main() {
  size_t N = 1024 * 1024;
  std::array<int *, 1000> pointers;
  {
    ZoneNamedN(a, "10 sekunder", true);
    sleep(10);
  }
  {
    ZoneNamedN(b, "3 sekunder", true);
    sleep(3);
    for (auto &pointer : pointers) {
      pointer = (int *)malloc(N * sizeof(int));
    }
  }

  {
    ZoneNamedN(c, "6 sekunder", true);
    for (auto &pointer : pointers) {
      for (size_t i = 0; i < N; ++i) {
        pointer[i] = 43.4 + i;
      }
    }
    sleep(6);
    for (auto &pointer : pointers) {
      free(pointer);
    }
  }

  std::cout << "Hei" << std::endl;
  return 0;
}
