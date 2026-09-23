#!/usr/bin/env python3
"""Convert EasyEDA Standard PCB JSON files to KiCad 10 projects.

Uses KiCad's native EasyEDA importer (kicad-cli pcb import), then links
matching footprints to an existing KiCad schematic by reference/UUID.

Example:
    python3 PCBs/easyeda_to_kicad.py Stage_Module
"""

from __future__ import annotations

import argparse
import json
import math
import re
import shutil
import subprocess
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KICAD_DIR = ROOT / "PCBs/KiCad"
LEGACY_KICAD_DIR = ROOT / "Documents/Schematics/Source Files/KiCAD"
EASYEDA_ROOT = ROOT / "PCBs/projects"
FP_LIB_NAME = "USC_EasyEDA"
FP_LIB_DIR = KICAD_DIR / f"{FP_LIB_NAME}.pretty"

def pcb(rel: str, **extra) -> dict:
    cfg = {
        "easyeda": EASYEDA_ROOT / rel,
        "company": "UNTITLED SPACE CRAFT",
        "date": "2026-06-17",
        "net_renames": {"VCC": "+5V"},
        "wirepad_ref_prefix": "TP",
    }
    nets = dict(cfg["net_renames"])
    cfg.update(extra)
    if "net_renames" in extra:
        nets.update(extra["net_renames"])
        cfg["net_renames"] = nets
    return cfg


# Production (TH) boards paired with the redrawn KiCad schematics.
MODULES = {
    "Abort_Module": pcb(
        "Executive Functions Modules/Abort_Module_(TH).json",
        title="ABORT MODULE",
        date="2026-06-17",
        rev="1.7",
        company="UNTITLED SPACE CRAFT",
        ref_renames={"R1-10K": "R1", "R2-1.2K": "R2"},
        net_renames={"VCC": "+5V"},
        values={"R1": "10K", "R2": "1.2K", "C1": "C104", "U1": "ATtiny25"},
        pad_number_map={"R1": {"4": "1", "5": "2"}, "R2": {"4": "1", "5": "2"}},
        number_empty_pads=["C1"],
        empty_fp_names={"R1": "TH_RES_10mm", "R2": "TH_RES_10mm", "C1": "TH_CAP_5mm"},
        wirepad_ref_prefix="TP",
    ),
    "Action_Groups_Module": pcb("Action Module/Action_Groups_Module_(TH).json"),
    "Analog_Module": pcb(
        "Analog Modules/Analog_Module_(TH).json",
        ref_renames={"U2": "U4"},
    ),
    "Analog_Throttle_Module": pcb(
        "Analog Modules/Analog_Throttle_Module_(TH).json",
        ref_renames={"U2": "U4"},
    ),
    "Camera_Module": pcb("Camera Module/Camera_Module_(TH).json"),
    "Control_Systems_Module": pcb("Control Systems Module/Control_Systems_Module_(TH).json"),
    "EVA_Module": pcb("EVA Module/EVA_Module_(TH).json"),
    "Executive_Actions_G_C_Module": pcb(
        "Executive Functions Modules/Executive_Actions_GroupControl_Module_(TH) copy.json"
    ),
    "Executive_Actions_Module": pcb(
        "Executive Functions Modules/Stage_Abort_Module_(TH).json",
        title="EXECUTIVE ACTIONS MODULE",
        date="2026-06-17",
        rev="1.7",
        company="UNTITLED SPACE CRAFT",
        ref_renames={
            "R1-10K": "R1",
            "R2-1.2K": "R2",
            "R3-300": "R3",
            "R4-10K": "R4",
        },
        net_renames={"VCC": "+5V"},
        values={
            "R1": "10K",
            "R2": "1.2K",
            "R3": "300",
            "R4": "10K",
            "C1": "C104",
            "U1": "ATtiny25",
        },
        pad_number_map={
            "R1": {"4": "1", "5": "2"},
            "R2": {"4": "1", "5": "2"},
            "R3": {"4": "1", "5": "2"},
            "R4": {"4": "1", "5": "2"},
        },
        number_empty_pads=["C1"],
        empty_fp_names={
            "R1": "TH_RES_10mm",
            "R2": "TH_RES_10mm",
            "R3": "TH_RES_10mm",
            "R4": "TH_RES_10mm",
            "C1": "TH_CAP_5mm",
        },
        wirepad_ref_prefix="TP",
    ),
    "Navigation_Module": pcb("Navigation Module/Navigation_Module_(TH).json"),
    "Navigation_Time_Module": pcb("Navigation(Time) Module/Navigation_Time_Module_(TH) copy.json"),
    "Octo_Hub": pcb("Arduino Docks/Octo_Socket.json", ref_renames={"J1": "A1"}),
    "Quad_Hub": pcb("Arduino Docks/Quad_Socket.json", ref_renames={"J1": "A1"}),
    "Rotation_Module": pcb(
        "Analog Modules/Rotation_Module_(TH).json",
        ref_renames={"U2": "U4"},
    ),
    "Rotation_Throttle_Module": pcb("Analog Modules/Rotation_Throttle_Module_(TH).json"),
    "Stage_Module": pcb(
        "Executive Functions Modules/Stage Module(TH).json",
        title="STAGE MODULE",
        date="2026-06-17",
        rev="1.7",
        company="UNTITLED SPACE CRAFT",
        ref_renames={"R1-10K": "R1", "R2-150": "R2"},
        net_renames={"VCC": "+5V"},
        values={"R1": "10K", "R2": "150", "C1": "C104", "U1": "ATtiny25"},
        pad_number_map={"R1": {"4": "1", "5": "2"}, "R2": {"4": "1", "5": "2"}},
        number_empty_pads=["C1"],
        empty_fp_names={"R1": "TH_RES_10mm", "R2": "TH_RES_10mm", "C1": "TH_CAP_5mm"},
        wirepad_ref_prefix="TP",
    ),
    "Telemetry_Module": pcb(
        "Digital Telemetry Module/PCB_Digital Telemetry Module.json",
        title="TELEMETRY MODULE",
        date="2026-06-17",
        rev="1.7",
        company="UNTITLED SPACE CRAFT",
        ref_renames={"J1": "A1"},
        net_renames={"VCC": "+5V"},
        wirepad_ref_prefix="TP",
    ),
    "Throttle_Module": pcb("Throttle Module/PCB_Throttle Module.json"),
    "Time_Module": pcb("Time Module/Time_Module_(TH).json"),
    "Translation_Module": pcb("Analog Modules/Translation_Module_(TH).json"),
    "Utility_Navigation_Module": pcb("EVA Module/Utility_Navigation_Module_(TH).json"),
    "Utility_Time_Module": pcb("EVA Module/Utility_Time_Module_(TH).json"),
}


