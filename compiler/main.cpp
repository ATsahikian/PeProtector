#include <algorithm>
#include <fstream>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>
#include "../common/SCommand.h"
#include "../common/Types.h"
#include "../log/CLog.h"
#include "CCompile.h"
#include "CLexicalAnalizer.h"

using std::cout;
using std::exception;
using std::ifstream;
using std::ios_base;
using std::istream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

/**
 * @brief Compile.exe file.asm file.bin
 */
int main(int argc, char* argv[], char* env[]) {
  int exitCode = 0;
  if (argc == 3) {
    LOG_INITIALIZE(string(argv[0]) + ".log");
    try {
      ifstream file(argv[1]);
      if (file.is_open()) {
        const vector<NPeProtector::SCommand>& commands =
            NPeProtector::compile(file);

        ofstream binFile(argv[2], ios_base::binary);

        NPeProtector::serialize(binFile, commands);
      } else {
        exitCode = 1;
        printf("error: can't open file %s", argv[1]);
      }
    } catch (const exception& e) {
      cout << e.what();
    }
  } else {
    printf("Compile.exe file.asm file.bin");
  }

  return exitCode;
}