#include<string>
#include <cmath>
namespace lasd {

template<>
class Hash<int>{
    public:
    ulong operator()(const int& dato) const noexcept{
        return (dato * dato);
    }
};

template<>
class Hash<double>{
    public:
    ulong operator()(const double& dato) const noexcept{
        long intpart = std::floor(dato);
        long fract = pow(2,24) * (dato - intpart);
        return (intpart * fract);
    }
};

template<>
class Hash<std::string>{
    public:
    ulong operator()(const std::string& dato) const noexcept{
        ulong sum = 0;
        for(ulong i = 0; i < dato.length(); i++)
            sum += dato[i];
        return sum;
    }
};

template<typename Data>
int HashTable<Data>::generateRandom(int min, int max){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(min, max);

      return dist(gen);
}

template<typename Data>
HashTable<Data>::HashTable(){
    //scelta valori a : da 1 a p - b : da 0 a p
    a = generateRandom(1, p);
    b = generateRandom(0, p);   

}

template<typename Data>
ulong HashTable<Data>::HashKey(const Data& dato) const{
    return HashKey(hash.operator()(dato));
}

template<typename Data>
ulong HashTable<Data>::HashKey(const ulong& k) const{
    return ((a*k + b) % p) % tableSize;
}

}
