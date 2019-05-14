#include "keyboard.h"

void c_hold(char key, enum keys *held) {
	switch(key) {
		case 'w':
			*held |= kb_w;
			break;
		case 's':
			*held |= kb_s;
			break;
		case 'a':
			*held |= kb_a;
			break;
		case 'd':
			*held |= kb_d;
			break;
		case ' ':
			*held |= kb_space;
			break;
		case 'c':
			*held |= kb_c;
			break;
	}
}

void c_release(char key, enum keys *held) {
	switch(key) {
		case 'w':
			*held &= kb_w ^ 0xFFFFF;
			break;
		case 's':
			*held &= kb_s ^ 0xFFFFF;
			break;
		case 'a':
			*held &= kb_a ^ 0xFFFFF;
			break;
		case 'd':
			*held &= kb_d ^ 0xFFFFF;
			break;
		case ' ':
			*held &= kb_space ^ 0xFFFFF;
			break;
		case 'c':
			*held &= kb_c ^ 0xFFFFF;
			break;
	}
}
