#ifndef SIGNAL_HANDLERS_H
#define SIGNAL_HANDLERS_H

extern int num_handlers;
void signal_handler(int signum);
void register_signal_handlers();

#endif