def find_kicad_cli() -> list[str]:
    direct = shutil.which("kicad-cli")
    if direct:
        return [direct]
    if shutil.which("flatpak"):
        return ["flatpak", "run", "--command=kicad-cli", "org.kicad.KiCad"]
    raise SystemExit("kicad-cli not found (install KiCad or the org.kicad.KiCad Flatpak)")


def run_kicad(cli: list[str], args: list[str]) -> None:
    cmd = cli + args
    print("+", " ".join(cmd))
    subprocess.run(cmd, check=True)


def split_top_items(body: str) -> list[str]:
    """Split a kicad_pcb body into top-level s-expr items, preserving text."""
    items: list[str] = []
    i = 0
    n = len(body)
    while i < n:
        if body[i].isspace():
            i += 1
            continue
        if body[i] != "(":
            raise ValueError(f"expected '(' at {i}: {body[i:i+40]!r}")
        depth = 0
        j = i
        while j < n:
            ch = body[j]
            if ch == '"':
                j += 1
                while j < n:
                    if body[j] == "\\":
                        j += 2
                        continue
                    if body[j] == '"':
                        j += 1
                        break
                    j += 1
                continue
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    j += 1
                    break
            j += 1
        items.append(body[i:j])
        i = j
    return items


def item_head(item: str) -> str:
    m = re.match(r"\((\S+)", item)
    return m.group(1) if m else ""


def property_value(item: str, name: str) -> str | None:
    m = re.search(rf'\(property "{re.escape(name)}" "([^"]*)"', item)
    return m.group(1) if m else None


def replace_property(item: str, name: str, new_value: str) -> str:
    return re.sub(
        rf'(\(property "{re.escape(name)}" )"([^"]*)"',
        rf'\1"{new_value}"',
        item,
        count=1,
    )


def hide_property(item: str, name: str) -> str:
    pattern = re.compile(
        rf'(\(property "{re.escape(name)}" "[^"]*"\n'
        rf'(?:\t+\([^\n]+\)\n)*?'
        rf'\t+\(layer "[^"]+"\)\n)'
        rf'(\t+\(hide yes\)\n)?'
    )

    def repl(match: re.Match[str]) -> str:
        if match.group(2):
            return match.group(0)
        return match.group(1) + "\t\t\t(hide yes)\n"

    return pattern.sub(repl, item, count=1)


def is_wire_pad(ref: str, fp_name: str) -> bool:
    short = short_fp_name(fp_name)
    return short in {"WirePad", "WPAD-1-PTH-30AWG"} or ref.startswith(("WP", "TP_"))


def is_resistor(ref: str, fp_name: str) -> bool:
    short = short_fp_name(fp_name)
    return bool(re.match(r"^R\d", ref)) or "TH_RES" in short


def is_capacitor(ref: str, fp_name: str) -> bool:
    short = short_fp_name(fp_name)
    return bool(re.match(r"^C(\d|-)", ref)) or "TH_CAP" in short or "CAP-D" in short


def tidy_footprint_silk(item: str, cfg: dict) -> str:
    ref = property_value(item, "Reference") or ""
    fp_name = re.match(r'\(footprint "([^"]*)"', item).group(1)
    if is_wire_pad(ref, fp_name):
        item = hide_property(item, "Reference")
        item = hide_property(item, "Value")
    if re.match(r"^U\d+$", ref):
        item = hide_property(item, "Value")
    if is_capacitor(ref, fp_name):
        item = hide_property(item, "Value")
    if is_resistor(ref, fp_name):
        value = property_value(item, "Value") or ""
        if value and not value.startswith("- "):
            item = replace_property(item, "Value", f"- {value}")
    value = property_value(item, "Value") or ""
    if re.search(r"WPAD|PDIP-|CAP-D|^DIP-", value):
        item = hide_property(item, "Value")
    return item


MIN_TEXT_HEIGHT = 0.8
RESISTOR_DASH_WIDTH = 0.32
RESISTOR_DASH_HEIGHT = 0.37
RESISTOR_DASH_RADIUS_MM = 12.0
DASH_TEXT_RE = re.compile(r"^[\s\-–—]+$")


