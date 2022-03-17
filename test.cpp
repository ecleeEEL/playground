#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>

typedef void (*f_int_t) (int); 


void testme (int v) {
	std::cout << "me " << v << std::endl;
}

class plustwo {
    public:
        plustwo(){};

        void operator()(int &i) {i+=2;};
};

class VectorIntWrapper {
    private:
        std::vector<int> array;
    public:
        VectorIntWrapper(const std::vector<int> vi): array{vi} {};
        const std::vector<int>  &getArray()  const {return (array);};
	VectorIntWrapper(const VectorIntWrapper&) = default;
	VectorIntWrapper(VectorIntWrapper && other ): array(std::move(other.array)) {
	    std::cout << "In move constrcutor" << std::endl;
	};
	void PushInt(const int value) {array.push_back(value);};
	// Move assignment operator.
	VectorIntWrapper& operator=(VectorIntWrapper&& other) {
	    array = std::move(other.array);
	    std::cout << "In operator=(MemoryBlock&&)" << std::endl;
	    //array = std::move(other.array);
	    return *this;
	};
};

VectorIntWrapper operator+(const VectorIntWrapper & left, const VectorIntWrapper &right) {
    VectorIntWrapper result {{}};
    auto itleft = left.getArray().cbegin();
    auto itright = right.getArray().cbegin();
    if (left.getArray().size() && (left.getArray().size() == right.getArray().size())) {
        while (itleft != left.getArray().end()) {
            result.PushInt(*itleft + *itright);
            itleft++;
            itright++;
        }
    }
    return result;
}


int main () {

    std::vector<int> vi = {1,2,3,4,5,6,7};
    VectorIntWrapper testrapper1{vi};
    std::cout << "testrapper1" << std::endl;
    for (auto x: testrapper1.getArray()) {
        std::cout << x << " ";
    }
    std::cout << std::endl; 
    
    for_each(vi.begin(), vi.end(), plustwo{});
    /*std::cout << "testrapper2"  << std::endl;
    for (auto x: testrapper2.getArray()) {
        std::cout << x << " ";
    }*/
    std::cout << std::endl; 
    VectorIntWrapper testrapper2{vi};
    std::cout << "testrapper2"  << std::endl;
    for (auto x: testrapper2.getArray()) {
        std::cout << x << " ";
    }
    std::cout << std::endl; 
    VectorIntWrapper sum{{(int) vi.size()}};
 
    sum= testrapper1 + testrapper2;
    std::cout << "sum"  << std::endl;
    for (auto x: sum.getArray()) {
        std::cout << x << " ";
    }
    std::cout << std::endl; 

    auto sumcopy(std::move(sum));
    std::cout << "sum"  << std::endl;
    for (auto x: sum.getArray()) {
        std::cout << x << " ";
    }
    std::cout << std::endl; 

    std::cout << "sumcopy"  << std::endl;
    for (auto x: sumcopy.getArray()) {
        std::cout << x << " ";
    }
    std::cout << std::endl; 
    
    std::unordered_map<std::string, f_int_t> fnmap{};

    fnmap.insert({"eric", &testme});

    fnmap.insert({"bill", &testme});

    for (auto entry: fnmap) {
        std::cout << entry.first << ": " << std::endl;
        entry.second(5);
    }


        
    return 0;
}
