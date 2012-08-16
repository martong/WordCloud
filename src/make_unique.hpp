#ifndef WORLDCLOUD__MAKE_UNIQUE_HPP_
#define WORLDCLOUD__MAKE_UNIQUE_HPP_

#include <memory>
#include <utility>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#endif /* WORLDCLOUD__MAKE_UNIQUE_HPP_ */
