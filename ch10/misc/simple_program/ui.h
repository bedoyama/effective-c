/*
 * Simple Calculator - ui.h
 * 
 * Public interface for user interface functions.
 */

#ifndef CALC_UI_H
#define CALC_UI_H

// Display operations
void show_menu(void);
void show_result(const char *operation, int result);
void show_error(const char *message);

// Input operations
int get_integer(const char *prompt);
char get_operation(void);

#endif /* CALC_UI_H */
