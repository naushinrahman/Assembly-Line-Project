// Name: Naushin Rahman
// Seneca Student ID: 144079225
// Seneca email: nrahman30@myseneca.ca
// Date of completion: 11/21/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include "Station.h"

namespace sdds {
   class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		static size_t m_widthField;
		std::string m_name = "";
		std::string m_product = "";
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;

	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);

		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;

		CustomerOrder(CustomerOrder&& CustOr) noexcept;
		CustomerOrder& operator=(CustomerOrder&& CustOr) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
   };
}

#endif // !1
