#include <iostream>
#include "fecha.h"

using namespace std;

int main()
{
    Fecha a(12,3,2026);
    Fecha b(22,3,2026);

    cout<<a.diferencia(b)<<endl;
    return 0;
}
