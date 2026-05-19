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
1. Player 1 sees keys appear on screen and must press them; Player 2 sees bubbles appear and must click them.
2. Each player must hit their elements with the best timing possible.
3. Players who **fail** their challenge take damage to themselves.
4. Players who **succeed** their challenge perfectly fill a combo bar that when full deals big damage to the other player (Not yet sure if this will be implemented)
5. This happens until one of them dies

---

## Player 1 — Keyboard (Q W E R)

- Keys (Q, W, E, R) appear on screen and Player 1 must press them before time runs out.
- **Success:** : If hit doesnt take health, if perfect fills combo bar
- **Failure:** Player 1 takes damage to their own HP.
- Keys in the sequence: _[Q,W,E,R]_
- Key Sequence: Random
- Timing: _[To be Defined]_ But harder than player 2

---

## Player 2 — Mouse (Bubbles)

- Bubbles (highlighted zones) appear on screen at random positions.
- Player 2 must click each bubble before time runs out.
- **Success:**: If hit doesnt take health, if perfect fills combo bar
- **Failure:** Player 2 takes damage to their own HP.
- Zone layout: Randomized
- Timing: _[To be Defined]_

---

## Rounds

- Each Round has a countdown timer visible to the players.
- Rounds are infinite if no plyer dies
- The time window **decreases as the fight progresses**, raising difficulty over time.
- Time window: _[to be Defined]_

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

- The time window shrinks over rounds

---

## Game States

| State | Description |
|---|---|
| **Main Menu** | _[to be filled]_ |
| **Round Start** | 3 second countdown before the round begins |
| **Active** | Both players act simultaneously — keys appear for P1, bubbles appear for P2 |
| **Round End** | 3 Second wait until next Round|
| **Game Over** | Winner displayed, option to rematch or quit |