def is_dash_silk(item: str) -> bool:
    if item_head(item) != "gr_text":
        return False
    m = re.match(r'\(gr_text "([^"]*)"', item)
    return bool(m and DASH_TEXT_RE.match(m.group(1)))


def item_xy(item: str) -> tuple[float, float] | None:
    m = re.search(r"\n\t\t\(at ([-\d.]+) ([-\d.]+)", item)
    if m:
        return float(m.group(1)), float(m.group(2))
    m = re.search(r"\(at ([-\d.]+) ([-\d.]+)", item)
    return (float(m.group(1)), float(m.group(2))) if m else None


def resistor_positions(items: list[str]) -> list[tuple[float, float]]:
    pts: list[tuple[float, float]] = []
    for item in items:
        if item_head(item) != "footprint":
            continue
        ref = property_value(item, "Reference") or ""
        fp_name = re.match(r'\(footprint "([^"]*)"', item).group(1)
        if not is_resistor(ref, fp_name):
            continue
        xy = item_xy(item)
        if xy:
            pts.append(xy)
    return pts


def near_any(xy: tuple[float, float], pts: list[tuple[float, float]], radius: float) -> bool:
    return any(math.hypot(xy[0] - px, xy[1] - py) <= radius for px, py in pts)


def set_gr_text_size(item: str, width: float, height: float) -> str:
    return re.sub(
        r"\(size [\d.]+ [\d.]+\)",
        f"(size {width:.2f} {height:.2f})",
        item,
        count=1,
    )


def bump_gr_text_height(item: str) -> str:
    if item_head(item) != "gr_text":
        return item

    def size_repl(match: re.Match[str]) -> str:
        width, height = float(match.group(1)), float(match.group(2))
        return f"(size {max(width, MIN_TEXT_HEIGHT):.2f} {max(height, MIN_TEXT_HEIGHT):.2f})"

    item = re.sub(r"\(size ([\d.]+) ([\d.]+)\)", size_repl, item, count=1)
    size_m = re.search(r"\(size ([\d.]+) ([\d.]+)\)", item)
    max_thick = float(size_m.group(2)) * 0.25 if size_m else 0.2

    def thick_repl(match: re.Match[str]) -> str:
        thick = min(max(float(match.group(1)), 0.08), max_thick)
        return f"(thickness {thick:.2f})"

    return re.sub(r"\(thickness ([\d.]+)\)", thick_repl, item, count=1)


def cleanup_board_graphics(items: list[str]) -> list[str]:
    res_pts = resistor_positions(items)
    cleaned: list[str] = []
    for item in items:
        if is_dash_silk(item):
            xy = item_xy(item)
            if xy and near_any(xy, res_pts, RESISTOR_DASH_RADIUS_MM):
                item = set_gr_text_size(item, RESISTOR_DASH_WIDTH, RESISTOR_DASH_HEIGHT)
        elif item_head(item) == "gr_text":
            item = bump_gr_text_height(item)
        cleaned.append(item)
    return cleaned


def set_footprint_name(item: str, name: str) -> str:
    return re.sub(r'^\(footprint "[^"]*"', f'(footprint "{name}"', item, count=1)


def pad_renumber(item: str, mapping: dict[str, str]) -> str:
    def repl(m: re.Match[str]) -> str:
        old = m.group(1)
        return f'(pad "{mapping.get(old, old)}"'

    return re.sub(r'\(pad "([^"]*)"', repl, item)


def number_empty_pads(item: str) -> str:
    n = 0

    def repl(m: re.Match[str]) -> str:
        nonlocal n
        if m.group(1) != "":
            return m.group(0)
        n += 1
        return f'(pad "{n}"'

    return re.sub(r'\(pad "([^"]*)"', repl, item)


def _strip_named_block(item: str, name: str) -> str:
    token = f"({name}"
    start = item.find(token)
    while start != -1:
        if start > 0 and not item[start - 1].isspace() and item[start - 1] != "\n":
            start = item.find(token, start + 1)
            continue
        depth = 0
        j = start
        while j < len(item):
            ch = item[j]
            if ch == '"':
                j += 1
                while j < len(item):
                    if item[j] == "\\":
                        j += 2
                        continue
                    if item[j] == '"':
                        j += 1
                        break
                    j += 1
                continue
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    j += 1
                    break
            j += 1
        before = item[:start]
        after = item[j:]
        if before.endswith("\n") and after.startswith("\n"):
            after = after[1:]
        item = before + after
        start = item.find(token)
    return item


