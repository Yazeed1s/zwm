/*
 * BSD 2-Clause License
 * Copyright (c) 2024, Yazeed Alharthi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	  1. Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	  2. Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ZWM_ZWM_H
#define ZWM_ZWM_H

#include "type.h"
#include <xcb/xcb_icccm.h>
#include <xcb/xproto.h>

// clang-format off
extern config_t 		  conf;
extern wm_t 			  *wm;
extern xcb_window_t 	  focused_win;
extern monitor_t 		  *head_monitor;
extern monitor_t		  *prim_monitor;
extern monitor_t 		  *cur_monitor;
extern bool 			  using_xrandr;
extern bool 		      using_xinerama;
extern uint8_t 			  randr_base;

xcb_get_geometry_reply_t *get_geometry(xcb_window_t win, xcb_conn_t *c);
xcb_atom_t                get_atom(char *atom_name, xcb_conn_t *con);
client_t                 *create_client(xcb_window_t win, xcb_atom_t wtype, xcb_conn_t *cn);
client_t                 *find_client_by_window(xcb_window_t win);
xcb_window_t 			  get_window_under_cursor(xcb_conn_t *conn, xcb_window_t win);
bool                      window_exists(xcb_conn_t *conn, xcb_window_t win);
bool					  should_ignore_hints(xcb_window_t win, const char *name);
void                      init_clients();
desktop_t 				 *init_desktop();
void                      add_client(client_t *new_client);
void                      free_clients();
void 					  raise_window(xcb_window_t win);
void 		              lower_window(xcb_window_t win);
void                      grab_buttons(xcb_window_t win);
void                      window_grab_buttons(xcb_window_t win);
void 					  window_above(xcb_window_t, xcb_window_t);
void 				      window_below(xcb_window_t, xcb_window_t);
void				      update_grabbed_window(node_t *root, node_t *n);
void 					  ungrab_keys(xcb_conn_t *conn, xcb_window_t win);
desktop_t                *get_focused_desktop(void);
monitor_t                *get_focused_monitor();
int16_t                   get_cursor_axis(xcb_conn_t *conn, xcb_window_t window);
int                       exec_process(arg_t *arg);
int 					  layout_handler(arg_t *arg);
int 					  cycle_win_wrapper(arg_t *arg);
int  					  set_fullscreen(node_t *n, bool flag);
int  					  set_fullscreen_wrapper();
int 					  flip_node_wrapper();
int                       reload_config_wrapper();
int						  handle_tiled_window_request(xcb_window_t win, desktop_t *d);
int						  handle_floating_window_request(xcb_window_t win, desktop_t *d);
int						  handle_bar_request(xcb_window_t win, desktop_t *d);
int					      grab_keys(xcb_conn_t *conn, xcb_window_t win);
int 					  win_focus(xcb_window_t win, bool set_focus);
int                       handle_first_window(client_t *client, desktop_t *d);
int                       handle_subsequent_window(client_t *client, desktop_t *d);
int                       set_active_window_name(xcb_window_t win);
int                       kill_window(xcb_window_t win);
int                       hide_window(xcb_window_t win);
int                       get_focused_desktop_idx();
int                       set_window_state(xcb_window_t win, xcb_icccm_wm_state_t state);
int                       show_window(xcb_window_t win);
int 				      switch_desktop_wrapper(arg_t *arg);
int 				      switch_desktop(const int nd);
int 					  cycle_desktop_wrapper(arg_t *arg);
int 					  close_or_kill_wrapper();
int 					  close_or_kill(xcb_window_t win);
int 					  horizontal_resize_wrapper(arg_t *arg);
int 					  traverse_stack_wrapper(arg_t *arg);
int                       resize_window(xcb_window_t win, uint16_t width, uint16_t height);
int                       move_window(xcb_window_t win, int16_t x, int16_t y);
int                       handle_map_request(const xcb_map_request_event_t *ev);
int                       handle_enter_notify(const xcb_enter_notify_event_t *ev);
int                       tile(node_t *node);
int 					  set_focus(node_t *n, bool flag);
int                       handle_leave_notify(const xcb_leave_notify_event_t *ev);
int                       change_border_attr(xcb_conn_t *, xcb_window_t, uint32_t, uint32_t, bool);
int                       change_window_attr(xcb_conn_t *, xcb_window_t, uint32_t, const void *);
int                       configure_window(xcb_conn_t *, xcb_window_t, uint16_t, const void *);
int                       set_input_focus(xcb_conn_t *, uint8_t, xcb_window_t, xcb_timestamp_t );
int                       handle_xcb_error(xcb_conn_t *, xcb_void_cookie_t, const char *);
int 					  swap_node_wrapper();
int                       ewmh_update_current_desktop(xcb_ewmh_connection_t*, int, uint32_t);
char 					  *win_name(xcb_window_t win);
int                       ewmh_update_number_of_desktops(void);
#endif // ZWM_ZWM_H
