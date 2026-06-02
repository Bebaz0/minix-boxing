# Game Rules — 2D Boxing Game

## Overview

A two-player local boxing game with Street Fighter-style 2D visuals. Both players compete simultaneously, each using a different input device. The last player standing wins.

---

## Players

| | Player 1 | Player 2 |
|---|---|---|
| **Input** | Keyboard (Q W E R) | Mouse |
| **Mechanic** | Press the correct keys as they appear | Click highlighted zones (bubbles) on screen |

---

## Objective

Reduce your opponent's HP to zero before your own HP reaches zero.

---

## Core Loop

Both players act simultaneously in a continuous fight:
1. **Timing events** spawn continuously and independently for each player — key prompts for Player 1, bubbles for Player 2.
2. Multiple timing events can be active at the same time (e.g. two bubbles on screen while Player 1 has two key prompts to press).
3. Each event has a response window; the player must act before it closes.
4. Early hits are **perfect**; late hits are **normal**; no hit before the window closes is a **failure**.
5. Players who **fail** a timing event take damage to themselves.
6. Players who land a **perfect hit** fill their combo bar; a full combo bar deals big damage to the opponent.
7. This continues until one player's HP reaches 0 or the round timer runs out.

---

## Player 1 — Keyboard (Q W E R) — Key Prompts

- Key prompts appear on screen each showing one key from {Q, W, E, R}.
- Multiple key prompts can be active at the same time; Player 1 must press each before its window closes.
- New key prompts spawn on a timer — independently of whether previous ones were resolved.
- **Perfect hit** (early in the window): fills combo bar.
- **Normal hit** (late in the window): no damage, no combo.
- **Failure** (window expires without the key being pressed): Player 1 takes damage to their own HP.
- Key assignment: Random per prompt
- Response window: _[To be Defined]_ — harder than Player 2's window
- Simultaneous prompts: _[To be Defined]_ max active at once

---

## Player 2 — Mouse (Bubbles)

- Bubble timing events appear at random positions on screen.
- Multiple bubbles can be active at the same time; Player 2 must click each one before its window closes.
- New bubbles spawn on a timer — independently of whether previous ones were resolved.
- Player can 
- **Perfect hit** (early in the window): fills combo bar.
- **Normal hit** (late in the window): no damage, no combo.
- **Failure** (window expires without a click): Player 2 takes damage to their own HP.
- Position: Randomized
- Response window: _[To be Defined]_
- Simultaneous bubbles: _[To be Defined]_ max active at once

---

## Rounds

- Each round has a **countdown timer** visible to both players.
- A round ends when the timer hits 0 or a player dies — whichever comes first.
- After a round ends there is a 3-second break before the next round starts.
- There is no limit on the number of rounds — the match continues until someone dies.
- Round duration: _[To be Defined]_

### Difficulty Progression (per round)

- The **response window** (time per challenge) decreases at the start of each new round.
- The challenges themselves remain continuous — only the window to respond shrinks.
- Minimum response window: _[To be Defined]_ (floor to avoid zero-time challenges)

---

## Combo Bar

- Each player has their own combo bar, displayed on screen.
- The bar fills only with **perfect hits** (hitting an element with ideal timing).
- Normal hits do not fill the combo bar.
- When a player's combo bar is **full**, it automatically deals damage to the opponent.
- After triggering, the combo bar resets to empty.
- Combo damage: _[to be filled]_
- Combo bar size (hits required to fill): _[to be filled]_
- Does the combo bar reset on failure: _[to be filled]_

---

## Health Points (HP)

- Each player starts with the same amount of HP.
- Starting HP: 100%
- Damage dealt per failure: _[to be filled — scales with difficulty]_
- HP cannot go below 0.
- HP bars are displayed on screen at all times.

---

## Win Condition

- The player whose HP reaches **0 first loses**.
- The surviving player wins the match.
- Draw condition (simultaneous KO): If we lose the same hp required to bring us to 0 at the same time. Shows draw result

---

## Match Structure

- Number of rounds per match: infinite
- Inter-round break: 3 seconds
- Rematch / return to menu

---

## Visual Feedback

- **Success:** _[to be filled — e.g., hit animation, flash, sound cue]_
- **Failure:** _[to be filled — e.g., recoil animation, screen shake]_ , health reduces
- Countdown display style: Digital Timer Style

---

## Difficulty Progression

- At the start of each new round the response window for both players shrinks by a fixed amount.
- The challenges themselves are always continuous — difficulty comes purely from having less time to react.
- Decrease per round: _[To be Defined]_

---

## Game States

| State | Description |
|---|---|
| **Main Menu** | _[to be filled]_ |
| **Round Start** | 3 second countdown before the round begins |
| **Active** | Timing events spawn continuously — key prompts for P1, bubbles for P2; multiple can be active at once |
| **Round End** | 3 Second wait until next Round|
| **Game Over** | Winner displayed, option to rematch or quit |
