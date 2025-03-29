// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/10/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

namespace sdds {
   char Utilities::m_delimiter = ',';

   void Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      if (str[next_pos] == m_delimiter) {
         ++next_pos;
         more = false;
         throw "error";

      }

      std::string untrimmedToken, token;
      const size_t nextPos = next_pos;
      size_t tokenPos = str.find(m_delimiter, nextPos);

      if (tokenPos != std::string::npos) {
         size_t temp = tokenPos - nextPos;
         untrimmedToken = str.substr(nextPos, temp);
         size_t last = untrimmedToken.find_last_not_of(' ') + 1;
         token = untrimmedToken.substr(untrimmedToken.find_first_not_of(' '), (last - untrimmedToken.find_first_not_of(' ')));
         
         next_pos = ++tokenPos;
         more = true;
      } 
      else {
         untrimmedToken = str.substr(nextPos);
         size_t last = untrimmedToken.find_last_not_of(' ') + 1;
         token = untrimmedToken.substr(untrimmedToken.find_first_not_of(' '), (last - untrimmedToken.find_first_not_of(' ')));
         more = false;
         next_pos = std::string::npos;
      }

      if (m_widthField < token.length()) {
         m_widthField = token.length();
      }
      return token;
   }

   void Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter() {
      return m_delimiter;
   }
}