def normalize_custom_pad(pad: str) -> str:
    """Turn EasyEDA custom pads with a 0-size anchor into normal rect pads.

    KiCad zone refill uses the pad size for thermal spokes. EasyEDA imports
    square PTH pads as custom polygons with size 0.000001, so GND/+5V pours
    isolate those pads after a refill.
    """
    if " thru_hole custom" not in pad[:120]:
        return pad
    size_m = re.search(r"\(size ([0-9.]+) ([0-9.]+)\)", pad)
    if not size_m:
        return pad
    if float(size_m.group(1)) > 0.05 or float(size_m.group(2)) > 0.05:
        return pad
    if pad.count("(gr_poly") != 1:
        return pad
    pts = [(float(x), float(y)) for x, y in re.findall(r"\(xy ([-\d.]+) ([-\d.]+)\)", pad)]
    if len(pts) != 4:
        return pad
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    minx, maxx = min(xs), max(xs)
    miny, maxy = min(ys), max(ys)
    corners = {(minx, miny), (minx, maxy), (maxx, miny), (maxx, maxy)}
    if not all(min(abs(px - cx) + abs(py - cy) for cx, cy in corners) < 0.02 for px, py in pts):
        return pad
    width = maxx - minx
    height = maxy - miny
    if width < 0.2 or height < 0.2:
        return pad
    cx = (minx + maxx) / 2
    cy = (miny + maxy) / 2
    at_m = re.search(r"\(at ([-\d.]+) ([-\d.]+)(?: ([-\d.]+))?\)", pad)
    if at_m and (abs(cx) > 0.02 or abs(cy) > 0.02):
        angle = float(at_m.group(3) or 0)
        dx, dy = cx, cy
        if angle:
            rad = math.radians(angle)
            dx = cx * math.cos(rad) - cy * math.sin(rad)
            dy = cx * math.sin(rad) + cy * math.cos(rad)
        new_at = f'(at {float(at_m.group(1)) + dx:.4f} {float(at_m.group(2)) + dy:.4f}'
        if at_m.group(3):
            new_at += f" {at_m.group(3)}"
        new_at += ")"
        pad = pad[: at_m.start()] + new_at + pad[at_m.end() :]
    pad = pad.replace(" thru_hole custom", " thru_hole rect", 1)
    pad = re.sub(
        r"\(size [0-9.]+ [0-9.]+\)",
        f"(size {width:.4f} {height:.4f})",
        pad,
        count=1,
    )
    pad = _strip_named_block(pad, "options")
    pad = _strip_named_block(pad, "primitives")
    return pad


def normalize_footprint_pads(item: str) -> str:
    if item_head(item) != "footprint":
        return item
    nl = item.find("\n")
    end = item.rfind(")")
    if nl < 0 or end < 0:
        return item
    children = split_top_items(item[nl + 1 : end])
    fixed: list[str] = []
    for ch in children:
        if item_head(ch) == "pad":
            ch = normalize_custom_pad(ch)
            ch = re.sub(r"\n(?:[ \t]*\n)+", "\n", ch)
        if not ch.startswith("\t"):
            ch = "\t\t" + ch
        fixed.append(ch)
    return item[: nl + 1] + "\n".join(fixed) + "\n" + item[end:]


def fix_zone_thermals(item: str) -> str:
    """KiCad cannot draw thermal spokes when spoke width == min thickness."""
    if item_head(item) != "zone":
        return item
    if '(net "' not in item:
        return item
    item = re.sub(
        r"\(connect_pads\n(\t+)\(clearance",
        r"(connect_pads yes\n\1(clearance",
        item,
        count=1,
    )
    thick_m = re.search(r"\(min_thickness ([0-9.]+)\)", item)
    spoke_m = re.search(r"\(thermal_bridge_width ([0-9.]+)\)", item)
    if thick_m and spoke_m:
        thick = float(thick_m.group(1))
        spoke = float(spoke_m.group(1))
        if spoke <= thick:
            item = (
                item[: spoke_m.start()]
                + f"(thermal_bridge_width {thick + 0.1:.3f})"
                + item[spoke_m.end() :]
            )
    return item


def insert_after_uuid(item: str, extra: str) -> str:
    if "(path " in item:
        return item
    return re.sub(r'(\(uuid "[^"]+"\)\n)', rf"\1{extra}", item, count=1)


def parse_schematic_symbols(sch_text: str) -> tuple[str, dict[str, dict[str, str]]]:
    sheet_uuid = re.search(r'\(uuid "([^"]+)"\)', sch_text).group(1)
    symbols: dict[str, dict[str, str]] = {}
    # Instance symbols are top-level (one tab), not the lib_symbols copies.
    for m in re.finditer(
        r'\n\t\(symbol\n'
        r'\t\t\(lib_id "([^"]+)"\)\n'
        r'.*?\n\t\t\(uuid "([^"]+)"\)\n'
        r'\t\t\(property "Reference" "([^"]+)"',
        sch_text,
        re.S,
    ):
        lib_id, uuid, ref = m.group(1), m.group(2), m.group(3)
        if ref.startswith("#PWR") or ref.startswith("#FLG"):
            continue
        after = sch_text[m.end() : m.end() + 1500]
        val_m = re.search(r'\(property "Value" "([^"]*)"', after)
        symbols[ref] = {
            "uuid": uuid,
            "lib_id": lib_id,
            "value": val_m.group(1) if val_m else "",
        }
    return sheet_uuid, symbols


def _ref_kind(ref: str) -> str:
    m = re.match(r"^([A-Z]+)", ref)
    return m.group(1) if m else ref


def infer_ref_renames(pcb_refs: set[str], sch_refs: set[str], explicit: dict[str, str]) -> dict[str, str]:
    renames = dict(explicit)
    mapped_sch = set(renames.values())
    skip = ("WP", "TP", "Pad", "NONE", "WIRE", "AREF")
    for pref in pcb_refs:
        if pref in sch_refs or pref in renames:
            continue
        m = re.match(r"^([A-Z]+\d+)-.+$", pref)
        if m and m.group(1) in sch_refs:
            renames[pref] = m.group(1)
            mapped_sch.add(m.group(1))
            continue
        if pref.endswith("1") and pref[:-1] in sch_refs:
            renames[pref] = pref[:-1]
            mapped_sch.add(pref[:-1])
            continue
        if pref + "1" in sch_refs:
            renames[pref] = pref + "1"
            mapped_sch.add(pref + "1")

    pcb_left = {
        r
        for r in pcb_refs
        if r not in sch_refs and r not in renames and not r.startswith(skip)
    }
    sch_left = {r for r in sch_refs if r not in pcb_refs and r not in mapped_sch}
    pcb_g: dict[str, list[str]] = defaultdict(list)
    sch_g: dict[str, list[str]] = defaultdict(list)
    for r in pcb_left:
        pcb_g[_ref_kind(r)].append(r)
    for r in sch_left:
        if r.startswith(("J", "SW", "JOY", "POT", "RV", "D")):
            continue
        sch_g[_ref_kind(r)].append(r)
    for kind, prefs in pcb_g.items():
        srefs = sch_g.get(kind, [])
        if len(prefs) == 1 and len(srefs) == 1:
            renames[prefs[0]] = srefs[0]
    return renames


