#include "cng/mainloop.h"
#include "ncurses.h"
using namespace cng;

void DefaultMainLoop::init() {
	initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	halfdelay(1);

	keypad(stdscr, true);
	mousemask(ALL_MOUSE_EVENTS, NULL);
}

void DefaultMainLoop::enter(Handler* handler) {
	m_handlerAccess.lock();
	m_handler = handler;
	m_handlerAccess.unlock();
}

bool DefaultMainLoop::loop() {
	if( m_handler) m_handler -> sync();
	int key = wgetch(stdscr);

	m_handlerAccess.lock();
	if(!m_handler) return false;
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

		case -1:
			break;

		default:
			m_handler -> keyboard(key);
	}
	m_handlerAccess.unlock();
	return true;
}

void DefaultMainLoop::destroy() {
	endwin();
}
