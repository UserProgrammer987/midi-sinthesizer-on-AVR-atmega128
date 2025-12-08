#!/usr/bin/env python3
import math

# ---------- Настройки ----------
SAMPLE_RATE = 15935.0        # ваш sample rate
A4_FREQ = 440.0              # стандарт
TABLE_SIZE = 256             # таблица синуса

# ---------- Функции ----------
def midi_to_freq(midi_note, a4=A4_FREQ):
    return a4 * (2 ** ((midi_note - 69) / 12.0))

# Для 16-битного фазового аккумулятора
PHASE_MOD = 65536.0          # 2^16


# ---------- Генерация phase_step ----------
phase_steps = []
for note in range(0, 101):
    freq = midi_to_freq(note)
    val = int((freq * PHASE_MOD) / SAMPLE_RATE) & 0xFFFF
    phase_steps.append(val)


# ---------- Генерация таблицы синуса (0..255) ----------
sine_table = []
for i in range(TABLE_SIZE):
    # синус от 0 до 2π
    s = math.sin(2.0 * math.pi * i / TABLE_SIZE)
    # переносим -1..1 → 0..255
    v = int((s * 127.5) + 127.5) & 0xFF
    sine_table.append(v)


# ---------- Печать ----------
print(f"/* Generated for 16-bit phase accumulator, SAMPLE_RATE = {SAMPLE_RATE} */\n")

# ---- phase_step ----
print("static const uint16_t phase_step[101] = {")
for i, v in enumerate(phase_steps):
    if i % 8 == 0:
        print("    ", end="")
    print(f"{v:6d}, ", end="")
    if i % 8 == 7:
        print()
if len(phase_steps) % 8 != 0:
    print()
print("};\n")


# ---- sine table ----
print(f"static const uint8_t sine256[{TABLE_SIZE}] = {{")
for i, v in enumerate(sine_table):
    if i % 16 == 0:
        print("    ", end="")
    print(f"{v:3d}, ", end="")
    if i % 16 == 15:
        print()
if len(sine_table) % 16 != 0:
    print()
print("};")
