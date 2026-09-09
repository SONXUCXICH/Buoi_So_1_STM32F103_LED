#include <stdint.h>
#define RCC_APB2ENR (*((volatile uint32_t *)0x40021018))
#define GPIOC_CRH   (*((volatile uint32_t *)0x40011004))
#define GPIOC_ODR   (*((volatile uint32_t *)0x4001100C))
void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    // 1. Cấp xung nhịp (clock) cho Port C (Bit 4)
    RCC_APB2ENR |= (1 << 4);

    // 2. Cấu hình chân PC13 làm Output (Push-Pull)
    GPIOC_CRH &= ~(0xF << 20); // Xóa cấu hình cũ của PC13 (bit 20 đến 23)
    GPIOC_CRH |= (0x2 << 20);  // Đặt cấu hình mới là Output mode, max speed 2MHz

    // 3. Vòng lặp nháy LED vô tận
    while (1) {
        GPIOC_ODR ^= (1 << 13); // Đảo trạng thái logic của chân PC13
        delay(500000);          // Trễ để mắt người kịp nhìn thấy
    }
    return 0;
}
