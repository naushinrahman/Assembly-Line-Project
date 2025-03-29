// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/10/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

   size_t Station::m_widthField = 0;
   int Station::id_generator = 0;

   Station::Station(const std::string& s) {
      Utilities module;
      bool keepGoing;
      size_t pos = 0;
      std::string extracted = module.extractToken(s, pos, keepGoing);
      m_itemName = extracted;

      extracted = module.extractToken(s, pos, keepGoing);
      m_serialNum = std::stoi(extracted);

      extracted = module.extractToken(s, pos, keepGoing);
      m_quantity = std::stoi(extracted);

      if (module.getFieldWidth() > m_widthField) {
         m_widthField = module.getFieldWidth();
      }

      extracted = module.extractToken(s, pos, keepGoing);
      m_description = extracted;

      m_id = ++id_generator;
   }

   const std::string& Station::getItemName() const {
      return m_itemName;
   }

   size_t Station::getNextSerialNumber() {
      return m_serialNum++;
   }

   size_t Station::getQuantity() const {
      return m_quantity;
   }

   void Station::updateQuantity() {
      if (m_quantity > 0) {
         --m_quantity;
      }
   }

   void Station::display(std::ostream& os, bool full) const {
      os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setfill(' ');
      os << std::setw(m_widthField) << std::left << m_itemName << " | ";
      os << std::setw(6) << std::right << std::setfill('0') << m_serialNum << " | ";
      os << std::setfill(' ');

      if (full) {
         os << std::setw(4) << std::right << m_quantity << " | ";
         os << std::setw(0) << std::left << m_description;
      }

      os << std::endl;
   }

}