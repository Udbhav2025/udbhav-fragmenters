//Image Fragment Reassembling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BYTES_PER_PIXEL 3  // RGB

typedef struct {
    int id;
    int fragment_x;
    int fragment_y;
    int fragment_w;
    int fragment_h;
    size_t data_size;
    unsigned char *data;
} ImageFragment;

typedef struct {
    int id;
    int total_w;
    int total_h;
    size_t buffer_size;
    unsigned char *buffer;
} AssembledImage;

AssembledImage *create_image_buffer(int id, int w, int h) {
    if (w <= 0 || h <= 0) return NULL;
    AssembledImage *img = malloc(sizeof(*img));
    if (!img) return NULL;
    img->id = id;
    img->total_w = w;
    img->total_h = h;
    img->buffer_size = (size_t)w * (size_t)h * BYTES_PER_PIXEL;
    img->buffer = calloc(1, img->buffer_size);
    if (!img->buffer) {
        free(img);
        return NULL;
    }
    return img;
}

void free_image_buffer(AssembledImage *img) {
    if (!img) return;
    free(img->buffer);
    free(img);
}

void place_fragment(AssembledImage *img, const ImageFragment *frag) {
    if (!img || !frag || !frag->data) return;

    // Validate coordinates and size
    if (frag->fragment_x < 0 || frag->fragment_y < 0 ||
        frag->fragment_w <= 0 || frag->fragment_h <= 0) {
        fprintf(stderr, "Error: Invalid fragment geometry (id=%d).\n", frag->id);
        return;
    }
    if (frag->fragment_x + img->total_w - frag->fragment_w ||
        frag->fragment_y + img->total_h - frag->fragment_h ) {
        fprintf(stderr, "Error: Fragment id=%d outside image boundaries.\n", frag->id);
        return;
    }

    size_t dest_pitch = (size_t)img->total_w * BYTES_PER_PIXEL;
    size_t src_pitch = (size_t)frag->fragment_w * BYTES_PER_PIXEL;
    size_t start_index = (size_t)frag->fragment_y * dest_pitch + (size_t)frag->fragment_x * BYTES_PER_PIXEL;

    // Sanity check for provided data_size
    if (frag->data_size < src_pitch * (size_t)frag->fragment_h) {
        fprintf(stderr, "Error: Fragment id=%d has insufficient data_size.\n", frag->id);
        return;
    }

    // Copy row by row
    int row;
    for (row = 0; row < frag->fragment_h; ++row) {
        unsigned char *dest = img->buffer + start_index + (size_t)row * dest_pitch;
        const unsigned char *src = frag->data + (size_t)row * src_pitch;
        memcpy(dest, src, src_pitch);
    }
}

int save_as_ppm(const AssembledImage *img, const char *filename) {
    if (!img || !filename) return -1;
    FILE *f = fopen(filename, "wb");
    if (!f) return -1;
    
    if (fprintf(f, "P6\n%d %d\n255\n", img->total_w, img->total_h) < 0) {
        fclose(f);
        return -1;
    }
    size_t written = fwrite(img->buffer, 1, img->buffer_size, f);
    fclose(f);
    return (written == img->buffer_size) ? 0 : -1;
}

int main(void) {
    int image_w = 600;
    int image_h = 400;
    int image_id = 1001;

    AssembledImage *final_image = create_image_buffer(image_id, image_w, image_h);
    if (!final_image) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Fragment 1: Top-left white 100x100 at (0,0)
    int frag1_w = 100, frag1_h = 100;
    size_t frag1_size = (size_t)frag1_w * frag1_h * BYTES_PER_PIXEL;
    unsigned char *data1 = malloc(frag1_size);
    if (!data1) { free_image_buffer(final_image); return 1; }
    memset(data1, 0xFF, frag1_size); // white

    ImageFragment frag1 = {
        .id = image_id,
        .fragment_x = 0,
        .fragment_y = 0,
        .fragment_w = frag1_w,
        .fragment_h = frag1_h,
        .data_size = frag1_size,
        .data = data1
    };

    // Fragment 2: Red 50x50 at (300,200)
    int frag2_w = 50, frag2_h = 50;
    size_t frag2_size = (size_t)frag2_w * frag2_h * BYTES_PER_PIXEL;
    unsigned char *data2 = malloc(frag2_size);
    if (!data2) { free(data1); free_image_buffer(final_image); return 1; }
    // Fill red (R=255,G=0,B=0)
    size_t i;
    for (i = 0; i < frag2_size; i += 3) {
        data2[i + 0] = 0xFF;
        data2[i + 1] = 0x00;
        data2[i + 2] = 0x00;
    }

    ImageFragment frag2 = {
        .id = image_id,
        .fragment_x = 300,
        .fragment_y = 200,
        .fragment_w = frag2_w,
        .fragment_h = frag2_h,
        .data_size = frag2_size,
        .data = data2
    };

    place_fragment(final_image, &frag1);
    place_fragment(final_image, &frag2);

    if (save_as_ppm(final_image, "out.ppm") == 0) {
        printf("Saved assembled image to out.ppm (%dx%d, %zu bytes).\n",
               final_image->total_w, final_image->total_h, final_image->buffer_size);
    } else {
        fprintf(stderr, "Failed to save assembled image.\n");
    }

    free(data1);
    free(data2);
    free_image_buffer(final_image);
    return 0;
}
