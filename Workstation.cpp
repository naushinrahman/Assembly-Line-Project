// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 12/2/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

namespace sdds {

   std::deque<CustomerOrder> g_pending;
   std::deque<CustomerOrder> g_completed;
   std::deque<CustomerOrder> g_incomplete;

   Workstation::Workstation(const std::string& name) : Station(name) { 
      m_pNextStation = nullptr;
   }

   void Workstation::fill(std::ostream& os) {
      if (!m_orders.empty()) {
         m_orders.front().fillItem(*this, os);
      }
   }

   bool Workstation::attemptToMoveOrder() {
      bool ret = false;

      if (!m_orders.empty()) {
         if (getQuantity() == 0|| m_orders.front().isItemFilled(getItemName())) {
            if (m_pNextStation) {
               *m_pNextStation += std::move(m_orders.front());
            }
            else {
               if (m_orders.front().isOrderFilled()) {
                  g_completed.push_back(std::move(m_orders.front()));
               }
               else {
                  g_incomplete.push_back(std::move(m_orders.front()));
               }
            }
            m_orders.pop_front();
            ret = true;
         }
      }
      return ret;
   }

   void Workstation::setNextStation(Workstation* station) {
      m_pNextStation = station;
   }

   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }

   void Workstation::display(std::ostream& os) const {
      if (m_pNextStation) {
         os << getItemName() << " --> " << m_pNextStation->getItemName() << '\n';
      }
      else {
         os << getItemName() << " --> End of Line\n";
      }

   }

   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
      m_orders.push_back(std::move(newOrder));
      return *this;
   }

   Workstation::~Workstation() {

   }
}