# Game Rules — 2D Boxing Game

## Overview

A two-player local boxing game with Street Fighter-style 2D visuals. Both players compete simultaneously, each using a different input device. The last player standing wins.

---

## Players

| | Player 1 | Player 2 |
|---|---|---|
| **Input** | Keyboard | Mouse |
| **Challenge** | Press a displayed key sequence in order | Click a highlighted screen zone |

---

## Objective

Reduce your opponent's HP to zero before your own HP reaches zero.

---

## Core Loop

Each round, both players are simultaneously presented with a challenge:
1. A challenge is displayed to each player.
2. Each player must complete their challenge within the time window.
3. Players who **fail** their challenge take damage to themselves.
4. Players who **succeed** their challenge fill a combo bar that when full deals big damage to the other player
5. A new challenge immediately follows.

---

## Player 1 — Keyboard Challenge

- A random key sequence is displayed on screen.
- Player 1 must press the keys **in the correct order** before time runs out.
- **Success:** 
- **Failure:** Player 1 takes damage to their own HP.
- Keys in the sequence: _[number/range to be filled]_
- Valid keys used: _[to be filled — e.g., WASD, arrow keys, letter subset]_

---

## Player 2 — Mouse Challenge

- One or more zones on screen are highlighted.
- Player 2 must click the correct highlighted zone before time runs out.
- **Success:** _[to be filled — e.g., attack opponent, block incoming damage]_
- **Failure:** Player 2 takes damage to their own HP.
- Zone layout: Randomized
- Timing: _[To be Defined]_

---

## Time Window

- Each challenge has a countdown timer visible to the player.
- The time window **decreases as the fight progresses**, raising difficulty over time.
- Starting time limit: _[to be filled — e.g., 3 seconds]_
- Minimum time limit (floor): _[to be filled]_
- Rate of decrease: _[to be filled — e.g., every N successful rounds, every X seconds elapsed]_

---

## Health Points (HP)

- Each player starts with the same amount of HP.
- Starting HP: _[to be filled]_
- Damage dealt per failure: _[to be filled — e.g., fixed value, scales with difficulty]_
- HP cannot go below 0.
- HP bars are displayed on screen at all times.
- HP recovery: _[to be filled — e.g., none / partial on streak]_

---

## Win Condition

- The player whose HP reaches **0 first loses**.
- The surviving player wins the match.
- Draw condition (simultaneous KO): _[to be filled]_

---

## Match Structure

- Number of rounds per match: _[to be filled — e.g., best of 3 / single round]_
- Inter-round break: _[to be filled]_
- Rematch / return to menu: _[to be filled]_

---

## Visual Feedback

- **Success:** _[to be filled — e.g., hit animation, flash, sound cue]_
- **Failure:** _[to be filled — e.g., recoil animation, screen shake]_
- Challenge prompt location on screen: _[to be filled]_
- Countdown display style: _[to be filled — e.g., shrinking bar, number]_

---

## Difficulty Progression

- The time window shrinks over time (see Time Window section).
- _[to be filled — e.g., sequence length increases, more zones added, zones move]_

---

## Game States

| State | Description |
|---|---|
| **Main Menu** | _[to be filled]_ |
| **Round Start** | Brief pause before challenges begin |
| **Active** | Both players face simultaneous challenges |
| **Round End** | _[to be filled]_ |
| **Game Over** | Winner displayed, option to rematch or quit |