def infer_title_rev(pcb_text: str, cfg: dict) -> dict:
    cfg = dict(cfg)
    if cfg.get("title") and cfg.get("rev"):
        return cfg
    for text in re.findall(r'\(gr_text "([^"]+)"', pcb_text):
        if "MODULE" not in text.upper() and "HUB" not in text.upper():
            continue
        m = re.match(r"^(.+?)\s+(?:\((?:TH|STH)\)\s+)?v([\d.]+)\s*$", text, re.I)
        if m:
            cfg.setdefault("title", m.group(1).strip())
            cfg.setdefault("rev", m.group(2))
            break
        cfg.setdefault("title", text.strip())
    return cfg


def prepare_cfg(cfg: dict, pcb_text: str, pcb_refs: set[str], sch_symbols: dict[str, dict[str, str]]) -> dict:
    cfg = infer_title_rev(pcb_text, cfg)
    cfg["ref_renames"] = infer_ref_renames(pcb_refs, set(sch_symbols), cfg.get("ref_renames", {}))
    values = dict(cfg.get("values", {}))
    for pref in pcb_refs:
        ref = cfg["ref_renames"].get(pref, pref)
        if ref in values:
            continue
        sch_val = (sch_symbols.get(ref) or {}).get("value") or ""
        if sch_val and (re.match(r"^[RCU]\d", ref) or ref.startswith("C-") or re.match(r"^U\d+$", ref)):
            values[ref] = sch_val
    cfg["values"] = values
    return cfg


def set_schematic_footprint(sch_text: str, uuid: str, footprint: str) -> str:
    pattern = (
        rf'(\(uuid "{re.escape(uuid)}"\)\n'
        rf'.*?\(property "Footprint" )"([^"]*)"'
    )
    return re.sub(pattern, rf'\1"{footprint}"', sch_text, count=1, flags=re.S)


def short_fp_name(name: str) -> str:
    return name.split(":", 1)[-1]


def prefixed_fp_name(name: str) -> str:
    short = short_fp_name(name)
    return f"{FP_LIB_NAME}:{short}" if short else name


def footprint_to_mod(item: str) -> tuple[str, str]:
    name = short_fp_name(re.match(r'\(footprint "([^"]*)"', item).group(1))
    item = set_footprint_name(item, name)
    item = re.sub(r"\n\t\t\(locked yes\)", "", item, count=1)
    item = re.sub(r'\n\t\t\(path "[^"]*"\)', "", item, count=1)
    item = re.sub(r'\n\t\t\(sheetname "[^"]*"\)', "", item, count=1)
    item = re.sub(r'\n\t\t\(sheetfile "[^"]*"\)', "", item, count=1)
    item = re.sub(r"\n\t\t\(at [^\n]+\)", "", item, count=1)
    item = re.sub(r'\n\t\t\t\(net "[^"]*"\)', "", item)
    item = replace_property(item, "Reference", "REF**")
    item = replace_property(item, "Value", name)
    if name in {"WirePad", "WPAD-1-PTH-30AWG"}:
        item = hide_property(item, "Reference")
        item = hide_property(item, "Value")
    header = (
        f'(footprint "{name}"\n'
        "\t(version 20260206)\n"
        '\t(generator "pcbnew")\n'
        '\t(generator_version "10.0")\n'
    )
    item = re.sub(r'^\(footprint "[^"]*"\n', header, item, count=1)
    return name, item


def write_fp_lib_table(path: Path) -> None:
    path.write_text(
        "(fp_lib_table\n"
        "  (version 7)\n"
        f'  (lib (name "{FP_LIB_NAME}")(type "KiCad")'
        f'(uri "${{KIPRJMOD}}/../{FP_LIB_NAME}.pretty")(options "")'
        '(descr "Footprints imported from EasyEDA PCBs"))\n'
        ")\n"
    )


def module_dir(name: str) -> Path:
    return KICAD_DIR / name


def locate_schematic(name: str) -> Path:
    candidates = [
        module_dir(name) / f"{name}.kicad_sch",
        KICAD_DIR / f"{name}.kicad_sch",
        LEGACY_KICAD_DIR / name / f"{name}.kicad_sch",
        LEGACY_KICAD_DIR / f"{name}.kicad_sch",
    ]
    for path in candidates:
        if path.exists():
            return path
    raise SystemExit(f"schematic not found for {name}")


