//--------------------------------------------
// Thought behind coding
// Idea is to provide heirachy for vehicle types
// containers can be list or multiindex , chose list for simplicity
// Filter class should be generic to filter any vehicle

// Did run out of time
//--------------------------------------------

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>


// IVehicle interface
class IVehicle
{
    protected:
        std::string m_license_plate;
        std::string m_brand;
        int m_capacity = 0;
        bool m_available_to_rent = true;
    public :
        IVehicle(const std::string& license_plate, const std::string& brand, int capacity) :
            m_license_plate(license_plate),
            m_brand(brand),
            m_capacity(capacity)
        {
        }
        virtual int getCapacity() = 0;
        const std::string& getBrand() const { return m_brand; } 
        const bool isAvailableToRent() const { return m_available_to_rent; }
        virtual ~IVehicle() {}
};

class SUV : public IVehicle
{
    private:
        bool m_has_third_row_seat = false;
    public:
        SUV(const std::string& license_plate, const std::string& brand, int capacity, bool has_third_row_seat) :
            IVehicle(license_plate, brand, capacity),
            m_has_third_row_seat(has_third_row_seat)
        {
        }

        virtual int getCapacity()
        {
            return m_has_third_row_seat ? m_capacity + 3 : m_capacity;
        }

        bool hasThirdRow() { return m_has_third_row_seat; }
};

class Sedan : public IVehicle
{
    private:
        bool m_has_sports_package = false;
    public :
        Sedan(const std::string& license_plate, const std::string& brand, int capacity, bool has_sports_package) :
            IVehicle(license_plate, brand, capacity),
            m_has_sports_package(has_sports_package)
        {
        }

        virtual int getCapacity()
        {
            return m_capacity;
        }
};

enum class VehicleType
{
    Sedan = 0,
    SUV = 1,
    Any = 2
};

struct Filter
{
    VehicleType m_type = VehicleType::Sedan;    
    int m_min_capacity = 0;
    bool m_with_third_row_seat = false;
    bool m_with_sport_package = false;
    std::string m_matching_brand;
    bool m_available_to_rent = true;

    Filter(const VehicleType& type, const int min_capacity , const bool with_third_row_seat, const bool with_sport_package, 
            const std::string& matching_brand, bool available_to_rent) :
            m_type(type),
            m_min_capacity(min_capacity),
            m_with_third_row_seat(with_third_row_seat),
            m_with_sport_package(with_sport_package),
            m_matching_brand(matching_brand),
            m_available_to_rent(available_to_rent)
            {

            }
};

class CarRental
{
    private:
        std::list<std::shared_ptr<IVehicle>> m_inventory;
        // boost::multi_index<....>   

        std::shared_ptr<IVehicle> findCar(const Filter& filter)
        {
            for (const auto& car : m_inventory)
            {
                if (car->getCapacity() > filter.m_min_capacity &&
                    (filter.m_type == VehicleType::Any || car->getBrand() == filter.m_matching_brand) &&
                    car->isAvailableToRent() == filter.m_available_to_rent)
                {
                    if (filter.m_type == VehicleType::Sedan)
                    {
                        auto sedan = dynamic_cast<Sedan*>(car.get());     
                        if (sedan->getBrand() == filter.m_matching_brand)
                        {
                            return car;
                        }
                    }   
                    else
                    {
                        auto suv = dynamic_cast<SUV*>(car.get()); 
                        if (suv->hasThirdRow() == filter.m_with_third_row_seat)
                            return car;
                    }
                }
            }
            return nullptr;
        }
        std::list<std::shared_ptr<IVehicle>> findCars(const Filter& filter);
    
    public:
        auto addSUV(const std::string& license_plate, const std::string& brand, int capacity, bool has_third_row_seat)
        {
            auto suv = std::make_shared<SUV>(license_plate,brand,capacity,has_third_row_seat);
            m_inventory.emplace_back(suv);
            return suv;
        }

        auto addSedan(const std::string& license_plate, const std::string& brand, int capacity, bool m_has_sports_package)
        {
            auto sedan = std::make_shared<Sedan>(license_plate,brand,capacity,m_has_sports_package);
            m_inventory.emplace_back(sedan);
            return sedan;
        }
        
        std::shared_ptr<IVehicle> getSUVCar(const std::string& license_plate, const std::string& brand, int capacity, bool has_third_row_seat)
        {
            Filter f(VehicleType::SUV, capacity,has_third_row_seat,false,brand,true); 
            return findCar(f);
        }
        
        std::shared_ptr<IVehicle> getSedanCar(const std::string& license_plate, const std::string& brand, int capacity, bool has_third_row_seat)
        {
            Filter f(VehicleType::Sedan, capacity,has_third_row_seat,false,brand,true); 
            return findCar(f);
        }

        //void markRentedOut(std::string& license_plate);
        //void markAvailableToRent(std::string& );
        //std::list<std::shared_ptr<IVehicle>>& getAllInventory();
        //std::list<std::shared_ptr<IVehicle>>& getAllAvailableInventory();
        //std::list<std::shared_ptr<IVehicle>>& getAllRentedInventory();
        //std::list<std::shared_ptr<IVehicle>>& getAllSedans();
        //std::list<std::shared_ptr<IVehicle>>& getAllSedansWithCapacity(int min_capacity);
        //std::list<std::shared_ptr<IVehicle>>& getAllSedansWithCapacityAndBrand(int min_capacity, const std::string& brand);
        //std::list<std::shared_ptr<IVehicle>>& getAllSedansWithCapacityAndWithSportsPackage(int min_capacity);
        //std::list<std::shared_ptr<IVehicle>>& getAllSedansWithCapacityAndBrandWithSportsPackage(int min_capacity,const std::string& brand);
        
        

};

int main()
{
    CarRental rental;
    auto car = rental.addSedan("LICENCE_PLT1", "toyota", 5, false);
    assert(car->getCapacity() == 5);

    auto suv = rental.addSUV("LICENCE_PLT2", "toyota",5,true);
    assert(suv->getCapacity() == 8 );

    
    auto bigger_suv = rental.addSUV("LICENCE_PLT2", "toyota",5,false);
    assert(bigger_suv->getCapacity() == 5);

    return 0;
}



