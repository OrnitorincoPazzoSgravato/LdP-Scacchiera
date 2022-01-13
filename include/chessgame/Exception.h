#ifndef EXCEPTION_H
#define EXCEPTION_H

class CoordinateOutOfRangeException : public std::exception
{
public:
    CoordinateOutOfRangeException(const char *msg) : std::exception(msg) {}
};

#endif // EXCEPTION_H
