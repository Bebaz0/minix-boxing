#include "char_select_controller.h"
#include "kbc.h"

  void char_select_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
      (void)ctrl;

      if (scancode & SCANCODE_BREAK_MASK)
          return;

      switch (scancode) {
          case SCANCODE_LEFT:
          case SCANCODE_A:
              char_select_p1_prev(&g->char_select);
              g->char_select.p1_ready = false;
              break;
          case SCANCODE_RIGHT:
          case SCANCODE_D:
              char_select_p1_next(&g->char_select);
              g->char_select.p1_ready = false;
              break;
          case SCANCODE_ENTER:
              g->char_select.p1_ready = !g->char_select.p1_ready;
              break;
          case SCANCODE_ESC:
              char_select_init(&g->char_select);
              g->state = GS_MENU;
              break;
          default:
              break;
      }       
  }   

  void char_select_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
        (void)ctrl;
        (void)g;
        (void)left_clicked;
        (void)right_clicked;
  }