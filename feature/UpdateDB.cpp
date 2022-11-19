#include "../Beyond.h"

template <typename T>
bool CJob::CSubJob::updateDB (int _count, T ...){
    va_list list;
    va_list copy;

    va_start (list, _count);

    for (int i = 0; i < _count; i++){
        std::cout <<va_arg (copy, T) << " ";
    }

    va_end(list);
    va_end(copy);
    return true;
}