//
// Created by modnick on 18.12.2024.
//

#ifndef FYRFYROS_LOGER_H
#define FYRFYROS_LOGER_H

#include "_flags.h"
#include "vga_driver.h"

void log_massage_cond(byte cond, char* comment_str, u32 hex, byte clear_mode);
void log_warning_cond(byte cond,char* comment_str, u32 hex, byte clear_mode);
void log_expression_cond(byte cond,char* comment_str, u32 hex, byte clear_mode);

void log_massage(char* comment_str, u32 hex, byte clear_mode);
void log_warning(char* comment_str, u32 hex, byte clear_mode);
void log_expression(char* comment_str, u32 hex, byte clear_mode);
void log_critical_error();

#endif //FYRFYROS_LOGER_H
