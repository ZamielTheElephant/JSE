
class Resource
{
    private:
        std::string name;
        std::string type;
        int size;
        int value;
        int miningDifficulty;
    public:
        Resource() {};
        Resource(std::string, std::string, int, int, int);
        //Resource(Resource*)
        std::string getName() {return name;}
        std::string getType() {return type;}
        int getSize() {return size;}
        int getValue() {return value;}
        int getMiningDifficulty() {return miningDifficulty;}
};
