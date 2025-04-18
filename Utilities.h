// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/10/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
   class Utilities {
      size_t m_widthField = 0;   //instance var
      static char m_delimiter;  //class var
   public:
      void setFieldWidth(size_t newWidth);
      size_t getFieldWidth() const;
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
      static void setDelimiter(char newDelimiter);
      static char getDelimiter();
   };
}
#endif // !SDDS_UTILITIES_H
