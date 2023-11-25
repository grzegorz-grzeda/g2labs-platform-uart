/*
 * MIT License
 *
 * Copyright (c) 2023 G2Labs Grzegorz Grzęda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "g2labs-platform-uart.h"
#include <pthread.h>
#include <stdio.h>

static platform_uart_receive_handler_t uart_receive_handler = NULL;

static void* detect_keypress(void* ptr) {
    char data[2] = {0};
    while (1) {
        char c = getchar();
        if (c == '\n') {
            c = '\r';
        }
        data[0] = c;
        if (uart_receive_handler) {
            uart_receive_handler(data, 1);
        }
    }
}

void platform_uart_initialize(uint32_t baudrate, platform_uart_receive_handler_t handler) {
    uart_receive_handler = handler;
    pthread_t thread1;
    pthread_create(&thread1, NULL, detect_keypress, NULL);
}

void platform_uart_send_data(const uint8_t* data, size_t size) {
    printf("%.*s", (int)size, (const char*)data);
}