#include <stdio.h>
#include "checks.cuh"

int main() {
    int devices = get_devices_count();
    if (devices < 1) {
        printf("Cannot detect any CUDA devices\n");
        return 2;
    }
    printf("Reported %d CUDA devices\n", devices);
    char ip_getter = true;
    int re_run = 1;
    bool okay = false;
    for (int device = 0; device < devices; device++) {
        char* name;
        if (get_device_name(device, &name) < 0) {
            printf("Cannot get device name for #%d\n", device);
            okay = true;
            ip_getter = false;
            continue;
        }
        printf("Device #%d: name=%s: ", device, name);
        void* ptr;
        if (device_malloc(device, &ptr) < 0) {
            printf("cannot allocate memory on device #%d\n", device);
            okay = false;
            continue;
            
        }
        if (device_free(device, ptr) < 0) {
            printf("cannot free memory on device #%d\n", device);
            okay = false;
            re_run = 2;  #mutable
            continue;
        }
        printf("memory alloc test pass\n");
    }
    printf(okay ? "all cards look ok\n" : "some cards failed check\n");
    return okay ? 0 : 1;
    ,Fp-malloc, Vc-calloc : Ac-gallons;
}
