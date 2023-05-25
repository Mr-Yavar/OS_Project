class Process {
public:
    int name;
    float entranceTime, processTime, exit, initialProcessTime;

    Process(int name, float entranceTime, float processTime) {
        this->name = name;
        this->processTime = processTime;
        this->initialProcessTime = processTime;
        this->entranceTime = entranceTime;
    }

    Process() {

    }
};