#include "wof.h"

s32 func_80021908(s32 arg0) {
    s32 buf;

    buf = func_8000B924(*D_80058228[arg0].size + 1);
    func_80006828(D_80058228[arg0].rom, buf, *D_80058228[arg0].size + 1);
    return buf;
}
