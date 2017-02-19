#include "cng/mainloop.h"
#include "ncurses.h"
using namespace cng;

void DefaultMainLoop::init() {
	initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(0);

	keypad(stdscr, true);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	halfdelay(1);
}

void DefaultMainLoop::enter(Handler* handler) {
	m_handler = handler;
}

bool DefaultMainLoop::loop() {
	if( m_handler) m_handler -> sync();
	if(!m_handler) return false;

	int key = wgetch(stdscr);
	switch(key) {
		case KEY_MOUSE: {
			MEVENT mouseEvent;
			int mouseStatus = getmouse(&mouseEvent);
			Point position = { mouseEvent.x, mouseEvent.y };
			if(mouseStatus == OK) {
				int mouseButton = mouseEvent.bstate;
				if(mouseButton & BUTTON1_PRESSED)
					m_handler -> click(1, position);
				if(mouseButton & BUTTON1_RELEASED)
					m_handler -> release(1, position);
				if(mouseButton & BUTTON2_PRESSED)
					m_handler -> click(2, position);
				if(mouseButton & BUTTON2_RELEASED)
					m_handler -> release(2, position);
			}
		}
		break;

		default:
			m_handler -> keyboard(key);
	}
	return true;
}

void DefaultMainLoop::destroy() {
	endwin();
}
