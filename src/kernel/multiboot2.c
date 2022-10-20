/**
 * @file multiboot2.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 20-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>
#include <com1_log.h>
#include <multiboot2.h>


/**
 * @brief Получение данных из multiboot2
 * 
 * @param magic Магическое число
 * @param addr Адресс структуры Multiboot2
 * @return true В случае успешной инициализации
 * @return false В случае ошибки
 */
bool multiboot2_init(unsigned int magic, unsigned int addr) {
    struct multiboot_tag *tag;
    unsigned size;

    /*  Am I booted by a Multiboot-compliant boot loader? */
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        com1_log("Invalid magic number: %x", (unsigned) magic);
        return false;
    }

    if (addr & 7) {
        com1_log ("Unaligned mbi: %x", addr);
        return false;
    }

    size = *(unsigned *) addr;
    com1_log ("Announced mbi size %x", size);
    
    for (tag = (struct multiboot_tag *) (addr + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                        + ((tag->size + 7) & ~7))) {
        com1_log ("Tag %x, Size %x", tag->type, tag->size);
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                com1_log ("Command line = %s",
                        ((struct multiboot_tag_string *) tag)->string);
                break;
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                com1_log ("Boot loader name = %s",
                        ((struct multiboot_tag_string *) tag)->string);
                break;
            case MULTIBOOT_TAG_TYPE_MODULE:
                com1_log ("Module at %x-%x. Command line %s",
                        ((struct multiboot_tag_module *) tag)->mod_start,
                        ((struct multiboot_tag_module *) tag)->mod_end,
                        ((struct multiboot_tag_module *) tag)->cmdline);
                break;
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                com1_log ("mem_lower = %uKB, mem_upper = %uKB",
                        ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower,
                        ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper);
                break;
            case MULTIBOOT_TAG_TYPE_BOOTDEV:
                com1_log ("Boot device %x,%u,%u",
                        ((struct multiboot_tag_bootdev *) tag)->biosdev,
                        ((struct multiboot_tag_bootdev *) tag)->slice,
                        ((struct multiboot_tag_bootdev *) tag)->part);
                break;
            case MULTIBOOT_TAG_TYPE_MMAP: {
                multiboot_memory_map_t *mmap;

                com1_log ("mmap");
        
                for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
                    (multiboot_uint8_t *) mmap 
                    < (multiboot_uint8_t *) tag + tag->size;
                    mmap = (multiboot_memory_map_t *) 
                    ((unsigned long) mmap
                        + ((struct multiboot_tag_mmap *) tag)->entry_size))
                com1_log (" base_addr = %x %x,"
                        " length = %x %x, type = %x",
                        (unsigned) (mmap->addr >> 32),
                        (unsigned) (mmap->addr & 0xffffffff),
                        (unsigned) (mmap->len >> 32),
                        (unsigned) (mmap->len & 0xffffffff),
                        (unsigned) mmap->type);
                }
                break;
            case MULTIBOOT_TAG_TYPE_VBE: {
                struct multiboot_tag_vbe *tag_vbe = (struct multiboot_tag_vbe *) tag;
                com1_log("vbe_mode: %d", tag_vbe->vbe_mode);
                com1_log("vbe_interface_seg: %d", tag_vbe->vbe_interface_seg);
                com1_log("vbe_interface_off: %d", tag_vbe->vbe_interface_off);
                com1_log("vbe_interface_len: %d", tag_vbe->vbe_interface_len);
                break;
            }  
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                multiboot_uint32_t color;
                struct multiboot_tag_framebuffer *tagfb = (struct multiboot_tag_framebuffer *) tag;
                void *fb = (void *) (unsigned long) tagfb->common.framebuffer_addr;

                switch (tagfb->common.framebuffer_type) {
                    case MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED: {
                        unsigned best_distance, distance;
                        struct multiboot_color *palette;
                    
                        palette = tagfb->framebuffer_palette;

                        color = 0;
                        best_distance = 4*256*256;
                    
                        for (unsigned int i = 0; i < tagfb->framebuffer_palette_num_colors; i++) {
                            distance = (0xff - palette[i].blue) 
                                * (0xff - palette[i].blue)
                                + palette[i].red * palette[i].red
                                + palette[i].green * palette[i].green;
                            if (distance < best_distance)
                                {
                                color = i;
                                best_distance = distance;
                                }
                            }
                        }
                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_RGB:
                        color = ((1 << tagfb->framebuffer_blue_mask_size) - 1) 
                        << tagfb->framebuffer_blue_field_position;
                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT:
                        color = '\\' | 0x0100;
                        break;

                    default:
                        color = 0xffffffff;
                        break;
                }
                
                for (unsigned int i = 0; i < tagfb->common.framebuffer_width && i < tagfb->common.framebuffer_height; i++) {
                    switch (tagfb->common.framebuffer_bpp) {
                        case 8: {
                            multiboot_uint8_t *pixel = fb
                                + tagfb->common.framebuffer_pitch * i + i;
                            *pixel = color;
                            }
                            break;
                        case 15:
                        case 16: {
                            multiboot_uint16_t *pixel
                                = fb + tagfb->common.framebuffer_pitch * i + 2 * i;
                            *pixel = color;
                            }
                            break;
                        case 24: {
                            multiboot_uint32_t *pixel
                                = fb + tagfb->common.framebuffer_pitch * i + 3 * i;
                            *pixel = (color & 0xffffff) | (*pixel & 0xff000000);
                            }
                            break;
                        case 32: {
                            multiboot_uint32_t *pixel
                                = fb + tagfb->common.framebuffer_pitch * i + 4 * i;
                            *pixel = color;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                    + ((tag->size + 7) & ~7));
    com1_log ("Total mbi size %x", (unsigned) tag - addr);

    return true;
}