#include <iostream>

using namespace std;

class Flight {
	private:
		int m_flight_no;
		string m_dest;
		float m_distance;
		float m_fuel;
		
	public:
		void set_fuel() {
			m_fuel = 13.2;
		}
		 
		void calculate_fuel() {
			if (m_distance <= 1000) {
				m_fuel = 500;
			} else if (m_distance > 1000 && m_distance <= 2000) {
				m_fuel = 1100;
			} else if (m_distance > 2000) {
				m_fuel = 2200;
			}
		}
		
		void display_info() {
			cout << "The flight number is: " << m_flight_no << "\nthe destination is:  "<< m_dest << "\nthe distance is " << m_distance << "\n the fuel required is " << m_fuel<<" liters"<<endl;
		}
		
		void information_entry(int flight_no, string dest, float distance) {
			m_flight_no = flight_no;
			m_dest = dest;
			m_distance = distance;
			
			calculate_fuel();
			display_info();
		}
};

int main() {
	int flight_no;
	string dest;
	float distance;
	
	Flight flight;
	flight.set_fuel();
	
	cout << "Enter flight number\n";
	cin >> flight_no;
	
	cout << "Enter destination\n";
	cin >> dest;
	
	cout << "Enter distance\n";
	cin >> distance;
	
	flight.information_entry(flight_no, dest, distance);
	
	return 0;
}

