# WealthDesk Assignment
 Assignment for hiring process.

Title - Parking Lot System

Contents:-

- Use-Case Diagram
- LLD Design
- HLD approches (beta)

How to Run:-

- Run parkingLot.cpp (in Linux Terminal type "g++ -std=c++11 parkingLot.cpp")
- Create a parking lot before doing any other operation. (Option 1 in the menu)
- Other operations are assisted in CLI.


######################################################################################################

Known Bugs/Missings:-

- There is no class for Parking Slots. So app doesn't realises whether it freed a bike space or car space.
- No setters/getters used due to lack of time.
- For sake of simplicity, only hourly basis of rates are described in rateChart.
- Admins can only access one parking lot at a time.
- No errors/exception handling methods applied.
- No authentication added. User class is not getting completely used.
- User Info not getting saved.
- Had to merge guard and admin users to avoid complications in some methods.
- getHistory not working.
- time objects are not handled properly. Thus TotalAmount is storing garbage value. 