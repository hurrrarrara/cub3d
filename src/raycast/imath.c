
#include <stdint.h>

 int16_t ft_i16max(int16_t a, int16_t b)
{
	return (a * (a >= b) + b * (a < b));
}

 int16_t	ft_i16min(int16_t a, int16_t b)
{
	return (a * (a <= b) + b * (a > b));
}

 int32_t ft_i32max(int32_t a, int32_t b)
{
	return (a * (a >= b) + b * (a < b));
}

 int32_t	ft_i32min(int32_t a, int32_t b)
{
	return (a * (a <= b) + b * (a > b));
}