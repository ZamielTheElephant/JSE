
class Resource
{
    private:
        std::string name;
        std::string type;
        int size;
        int value;
        int minValue;
        int miningDifficulty;
    public:
        Resource() {};
        Resource(std::string, std::string, int, int, int, int);
        //Resource(Resource*)
        std::string getName() {return name;}
        std::string getType() {return type;}
        int getSize() {return size;}
        int getValue() {return value;}
        int getMinValue() {return minValue;}
        int getMiningDifficulty() {return miningDifficulty;}
};
