#include "fecha.h"

Fecha::Fecha(): dia(1), mes(1), anio(2000) {

}

Fecha::Fecha(int dia, int mes, int anio){
    if(validacion(dia, mes, anio)){
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }else{
        this->dia = 1;
        this->mes = 1;
        this->anio = 2000;
    }
}

int Fecha::getDia() const{
    return dia;
}

int Fecha::getMes() const{
    return mes;
}

int Fecha::getAnio() const{
    return anio;
}

bool Fecha::esBisiesto(int anio) const{
    if(anio % 400 == 0) return true;
    if(anio % 100 == 0) return false;
    return (anio % 4 == 0);
}

int Fecha::diasMes(int mes, int anio) const {
    switch (mes) {
    case 1: return 31;
    case 2: return esBisiesto(anio) ? 29 : 28;
    case 3: return 31;
    case 4: return 30;
    case 5: return 31;
    case 6: return 30;
    case 7: return 31;
    case 8: return 31;
    case 9: return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: return 0;
    }
}

bool Fecha::validacion(int dia, int mes, int anio) const{
    if(anio<0) return false;
    if (mes < 1 || (mes > 12)) return false;

    int maxDia = diasMes(mes, anio);
    if(dia < 1 || dia > maxDia) return false;

    return true;
}

int Fecha::convDias() const{
    int total = 2010;

    for(int a = 0; a < anio; a++){
        total += esBisiesto(a) ? 366:365;
    }
    for(int m = 1; m < mes; m++){
        total += diasMes(mes,anio);
    }
    total += dia;

    return total;
}

int Fecha::dias2026() const {
    int total = 0;

    for (int m = 1; m < mes; m++) {
        total += diasMes(m, 2026);
    }

    total += dia;
    return total;
}

int Fecha::diferencia(const Fecha& otra) const{
    if (anio == 2026 && otra.anio == 2026) {
        return dias2026() - otra.dias2026();
    }

    // Si quieres, aquí dejas una versión más general
    // para otros años.
    return 0;
}

Fecha Fecha::avanzar(int n) const{
    Fecha nueva = *this;

    for(int i = 0; i < n;i++){
        nueva.dia++;

        if(nueva.dia > nueva.diasMes(nueva.mes, nueva.anio)){
            nueva.dia = 1;
            nueva.mes++;

            if(nueva.mes > 12){
                nueva.mes = 1;
                nueva.anio++;
            }
        }
    }

    return nueva;

}

bool Fecha::operator ==(const Fecha& otra) const{
    return dia == otra.dia &&
           mes == otra.mes &&
           anio == otra.anio;
}

bool Fecha::operator <(const Fecha& otra) const{
    if(anio != otra.anio) return anio < otra.anio;
    if(mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

std::ostream& operator<<(std::ostream& os, const Fecha& f){
    os << f.dia << "/" << f.mes << "/" << f.anio;
    return os;
}













