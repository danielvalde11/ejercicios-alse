#include <iostream>
#include <cmath>
int main(){
    std::cout<<"Ingresa la cantiddad de dinero"; << std::endl;
    int dinero;
    std::cin>>dinero;
    std::cout<<"Ingresa la tasa de interes" << std::endl;
    float tasa;
    std::cin>>tasa;
    std::cout<<"Ingresa el numero de años" << std::endl;
    int años;
    std::cin>>años;
    std::cout << "El capital final es: " << dinero * pow(1 + tasa, años);
    return 0;
}
