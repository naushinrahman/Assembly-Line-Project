// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 12/2/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "LineManager.h"

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : m_activeLine(stations) {
      std::string line;
		size_t size = 0;

      std::ifstream File(file);
      if (!File) {
         throw "ERROR: File cannot be opened.";
      }
      else {
         while (std::getline(File, line)) {
            if (File) {
               m_activeLine.resize(size + 1);
               std::copy_if(stations.begin(), stations.end(), m_activeLine.begin() + size, [&](Workstation* w) -> bool {
                  bool ret = false;

					std::string station = line.substr(0, line.find('|'));
               if (w->getItemName() == station && line.find('|') != std::string::npos) {
						auto next = std::find_if(stations.begin(), stations.end(), [&](Workstation* w1) -> bool {
							std::string nextStation = line.substr(line.find('|') + 1);
                     return w1->getItemName() == nextStation;
                     });

                  w->setNextStation(*next);
                  ret = true;
               }
               else if (w->getItemName() == line) {
                  ret = true;
               }
               return ret;
               });
            }
            size++;
         }
         File.close();

			auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [this](const Workstation* w) {
				return !std::any_of(m_activeLine.begin(), m_activeLine.end(), [&w](const Workstation* w1) {
					if (w1->getNextStation() == nullptr) {
						return false;
					}
					else {
						return w->getItemName() == w1->getNextStation()->getItemName();
					}
				});
			});
         m_firstStation = *first;
         m_cntCustomerOrder = g_pending.size();
      }
	}

	void LineManager::reorderStations() {
		std::vector<Workstation*> tempOrders;
		Workstation* temp = m_firstStation;

		tempOrders.push_back(temp);

		while (temp->getNextStation()) {
			temp = temp->getNextStation();
			tempOrders.push_back(temp);
		}
		m_activeLine = tempOrders;
	}

	bool LineManager::run(std::ostream& os) {
		bool ret = false;
		static size_t i = 1;

		os << "Line Manager Iteration: " << i++ << std::endl;
		if (g_pending.size() > 0) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& workStation : m_activeLine) {
			workStation->fill(os);
		}
		for (auto& workStation : m_activeLine) {
			workStation->attemptToMoveOrder();
		}

		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
			ret = true;
		}

		return ret;
	}

	void LineManager::display(std::ostream& os) const {
		for (auto& workStation : m_activeLine) {
			workStation->display(os);
		}
	}
}