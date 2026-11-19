/* GCC 2.7.2 libgcc2.c (L_umoddi3). */
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));
UDItype func_800380D8 ();
UDItype
func_80038718 (u, v)
     UDItype u, v;
{
  UDItype w;

  (void) func_800380D8 (u, v, &w);

  return w;
}
