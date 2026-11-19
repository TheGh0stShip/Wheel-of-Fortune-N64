typedef signed int s32;
s32 func_800A4AD8(s32 arg0); /* its definition returns void; the result is used here */

s32 func_800A38F8(s32 arg0) {
restart:
    switch (func_800A4AD8(arg0)) {
    case 0:
        goto second;
    case -1:
        goto fail;
    default:
        goto restart;
    }
second:
    switch (func_800A4AD8(arg0)) {
    case 0:
        goto wait;
    case -1:
        goto fail;
    default:
        goto restart;
    }
wait:
    switch (func_800A4AD8(arg0)) {
    case 1:
        goto done;
    case 0:
        goto wait;
    case -1:
        goto fail;
    default:
        goto restart;
    }
done:
    return func_800A4AD8(arg0) + 256;
fail:
    return -1;
}
