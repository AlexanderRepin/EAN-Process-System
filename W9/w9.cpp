// Workshop 9 - Smart Pointers
 // w9.cpp

 #include <iostream>
 #include <string>
 #include <sstream>
 #include <iomanip>
 #include "Element.h"
 #include "List.h"

 const int FWC =  5;
 const int FWD = 12;
 const int FWP =  8;

 w9::List<w9::Product> merge(const w9::List<w9::Description>& desc, 
  const w9::List<w9::Price>& price) {
     w9::List<w9::Product> priceList;

		int p, d;
		for(p = 0; p < price.size(); p++)
		{
			for(d = 0;d < desc.size();d++)
			{
				if(price[p].code == desc[d].code)
				{
					if(price[p].price < 0)
					{
						std::stringstream ss;
						ss << "Negative Price " << price[p].price << " for " << price[p].code << " description " << desc[d].desc;
						throw ss.str();
					}
					priceList += new w9::Product(desc[d].desc, price[p].price);
					break;
				}
			}
			
			if(d >= desc.size())
			{
				std::stringstream ss;
				ss << "Incomplete Data: " << " description for price code " << price[p].code << " missing \n";
				throw ss.str();
			}
		
		}

    
     return priceList;
 }

 int main(int argc, char** argv) {
     std::cout << "\nCommand Line : ";
     for (int i = 1; i < argc; i++) {
	 //starts at 1 to skip intial argv
         std::cout << argv[i] << ' ';
     }
     std::cout << std::endl;
     if (argc != 3) {
         std::cerr << "\n***Incorrect number of arguments***\n";
         return 1;
     }

     try {
         w9::List<w9::Description> desc(argv[1]);
         std::cout << std::endl;
         std::cout << std::setw(FWC) << "Code" <<
          std::setw(FWD) << "Description" << std::endl;
         std::cout << desc << std::endl;
         w9::List<w9::Price> price(argv[2]);
         std::cout << std::endl;
         std::cout << std::setw(FWC) << "Code" <<
          std::setw(FWP) << "Price" << std::endl;
         std::cout << price << std::endl;
         w9::List<w9::Product> priceList = merge(desc, price);
         std::cout << std::endl;
         std::cout << std::setw(FWD) << "Description" <<
          std::setw(FWP) << "Price" << std::endl;
         std::cout << priceList << std::endl;
     }
     catch (const std::string& msg) {
         std::cerr << msg << std::endl;
     }
     catch (const char* msg) {
         std::cerr << msg << std::endl;
     }

     std::cout << "\nPress any key to continue ... ";
     std::cin.get();
}