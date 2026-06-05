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
        (void)right_clicked;

        if (!left_clicked)
            return;

        int mx = ctrl->mouse_x;
        int my = ctrl->mouse_y;

        if (mx < SCREEN_WIDTH / 2)
            return;

        int panel_left = SCREEN_WIDTH / 2;
        int panel_w    = SCREEN_WIDTH / 2;
        int center_x   = 3 * SCREEN_WIDTH / 4;
        int total_w    = CHAR_SELECT_COLS * CS_BOX_SIZE + (CHAR_SELECT_COLS - 1) * CS_BOX_GAP;
        int row_x      = panel_left + (panel_w - total_w) / 2;

        for (int i = 0; i < CHAR_COUNT; i++) {
            int col = i % CHAR_SELECT_COLS;
            int row = i / CHAR_SELECT_COLS;
            int bx  = row_x + col * (CS_BOX_SIZE + CS_BOX_GAP);
            int by  = CS_BOX_Y + row * (CS_BOX_SIZE + CS_BOX_GAP);

            if (mx >= bx && mx < bx + (int)CS_BOX_SIZE && my >= by && my < by + (int)CS_BOX_SIZE) {
                char_select_p2_set_char(&g->char_select, i);
                g->char_select.p2_ready = false;
                return;
            }
        }

        int bx = center_x - (int)CS_BTN_W / 2;

        if (mx >= bx && mx < bx + (int)CS_BTN_W && my >= (int)CS_BTN_Y && my < (int)CS_BTN_Y + (int)CS_BTN_H)
            g->char_select.p2_ready = !g->char_select.p2_ready;
  }
  

  
