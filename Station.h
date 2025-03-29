// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/10/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
   class Station {
      int m_id;
      std::string m_itemName;
      std::string m_description;
      unsigned m_serialNum;
      unsigned m_quantity;
      static size_t m_widthField;
      static int id_generator;
   public:
      Station(const std::string& s);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}

#endif // !SDDS_STATION_H
