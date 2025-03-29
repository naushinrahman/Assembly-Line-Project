// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/21/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities module;
		bool keepGoing;
		size_t pos = 0;

		std::string extracted = module.extractToken(str, pos, keepGoing);
		m_name = extracted;

		extracted = module.extractToken(str, pos, keepGoing);
		m_product = extracted;

		while (pos != std::string::npos) {
			Item** temp = new Item * [m_cntItem + 1];
			extracted = module.extractToken(str, pos, keepGoing);

			for (size_t i = 0; i < m_cntItem; i++) {
				temp[i] = *&m_lstItem[i];
			}
			temp[m_cntItem] = new Item(extracted);
			delete[] m_lstItem;
			m_lstItem = temp;
			m_cntItem++;
		}

		if (module.getFieldWidth() > m_widthField) {
			m_widthField = module.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		std::string errMessage = "error";
		throw errMessage;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& CustOr) noexcept {
		*this = std::move(CustOr);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& CustOr) noexcept {
		if (this != &CustOr) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}

			m_cntItem = CustOr.m_cntItem;
			m_name = CustOr.m_name;
			m_product = CustOr.m_product;
			m_widthField = CustOr.m_widthField;

			delete[] m_lstItem;
			m_lstItem = CustOr.m_lstItem;
			CustOr.m_lstItem = nullptr;
			CustOr.m_cntItem = 0;
			CustOr.m_name = "";
			CustOr.m_product = "";
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem != nullptr) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
	}

	bool CustomerOrder::isOrderFilled() const {
		bool allFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				allFilled = false;
			}
		}
		return allFilled;

	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool allFilled = true;
		//If the item doesn't exist in the order, this query returns true.
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					allFilled = false;
				}
			}
		}
		return allFilled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool allFilled = false;
		for (size_t i = 0; i < m_cntItem && !allFilled; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (!m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {
					allFilled = true;
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]";
				}
				else if (station.getQuantity() == 0) {
					os << "    Unable to fill " << m_name << ", " << m_product;
					os << " [" << m_lstItem[i]->m_itemName << "]";
				}
				os << '\n';
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << '\n';
		}
		os << '\n';
	}

}
