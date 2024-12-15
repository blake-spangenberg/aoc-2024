#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <termios.h>

#include "../util.h"
#include "../14-1/input.h"

#define TIME_ELAPSED (100)
#define COLS (101)
#define ROWS (103)

#define KEY_ESCAPE (0x1B)
#define KEY_LEFT   (0x44)
#define KEY_RIGHT  (0x43)
#define KEY_SHIFT  (0x32)

static struct termios orig_termios;

// note: % in C is the remainder, not the modulus
static int32_t _mod(int32_t a, int32_t b)
{
    int32_t r = a % b;
    return r < 0 ? r + b : r;
}

static void _move_robot(robot_t* robot, int dt)
{
    robot->pos.x = _mod(robot->pos.x + robot->vel.x * dt, COLS);
    robot->pos.y = _mod(robot->pos.y + robot->vel.y * dt, ROWS);
}

static void _print_robots(const robots_t* robots)
{
    putchar('\n');
    for (unsigned y = 0; y < COLS; y++) {
        for (unsigned x = 0; x < COLS; x++) {
            unsigned count = 0;
            for (unsigned i = 0; i < ARRAY_LEN(robots->data); i++) {
                const xy_t pos = robots->data[i].pos;
                if (pos.x == x && pos.y == y) {
                    count++;
                }
            }
            
            if (count) {
                putchar('0' + count);
            } else {
                putchar('.');
            }
        }
        putchar('\n');
    }
}

static void _disable_raw_terminal(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void _enable_raw_terminal(void) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(_disable_raw_terminal);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


static void _delay(void)
{
    static const long PERIOD_MS = 100;

    static struct timeval last = {};
    
    struct timeval current = {};
    gettimeofday(&current, NULL);

    long elapsed_us = current.tv_usec - last.tv_usec + (current.tv_sec - last.tv_sec) * 1000000;
    long elapsed_ms = elapsed_us / 1000;

    last = current;

    if (elapsed_ms > PERIOD_MS) {
        return;
    }

    unsigned int usec = (PERIOD_MS - elapsed_ms) * 1000;
    struct timespec req = {0, usec * 1000}; // seconds, nanoseconds
    nanosleep(&req, NULL);
}

static char _get_input(void) {
    int nread;
    char c, seq[3];
    while ((nread = read(STDIN_FILENO, &c, 1)) == 0);
    if (nread == -1) exit(EXIT_FAILURE);

    if (c == KEY_ESCAPE) {
        if (read(STDIN_FILENO, &seq[0], 1) == 0 || seq[0] != '[') return c;
        if (read(STDIN_FILENO, &seq[1], 1) == 0) return c;

        if (seq[1] == KEY_SHIFT) {
            if (read(STDIN_FILENO, &seq[2], 1) == 0) return c;
            if (seq[2] == KEY_RIGHT) return 'a'; // Shift + Right
            if (seq[2] == KEY_LEFT) return 'b'; // Shift + Left
        } else {
            if (seq[1] == KEY_RIGHT) return KEY_RIGHT; // Right
            if (seq[1] == KEY_LEFT) return KEY_LEFT; // Left
        }
    }

    return c;
}

int main(void)
{
    int t = 38;

    _enable_raw_terminal();
    unsigned dt = 0;

    // dt was -1 + 1,
    // I used it to rapidly explore until I found a pattern repeating every 101 seconds like so:
    // 38, 139, 240...

    while (true) {
        robots_t robots = ROBOTS;
        t += dt;
        for (unsigned i = 0; i < ARRAY_LEN(robots.data); i++) {
            _move_robot(&robots.data[i], t);
        }
        _print_robots(&robots);
        printf("t = %d\n", t);
        _delay();
        switch (_get_input()) {
            case KEY_RIGHT:
                dt = 101;
                break;
            case KEY_LEFT:
                dt = -101;
                break;
            default:
                dt = 0;
        }
    }

    return 0;
}

// 7815 - too low
