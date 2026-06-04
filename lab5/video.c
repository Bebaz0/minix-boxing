#include <lcom/lcf.h>
#include "video.h"
#include "vbe.h"

static char *video_mem;
static char *back_buffer;
static vbe_mode_info_t vmi;
static unsigned bytes_per_pixel;
static unsigned vram_base;
static unsigned vram_size;

#include <lcom/lcf.h>
#include "video.h"
#include "vbe.h"

void *(vg_init)(uint16_t mode) {

    if (vbe_get_mode_info(mode, &vmi) != OK) {
        panic("%hu: vbe_get_mode_info(0x03X) failed\n",mode);
        return NULL;
    }

    if (video_set_mode(mode) != 0) {
        panic("vg_init(): video_set_mode failed\n");
        return NULL;
    }

    bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
    vram_base = vmi.PhysBasePtr;
    vram_size = vmi.XResolution * vmi.YResolution * bytes_per_pixel;

    int r;
    struct minix_mem_range mr;
    mr.mr_base = (phys_bytes) vmi.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;
    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
        return NULL;
    }

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if (video_mem == MAP_FAILED) {
        panic("couldn't map video memory");
        return NULL;
    }

    back_buffer = malloc(vram_size);
    if (back_buffer == NULL) {
        panic("couldn't allocate back buffer");
        return NULL;
    }
    memset(back_buffer, 0, vram_size);

    return video_mem;
}


int (video_set_mode)(uint16_t mode) {

    reg86_t reg;
    memset(&reg, 0, sizeof(reg));

    reg.intno = VBE_INTNO;
    reg.ah = VBE_AH;           
    reg.al = VBE_AL_SET_MODE;           
    reg.bx = mode | VBE_MODE_LINEAR_FRAME;

    if (sys_int86(&reg) != OK) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

    return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {

    if (x >= vmi.XResolution || y >= vmi.YResolution) return 1;

    unsigned int pixel_i = y * vmi.XResolution + x;

    char *pixel_addr = back_buffer + pixel_i * bytes_per_pixel;

    if (bytes_per_pixel == 2)
        *((uint16_t *)pixel_addr) = (uint16_t)color;
    else
        memcpy(pixel_addr, &color, bytes_per_pixel);

    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

    if (y >= vmi.YResolution || x >= vmi.XResolution)
        return 1;

    if (x + len > vmi.XResolution)
        len = vmi.XResolution - x;

    char *line = back_buffer + (y * vmi.XResolution + x) * bytes_per_pixel;

    if (bytes_per_pixel == 2) {
        uint16_t *pixels = (uint16_t *)line;
        uint16_t c = (uint16_t)color;
        for (uint16_t i = 0; i < len; i++)
            pixels[i] = c;
    }
    else {
        for (uint16_t i = 0; i < len; i++)
            memcpy(line + i * bytes_per_pixel, &color, bytes_per_pixel);
    }

    return 0;
}

int (vg_draw_image)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *pixels) {
    if (pixels == NULL || x >= vmi.XResolution || y >= vmi.YResolution)
        return 1;

    uint16_t src_width = width;

    if (x + width > vmi.XResolution)
        width = vmi.XResolution - x;
    if (y + height > vmi.YResolution)
        height = vmi.YResolution - y;

    if (bytes_per_pixel == 2) {
        for (uint16_t row = 0; row < height; row++) {
            char *dst = back_buffer + ((y + row) * vmi.XResolution + x) * bytes_per_pixel;
            const uint16_t *src = pixels + row * src_width;
            memcpy(dst, src, width * sizeof(uint16_t));
        }
    }
    else {
        for (uint16_t row = 0; row < height; row++) {
            for (uint16_t col = 0; col < width; col++)
                vg_draw_pixel(x + col, y + row, pixels[row * src_width + col]);
        }
    }

    return 0;
}

void (vg_flip)(void) {
    memcpy(video_mem, back_buffer, vram_size);
}
