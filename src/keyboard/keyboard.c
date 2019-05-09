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
			*held &= kb_w ^ kb_w;
			break;
		case 's':
			*held &= kb_s ^ kb_s;
			break;
		case 'a':
			*held &= kb_a ^ kb_a;
			break;
		case 'd':
			*held &= kb_d ^ kb_d;
			break;
		case ' ':
			*held &= kb_space ^ kb_space;
			break;
		case 'c':
			*held &= kb_c ^ kb_c;
			break;
	}
}
