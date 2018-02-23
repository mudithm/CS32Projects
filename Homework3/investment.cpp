///////////////////////
// Class Definitions //
///////////////////////

class Investment
{
    public:
        Investment(string name, int value);
        virtual ~Investment();
        string name() const;
        int purchasePrice() const;
        virtual bool fungible() const;
        virtual string description() const = 0;
    private:
        string m_name;
        int m_value;
};

class Painting : public Investment
{
    public:
        Painting(string name, int value);
        virtual ~Painting();
        virtual string description() const;
        
};

class Stock : public Investment
{
    public:
        Stock(string name, int value, string ticker);
        virtual ~Stock();
        virtual string description() const;
        virtual bool fungible() const;
    private:
        string m_ticker;   
};

class House : public Investment
{
    public:
        House(string name, int value);
        virtual ~House();
        virtual string description() const;
};

/////////////////////////////////////
// Member Function Implementations //
/////////////////////////////////////

///////////////////////////
//Investment

Investment::Investment(string name, int value) : m_name(name), m_value(value) 
{}

Investment::~Investment()
{}

string Investment::name() const
{
    return m_name;
}

int Investment::purchasePrice() const
{
    return m_value;
}

bool Investment::fungible() const
{
    return false;
}

////////////////////////////
//Painting

Painting::Painting(string name, int value) : Investment(name, value)
{}

Painting::~Painting()
{
    cout << "Destroying " << name() << ", a painting" << endl;
}

string Painting::description() const
{
    return "painting";
}

////////////////////////////
//Stock

Stock::Stock(string name, int value, string ticker) : Investment(name, value), m_ticker(ticker)
{}

Stock::~Stock()
{
    cout << "Destroying " << name() << ", a stock holding" << endl;
}

bool Stock::fungible() const
{
    return true;
}

string Stock::description() const
{
    return "stock trading as " + m_ticker;
}

////////////////////////////
//House

House::House(string name, int value) : Investment(name, value)
{}

House::~House()
{
    cout << "Destroying the house " << name() << endl;
}

string House::description() const
{
    return "house";
}


////////////////////////////
// end of implementations //
////////////////////////////

