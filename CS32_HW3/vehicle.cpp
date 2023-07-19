class Vehicle
{
    //pure virtual
    public:
        Vehicle(string id)
            :m_id(id)
        {}
        virtual ~Vehicle() {};
        virtual bool canHover() const {return true;} // it can be pure virtual but no two functions with non-empty bodies may have the same implementation
        virtual string description() const = 0; // pure virtual, since each class overrides.
        string id() const{return m_id;} // no class needs to override so leave it as non-virtual
    private:
        string m_id;
};

class Drone : public Vehicle
{
    public:
        Drone(string id)
            :Vehicle(id)
        {} // body is empty, so no problem
        virtual ~Drone() {cout << "Destroying "<< id() << ", a drone" << endl;}
        virtual string description() const { return "a drone";}
};

class Balloon : public Vehicle
{
    public:
        Balloon(string id, double diameter)
            :Vehicle(id), m_diameter(diameter)
        {}
        virtual ~Balloon(){cout << "Destroying the balloon " << id() << endl;}
        virtual string description() const { 
            if (m_diameter >= 8)
                return "a large balloon";
            else
                return "a small balloon";
        }
    private:
        double m_diameter;
};

class Satellite : public Vehicle
{
    public:
        Satellite(string id)
            :Vehicle(id)
        {} // body is empty, so no problem
        virtual ~Satellite() { cout << "Destroying the satellite " << id() << endl; }
        virtual bool canHover() const { return false;} // need to override, since default is true
        virtual string description() const { return "a satellite";}
};