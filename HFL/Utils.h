#ifndef Utils_h_already_included__05_04_2012__2DB26A00
#define Utils_h_already_included__05_04_2012__2DB26A00
//
// SeVlaT, 05.04.2012
//

std::string GenerateFileName(const std::string &sPrefix,
                             const std::string &sPostfix,
                             const std::string &sExtension,
                                   bool         bDate,
                                   bool         bTime);
                                   
std::string  W2A(const std::wstring &ws);
std::wstring A2W(const std::string  &as);

#endif
