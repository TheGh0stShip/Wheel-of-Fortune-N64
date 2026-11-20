#include "wof.h"

char *func_80021908(s32 arg0) {
    char *buf;

    buf = func_8000B924(*D_80058228[arg0].size + 1);
    func_80006828(D_80058228[arg0].rom, buf, *D_80058228[arg0].size + 1);
    return buf;
}
