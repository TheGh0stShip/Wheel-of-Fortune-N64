typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));
UDItype __udivmoddi4 ();
UDItype
__umoddi3 (u, v)
     UDItype u, v;
{
  UDItype w;

  (void) __udivmoddi4 (u, v, &w);

  return w;
}
