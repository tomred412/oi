#include <cstdio>
using namespace std;

int main() {
  const char* s =
      "#include <cstdio>\nusing namespace std;\n\nint main() {\n  const char* "
      "s =\n    %c%s%c;\n  "
      "std::printf(s, 34, s, 34);\n  return 0;\n}\n";
  printf(s, 34, s, 34);
  return 0;
}
