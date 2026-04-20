#include "recursos.h"

Recursos::Recursos(): iteraciones(1), bytes(0) {

}

Recursos::Recursos(long iteraciones, long bytes){
    if(validacion(iteraciones, bytes)){
        this->iteraciones = iteraciones;
        this->bytes = byres;
    }else{
        this->iteraciones = 1;
        this->bytes = 0;
    }
}

