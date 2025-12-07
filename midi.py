from mido import MidiFile

NOTE_NAMES = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]

def midi_note_to_name(note):
    octave = note // 12 - 1
    return NOTE_NAMES[note % 12] + str(octave)


def convert_midi_to_events(path, tick_us=63, release_us=5000):
    midi = MidiFile(path)
    ticks_per_beat = midi.ticks_per_beat

    # --- 1. собрать все сообщения по абсолютному тику ---
    msgs = []
    for track in midi.tracks:
        abs_tick = 0
        for msg in track:
            abs_tick += msg.time
            msgs.append((abs_tick, msg))
    msgs.sort(key=lambda x: x[0])

    # --- 2. перевод тиков в микросекунды ---
    tempo = 500000
    current_time_us = 0
    prev_tick = 0

    active = {}
    raw = []

    for abs_tick, msg in msgs:
        delta = abs_tick - prev_tick
        if delta > 0:
            current_time_us += (delta * tempo) / ticks_per_beat
            prev_tick = abs_tick

        if msg.type == "set_tempo":
            tempo = msg.tempo

        if msg.type == "note_on" and msg.velocity > 0:
            key = (msg.note, msg.channel)
            active.setdefault(key, []).append(current_time_us)

        elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
            key = (msg.note, msg.channel)
            if key not in active or not active[key]:
                continue

            start = active[key].pop(0)
            end = current_time_us - release_us
            if end < start:
                end = start

            raw.append((start, 1, msg.note, msg.channel))
            raw.append((end, 0, msg.note, msg.channel))

    # --- 3. Перевод времени в ТИКИ ---
    events = []
    for t_us, tp, note, ch in raw:
        tick = int(t_us / 63)
        events.append([tick, tp, note, ch])

    events.sort(key=lambda x: (x[0], -x[1], x[2], x[3]))

    # --- 4. полифония (сдвиг событий) ---
    fixed = []
    last_tick = None
    shift = 0

    for tick, tp, note, ch in events:
        if tick != last_tick:
            shift = 0
            last_tick = tick

        new_tick = tick + shift
        shift += 1

        fixed.append((new_tick, tp, note, ch))

    fixed.sort(key=lambda x: (x[0], -x[1], x[2], x[3]))

    # --- 5. перевод ТИК → ШАГИ (1 step = 954 ticks) ---
    final = []
    for tick, tp, note, ch in fixed:
        step = tick // 954
        final.append((note, tp, ch, step))

    # --- 6. Упаковка 16-битного значения ---
    # bit 15     = tp
    # bits 14-12 = channel
    # bits 11-0  = step
    out = []

    for note, tp, ch, step in final:
        event_word = ((tp & 1) << 15) | ((ch & 0b111) << 12) | (step & 0xFFF)
        note_name = midi_note_to_name(note)
        out.append(f"{{{note_name}, {event_word}}}")

    return "static event megalovania[] =\n{\n    " + ", ".join(out) + ", {}\n};"

print(convert_midi_to_events("D:/Study/5sem/MPU SU/st7920/Megalovania.mid"))