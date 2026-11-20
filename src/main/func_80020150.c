#include "wof.h"
#include "mpeg/proto.h"

void func_80020150(obj_t *obj, frame_t *frame) {
    if (D_800BCD54 == 6) {
        return;
    }
    switch (D_800B96A4) {
    case 0:
        switch (D_80107884->h_size) {
        case 112:
            func_8001EFF0(obj, frame);
            return;
        case 96:
            func_8001DAF0(obj, frame);
            return;
        case 64:
            func_8001D440(obj, frame);
            return;
        }
        func_80009D78(D_80107884->h_size);
        func_80009F98("x");
        func_80009D78(D_80107884->v_size);
        func_80009F98(" ");
        func_80009F38("Size Video Not Supported");
    }
}
