typedef signed int s32;
s32 func_8000B234(s32 arg0);
s32 func_8000B5DC(s32 arg0, s32 arg1);
s32 func_8000B670(s32 arg0, s32 arg1, s32 arg2);

void func_8000B6FC(s32 arg0, s32 arg1) {
    s32 node;

    node = func_8000B5DC(arg0, arg1);
    while (node != 0) {
        func_8000B234(node);
        node = func_8000B670(node, arg0, arg1);
    }
}
