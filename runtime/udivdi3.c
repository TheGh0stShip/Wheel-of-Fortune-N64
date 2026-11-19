typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));
UDItype __udivmoddi4 ();
UDItype
__udivdi3 (n, d)
     UDItype n, d;
{
  return __udivmoddi4 (n, d, (UDItype *) 0);
}
