#include "main.h"
#include <cstdint>
#include <cinttypes>
class cl {
  int i; // private by default
public:
  int get_i();
  void put_i(int j);
};

int cl::get_i()
{
  return i;
}

void cl::put_i(int j)
{
  i = j;
}


void operatorControl() {
	while (1) {
		delay(20);
    cl s;

    s.put_i(10);
		printf("Test-1-xx  %i\r",s.get_i());
	}
}
