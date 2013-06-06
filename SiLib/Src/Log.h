#ifndef Log_h_already_included__08_06_2012__37A1E940
#define Log_h_already_included__08_06_2012__37A1E940
//
// SeVlaT, 08.06.2012
//

#define DEBUG_LOG_FILE_ENV_VAR "SILIB_LOG_FILE"
#define DEBUG_LOG_FILE_NAME    "SiLib.log"

#include <DebugUtils/Log.h>

class TNullLogger {
 public:
  TNullLogger(const char*) {}
};

//  typedef TNullLogger TLogger;
  typedef TBlockLogger TLogger;


#endif
