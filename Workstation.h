// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 12/2/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>

namespace sdds {
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;

   class Workstation : public Station{
      std::deque<CustomerOrder> m_orders; //enter from the back exit from front, push.back vs pop.front
      Workstation* m_pNextStation;
   public:
      Workstation(const std::string& name);
      Workstation(const Workstation&) = delete;
      Workstation& operator=(const Workstation&) = delete;
      Workstation(Workstation&&) = delete;
      Workstation& operator=(Workstation&&) = delete;
      ~Workstation();
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
  };
}
#endif // !SDDS_WORKSTATION_H