def _is_git_tracked(path: Path) -> bool:
    result = subprocess.run(
        ["git", "-C", str(ROOT), "ls-files", "--error-unmatch", str(path.relative_to(ROOT))],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return result.returncode == 0


def _move_if_exists(src: Path, dest: Path) -> None:
    if not src.exists() or src.resolve() == dest.resolve():
        return
    dest.parent.mkdir(parents=True, exist_ok=True)
    if dest.exists():
        if dest.is_dir():
            shutil.rmtree(dest)
        else:
            dest.unlink()
    if _is_git_tracked(src):
        subprocess.run(["git", "-C", str(ROOT), "mv", "-f", str(src), str(dest)], check=True)
    else:
        shutil.move(str(src), str(dest))


def ensure_project_dir(name: str) -> Path:
    dest = module_dir(name)
    dest.mkdir(parents=True, exist_ok=True)
    search_roots = [KICAD_DIR, LEGACY_KICAD_DIR]
    for root in search_roots:
        for suffix in (".kicad_sch", ".kicad_pcb", ".kicad_pro", ".kicad_prl"):
            _move_if_exists(root / f"{name}{suffix}", dest / f"{name}{suffix}")
        _move_if_exists(root / f"{name}-backups", dest / f"{name}-backups")
        nested = root / name
        if nested.is_dir() and nested.resolve() != dest.resolve():
            for item in nested.iterdir():
                _move_if_exists(item, dest / item.name)
            if not any(nested.iterdir()):
                nested.rmdir()
    return dest


def organize_projects() -> None:
    KICAD_DIR.mkdir(parents=True, exist_ok=True)
    pretty_legacy = LEGACY_KICAD_DIR / f"{FP_LIB_NAME}.pretty"
    if pretty_legacy.is_dir():
        _move_if_exists(pretty_legacy, FP_LIB_DIR)

    names: set[str] = set()
    for root in (KICAD_DIR, LEGACY_KICAD_DIR):
        if not root.is_dir():
            continue
        names.update(p.stem for p in root.glob("*.kicad_sch"))
        names.update(
            p.name
            for p in root.iterdir()
            if p.is_dir() and (p / f"{p.name}.kicad_sch").exists()
        )

    for name in sorted(names):
        dest = ensure_project_dir(name)
        sch = dest / f"{name}.kicad_sch"
        pro = dest / f"{name}.kicad_pro"
        if sch.exists() and not pro.exists():
            sheet_uuid, _ = parse_schematic_symbols(sch.read_text())
            write_project(pro, sheet_uuid, name)
        write_fp_lib_table(dest / "fp-lib-table")
        print(f"organized {dest.relative_to(ROOT)}/")

    for root in (KICAD_DIR, LEGACY_KICAD_DIR):
        table = root / "fp-lib-table"
        if table.exists():
            table.unlink()
            print(f"removed {table.relative_to(ROOT)}")
    if LEGACY_KICAD_DIR.is_dir() and not any(LEGACY_KICAD_DIR.iterdir()):
        LEGACY_KICAD_DIR.rmdir()
        print(f"removed empty {LEGACY_KICAD_DIR.relative_to(ROOT)}")


def write_project(pro_path: Path, sheet_uuid: str, sheet_name: str) -> None:
    data = {
        "board": {"design_settings": {"defaults": {}, "diff_pair_dimensions": [], "drc_exclusions": [], "rules": {}, "track_widths": [], "via_dimensions": []}},
        "boards": [],
        "libraries": {"pinned_footprint_libs": [], "pinned_symbol_libs": []},
        "meta": {"filename": pro_path.name, "version": 3},
        "net_settings": {"classes": [], "meta": {"version": 0}},
        "pcbnew": {"page_layout_descr_file": ""},
        "schematic": {
            "top_level_sheets": [
                {
                    "filename": f"{sheet_name}.kicad_sch",
                    "name": sheet_name,
                    "uuid": sheet_uuid,
                }
            ]
        },
        "sheets": [[sheet_uuid, sheet_name]],
        "text_variables": {},
    }
    pro_path.write_text(json.dumps(data, indent=2) + "\n")


def link_board(pcb_text: str, cfg: dict, sheet_uuid: str, sch_symbols: dict[str, dict[str, str]], sch_name: str) -> str:
    m = re.match(r"\(kicad_pcb\n(.*)\n\)\s*\Z", pcb_text, re.S)
    if not m:
        raise ValueError("unexpected kicad_pcb wrapper")
    items = split_top_items(m.group(1))

    title = cfg.get("title") or sch_name.replace("_", " ")
    title_block = (
        "(title_block\n"
        f'\t\t(title "{title}")\n'
        f'\t\t(date "{cfg.get("date", "")}")\n'
        f'\t\t(rev "{cfg.get("rev", "1.7")}")\n'
        f'\t\t(company "{cfg.get("company", "UNTITLED SPACE CRAFT")}")\n'
        "\t)"
    )

    new_items: list[str] = []
    for item in items:
        head = item_head(item)
        if head == "paper":
            new_items.append(item)
            new_items.append(title_block)
            continue
        if head != "footprint":
            # Board-level net rename (tracks, zones, vias, pads inside footprints handled below)
            for old, new in cfg.get("net_renames", {}).items():
                item = item.replace(f'(net "{old}")', f'(net "{new}")')
            new_items.append(item)
            continue

        for old, new in cfg.get("net_renames", {}).items():
            item = item.replace(f'(net "{old}")', f'(net "{new}")')

        ref = property_value(item, "Reference") or ""
        fp_name = re.match(r'\(footprint "([^"]*)"', item).group(1)

        if ref in cfg.get("ref_renames", {}):
            new_ref = cfg["ref_renames"][ref]
            item = replace_property(item, "Reference", new_ref)
            ref = new_ref

        if ref.startswith("Pad_gge"):
            net_m = re.search(r'\(net "([^"]+)"\)', item)
            net = net_m.group(1) if net_m else ref
            safe = re.sub(r"[^A-Za-z0-9_+-]", "_", net)
            prefix = cfg.get("wirepad_ref_prefix", "TP")
            item = replace_property(item, "Reference", f"{prefix}_{safe}")
            item = replace_property(item, "Value", "WirePad")
            item = set_footprint_name(item, "WirePad")
            ref = f"{prefix}_{safe}"
            fp_name = "WirePad"

        if ref in cfg.get("values", {}):
            item = replace_property(item, "Value", cfg["values"][ref])
        elif ref in sch_symbols:
            sch_val = sch_symbols[ref].get("value") or ""
            if sch_val and (re.match(r"^[RCU]\d", ref) or ref.startswith("C-") or re.match(r"^U\d+$", ref)):
                item = replace_property(item, "Value", sch_val)

        pad_nums = re.findall(r'\(pad "([^"]*)"', item)
        if ref in cfg.get("pad_number_map", {}):
            item = pad_renumber(item, cfg["pad_number_map"][ref])
        elif is_resistor(ref, fp_name) and pad_nums and set(pad_nums) <= {"4", "5"}:
            item = pad_renumber(item, {"4": "1", "5": "2"})

        if ref in cfg.get("number_empty_pads", []):
            item = number_empty_pads(item)
        elif is_capacitor(ref, fp_name) and pad_nums and all(n == "" for n in pad_nums):
            item = number_empty_pads(item)

        if not fp_name and ref in cfg.get("empty_fp_names", {}):
            fp_name = cfg["empty_fp_names"][ref]
            item = set_footprint_name(item, fp_name)
        elif not fp_name:
            if is_resistor(ref, fp_name):
                fp_name = "TH_RES_10mm"
                item = set_footprint_name(item, fp_name)
            elif is_capacitor(ref, fp_name):
                fp_name = "TH_CAP_5mm"
                item = set_footprint_name(item, fp_name)

        if ref in sch_symbols:
            sym = sch_symbols[ref]
            extra = (
                f'\t\t(path "/{sheet_uuid}/{sym["uuid"]}")\n'
                f'\t\t(sheetname "/")\n'
                f'\t\t(sheetfile "{sch_name}.kicad_sch")\n'
            )
            item = insert_after_uuid(item, extra)

        item = tidy_footprint_silk(item, cfg)
        new_items.append(item)

    body = "\n\t".join(new_items)
    return f"(kicad_pcb\n\t{body}\n)\n"


def cleanup_pcb_silk(name: str) -> None:
    if name not in MODULES:
        raise SystemExit(f"unknown module {name!r}. known: {', '.join(MODULES)}")
    cfg = MODULES[name]
    pcb_path = module_dir(name) / f"{name}.kicad_pcb"
    if not pcb_path.is_file():
        raise SystemExit(f"PCB not found: {pcb_path}")
    text = pcb_path.read_text()
    match = re.match(r"\(kicad_pcb\n(.*)\n\)\s*\Z", text, re.S)
    if not match:
        raise ValueError("unexpected kicad_pcb wrapper")
    new_items: list[str] = []
    hidden = 0
    for item in split_top_items(match.group(1)):
        if item_head(item) == "footprint":
            ref = property_value(item, "Reference") or ""
            if ref in cfg.get("values", {}):
                item = replace_property(item, "Value", cfg["values"][ref])
            before = item
            item = tidy_footprint_silk(item, cfg)
            if item != before:
                hidden += 1
        new_items.append(item)
    before_n = len(new_items)
    new_items = cleanup_board_graphics(new_items)
    pcb_path.write_text("(kicad_pcb\n\t" + "\n\t".join(new_items) + "\n)\n")
    print(f"Cleaned silk on {hidden} footprints in {pcb_path.relative_to(ROOT)}")
    print(f"Normalized board graphics ({before_n} -> {len(new_items)} items)")


def repair_zone_connections(name: str) -> None:
    pcb_path = module_dir(name) / f"{name}.kicad_pcb"
    if not pcb_path.is_file():
        raise SystemExit(f"PCB not found: {pcb_path}")
    text = pcb_path.read_text()
    match = re.match(r"\(kicad_pcb\n(.*)\n\)\s*\Z", text, re.S)
    if not match:
        raise ValueError("unexpected kicad_pcb wrapper")
    pads = 0
    zones = 0
    new_items: list[str] = []
    for item in split_top_items(match.group(1)):
        if item_head(item) == "footprint":
            before = item
            item = normalize_footprint_pads(item)
            if item != before:
                pads += item.count(" thru_hole rect") - before.count(" thru_hole rect")
        elif item_head(item) == "zone":
            before = item
            item = fix_zone_thermals(item)
            if item != before:
                zones += 1
        new_items.append(item)
    pcb_path.write_text("(kicad_pcb\n\t" + "\n\t".join(new_items) + "\n)\n")
    FP_LIB_DIR.mkdir(exist_ok=True)
    exported: set[str] = set()
    for item in new_items:
        if item_head(item) != "footprint":
            continue
        fp_name = re.match(r'\(footprint "([^"]*)"', item).group(1)
        short = short_fp_name(fp_name)
        if short and short not in exported:
            mod_name, mod_text = footprint_to_mod(item)
            (FP_LIB_DIR / f"{mod_name}.kicad_mod").write_text(mod_text + "\n")
            exported.add(short)
    print(f"Repaired {pads} custom pads and {zones} zones in {pcb_path.relative_to(ROOT)}")


def convert_module(name: str, cli: list[str]) -> None:
    if name not in MODULES:
        raise SystemExit(f"unknown module {name!r}. known: {', '.join(MODULES)}")
    cfg = MODULES[name]
    easyeda = Path(cfg["easyeda"])
    if not easyeda.is_file():
        raise SystemExit(f"EasyEDA file not found: {easyeda}")

    dest = ensure_project_dir(name)
    sch_path = locate_schematic(name)
    if sch_path.parent != dest:
        shutil.move(str(sch_path), str(dest / sch_path.name))
        sch_path = dest / sch_path.name
    pcb_path = dest / f"{name}.kicad_pcb"
    pro_path = dest / f"{name}.kicad_pro"

    run_kicad(
        cli,
        ["pcb", "import", "--format", "auto", "--report-format", "text", "-o", str(pcb_path), str(easyeda)],
    )

    sch_text = sch_path.read_text()
    sheet_uuid, symbols = parse_schematic_symbols(sch_text)
    pcb_text = pcb_path.read_text()
    pcb_items_pre = split_top_items(re.match(r"\(kicad_pcb\n(.*)\n\)\s*\Z", pcb_text, re.S).group(1))
    pcb_refs = {
        property_value(item, "Reference") or ""
        for item in pcb_items_pre
        if item_head(item) == "footprint"
    }
    cfg = prepare_cfg(cfg, pcb_text, pcb_refs, symbols)
    pcb_path.write_text(link_board(pcb_text, cfg, sheet_uuid, symbols, name))

    pcb_linked = pcb_path.read_text()
    pcb_items = cleanup_board_graphics(
        split_top_items(re.match(r"\(kicad_pcb\n(.*)\n\)\s*\Z", pcb_linked, re.S).group(1))
    )
    FP_LIB_DIR.mkdir(exist_ok=True)
    exported: set[str] = set()
    new_items: list[str] = []
    for item in pcb_items:
        if item_head(item) != "footprint":
            new_items.append(fix_zone_thermals(item))
            continue
        item = normalize_footprint_pads(item)
        fp_name = re.match(r'\(footprint "([^"]*)"', item).group(1)
        short = short_fp_name(fp_name)
        if short and short not in exported:
            mod_name, mod_text = footprint_to_mod(item)
            (FP_LIB_DIR / f"{mod_name}.kicad_mod").write_text(mod_text + "\n")
            exported.add(short)
        if short:
            item = set_footprint_name(item, prefixed_fp_name(short))
        ref = property_value(item, "Reference") or ""
        if ref in symbols and short:
            sch_text = set_schematic_footprint(
                sch_text, symbols[ref]["uuid"], prefixed_fp_name(short)
            )
            print(f"  linked {ref}: {prefixed_fp_name(short)} -> {symbols[ref]['uuid']}")
        new_items.append(item)

    pcb_path.write_text("(kicad_pcb\n\t" + "\n\t".join(new_items) + "\n)\n")
    sch_path.write_text(sch_text)
    if not pro_path.exists():
        write_project(pro_path, sheet_uuid, name)
        print(f"Wrote {pro_path.relative_to(ROOT)}")
    else:
        print(f"Kept existing {pro_path.relative_to(ROOT)}")
    write_fp_lib_table(dest / "fp-lib-table")
    print(f"Wrote {pcb_path.relative_to(ROOT)}")
    print(f"Wrote {FP_LIB_DIR.relative_to(ROOT)} ({len(exported)} footprints)")
    print(f"Updated footprints in {sch_path.relative_to(ROOT)}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", nargs="?", default="Stage_Module", help="module name (default: Stage_Module)")
    parser.add_argument("--list", action="store_true", help="list known modules")
    parser.add_argument("--organize", action="store_true", help="move existing KiCad files into per-module folders")
    parser.add_argument(
        "--cleanup-silk",
        action="store_true",
        help="hide wire-pad silk and EasyEDA package names on an existing PCB",
    )
    parser.add_argument(
        "--cleanup-drc",
        action="store_true",
        help="fix undersized silk text on an existing PCB",
    )
    parser.add_argument(
        "--remaining",
        action="store_true",
        help="convert every module except Stage_Module and Abort_Module",
    )
    parser.add_argument(
        "--fix-zones",
        action="store_true",
        help="convert 0-size custom pads to rect pads and fix zone thermal widths",
    )
    args = parser.parse_args()
    if args.list:
        for name, cfg in MODULES.items():
            print(f"{name}: {cfg['easyeda']}")
        return
    if args.organize:
        organize_projects()
        return
    if args.cleanup_silk or args.cleanup_drc:
        cleanup_pcb_silk(args.module)
        return
    if args.fix_zones:
        repair_zone_connections(args.module)
        return
    if args.remaining:
        cli = find_kicad_cli()
        done = {"Abort_Module", "Stage_Module"}
        failed: list[str] = []
        for name in MODULES:
            if name in done:
                continue
            print(f"\n==== {name} ====")
            try:
                convert_module(name, cli)
            except Exception as exc:
                failed.append(f"{name}: {exc}")
                print(f"FAILED {name}: {exc}")
        if failed:
            print("\nFailures:")
            print("\n".join(failed))
            raise SystemExit(1)
        return
    convert_module(args.module, find_kicad_cli())


if __name__ == "__main__":
    main()
