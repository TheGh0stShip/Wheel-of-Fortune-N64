typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;
void func_80009F98(s32 arg0);

void func_80009D78(s32 arg0) {
    s8 buf[20];
    s32 i;
    s32 divisor;
    s32 digit;
    s32 value;

    value = arg0;
    if (value < 0) {
        value = value * -1;
    }
    buf[19] = 0;
    i = 18;
    for (divisor = 10; divisor <= 999999999; divisor = divisor * 10) {
        digit = value % divisor;
        value = value - digit;
        digit = digit / (divisor / 10);
        buf[i--] = (u8)digit + '0';
        if (value == 0) {
            break;
        }
    }
    if (arg0 < 0) {
        buf[i--] = '-';
    }
    func_80009F98((s32)&buf[i + 1]);
}
