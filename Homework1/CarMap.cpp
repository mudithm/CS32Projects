#include "CarMap.h"

// Constructor for the CarMap Object
CarMap::CarMap(){

}


// Adds car to map if possible
bool CarMap::addCar(std::string license){
  return m_map.insert(license, 0);
}

// Tells how much gas is present
double CarMap::gas(std::string license) const{
  double out = -1;
  m_map.get(license, out);
  return out;
}

// Adds gas to car if possible
bool CarMap::addGas(std::string license, double gallons){
  if( ! m_map.contains(license) || gallons < 0)
    return false;
  
  // updates gas value
  double temp = 0;
  m_map.get(license, temp);
  m_map.update(license, temp + gallons);
  return true;
}

// Uses gas if possible
bool CarMap::useGas(std::string license, double gallons){
  if( ! m_map.contains(license) || gallons < 0 || gallons > gas(license))
      return false;
    
    // updates gas value
    double temp;
    m_map.get(license, temp);
    m_map.update(license, temp - gallons);
    return true;
}

// Returns the number of cars
int CarMap::fleetSize() const{
  return m_map.size();
}

// Prints out the licenses and cars
void CarMap::print() const{
  std::string key;
  double value = 0;
  
  for (int i = 0; i < m_map.size(); i++){
    m_map.get(i, key, value);
    std::cout << key << " " << value << std::endl;
  }
}
