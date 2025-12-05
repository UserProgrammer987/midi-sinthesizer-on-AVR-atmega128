from mido import MidiFile

NOTE_NAMES = ['C', 'CS', 'D', 'DS', 'E', 'F', 'FS', 'G', 'GS', 'A', 'AS', 'B']

def midi_note_to_name(n):
    octave = (n // 12) - 1
    name = NOTE_NAMES[n % 12]
    return f"{name}{octave}"

def extract_segments(mid):
    ticks_per_beat = mid.ticks_per_beat

    # читаем все note_on/note_off с абсолютным временем
    events = []
    for track in mid.tracks:
        current_time = 0
        for msg in track:
            current_time += msg.time
            if msg.type == "note_on" and msg.velocity > 0:
                events.append((current_time, "on", msg.note))
            elif (msg.type == "note_on" and msg.velocity == 0) or msg.type == "note_off":
                events.append((current_time, "off", msg.note))

    # сортируем по времени
    events.sort(key=lambda x: x[0])

    segments = []
    active_notes = set()
    last_time = 0

    for time, typ, note in events:
        if time != last_time:
            if active_notes:
                duration_ticks = time - last_time
                segments.append((set(active_notes), duration_ticks))
            last_time = time

        if typ == "on":
            active_notes.add(note)
        elif note in active_notes:
            active_notes.remove(note)

    return segments, ticks_per_beat


def segments_to_output(segments, tpq):
    result = []
    for notes_set, ticks in segments:
        notes_list = sorted(list(notes_set))
        names = [midi_note_to_name(n) for n in notes_list]

        # дополняем до 4 нот
        while len(names) < 4:
            names.append("0")
        names = names[:4]

        # перевод длительности в полбиты
        halfbeats = ticks / (tpq / 2)
        result.append((names, int(round(halfbeats))))

    return result


def convert_midi_to_array(filename):
    mid = MidiFile(filename)
    segments, tpq = extract_segments(mid)
    output = segments_to_output(segments, tpq)

    out_strings = []
    for notes, length in output:
        s = "{" + ", ".join(str(x) for x in notes) + f", {length}" + "}"
        out_strings.append(s)

    # Добавляем запятую между элементами и перенос строки каждые 8 элементов
    result_lines = []
    for i in range(0, len(out_strings), 8):
        line = ", ".join(out_strings[i:i+8])
        result_lines.append(line)
    
    print(",\n".join(result_lines))


# ----------------------------------
# Использование:
convert_midi_to_array("D:/Study/5sem/MPU SU/st7920/Megalovania.mid")
# ----------------------------------