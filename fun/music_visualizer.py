#!/usr/bin/env python3
from __future__ import annotations

import argparse
import html
import shutil
import subprocess
import sys
import time
from functools import lru_cache
from dataclasses import dataclass
from pathlib import Path

import numpy as np


@dataclass(frozen=True)
class Style:
    name: str
    description: str


@dataclass(frozen=True)
class AudioAnalysis:
    band_profile: np.ndarray
    rms: np.ndarray
    onset: np.ndarray
    beat: np.ndarray
    activity: np.ndarray
    low: np.ndarray
    mid: np.ndarray
    high: np.ndarray
    silence: np.ndarray


class RenderProgress:
    def __init__(self, total: int, label: str = "Rendering") -> None:
        self.total = max(1, int(total))
        self.label = label
        self.started = time.monotonic()
        self.last_print = 0.0
        self.spinner = "|/-\\"

    def update(self, count: int) -> None:
        now = time.monotonic()
        if count < self.total and (now - self.last_print) < 0.08:
            return
        self.last_print = now
        elapsed = max(1e-6, now - self.started)
        rate = count / elapsed
        pct = min(100.0, 100.0 * count / self.total)
        filled = int(24 * count / self.total)
        bar = "#" * filled + "-" * (24 - filled)
        spin = self.spinner[count % len(self.spinner)]
        eta = (self.total - count) / rate if rate > 0 and count < self.total else 0.0
        sys.stderr.write(
            f"\r{self.label} {spin} [{bar}] {pct:6.2f}% "
            f"({count}/{self.total}) {rate:5.1f} it/s ETA {eta:5.1f}s"
        )
        sys.stderr.flush()

    def finish(self) -> None:
        elapsed = max(1e-6, time.monotonic() - self.started)
        sys.stderr.write(
            f"\r{self.label} ✓ [{'#' * 24}] 100.00% ({self.total}/{self.total}) "
            f"done in {elapsed:0.1f}s\n"
        )
        sys.stderr.flush()


STYLES: list[Style] = [
    Style(
        name="eclipse",
        description="Polished, buttery-smooth rotating 3-lobe circle",
    ),
    Style(
        name="classic_wave",
        description="Smooth, cinematic layered frequency wave (Trap Nation style)",
    ),
    Style(
        name="cinematic_bars",
        description="Razor-sharp glowing vertical frequency bars (Monstercat style)",
    ),
]


def style_by_name(name: str) -> Style:
    for style in STYLES:
        if style.name == name:
            return style
    raise KeyError(name)


def list_styles() -> None:
    for idx, style in enumerate(STYLES, start=1):
        print(f"{idx}. {style.name} - {style.description}")


def choose_style_interactively() -> Style:
    print("Choose a visualizer style:")
    list_styles()
    while True:
        choice = input(f"Enter 1-{len(STYLES)}: ").strip()
        try:
            index = int(choice)
            if 1 <= index <= len(STYLES):
                return STYLES[index - 1]
        except ValueError:
            pass
        print("Invalid choice, try again.")


def run_osascript(script: str) -> str | None:
    try:
        result = subprocess.run(["osascript", "-e", script], text=True, capture_output=True, check=False)
        return result.stdout.strip() if result.returncode == 0 else None
    except Exception:
        return None


def choose_input_file() -> str | None:
    if sys.platform == "darwin":
        return run_osascript('POSIX path of (choose file with prompt "Choose the audio file to visualize")')
    elif sys.platform == "win32":
        script = (
            "Add-Type -AssemblyName System.Windows.Forms; "
            "$f = New-Object System.Windows.Forms.OpenFileDialog; "
            "$f.Title = 'Choose the audio file to visualize'; "
            "$f.Filter = 'Audio Files|*.mp3;*.wav;*.flac;*.m4a;*.ogg;*.aac|All Files|*.*'; "
            "if ($f.ShowDialog() -eq 'OK') { Write-Output $f.FileName }"
        )
        try:
            res = subprocess.run(["powershell", "-NoProfile", "-Command", script], capture_output=True, text=True)
            return res.stdout.strip() or None
        except Exception:
            return None
    else:
        if shutil.which("zenity"):
            res = subprocess.run(["zenity", "--file-selection", "--title=Choose the audio file to visualize"], capture_output=True, text=True)
            return res.stdout.strip() if res.returncode == 0 else None
        elif shutil.which("kdialog"):
            res = subprocess.run(["kdialog", "--getopenfilename", ".", "Audio Files (*.mp3 *.wav *.flac *.m4a *.ogg)"], capture_output=True, text=True)
            return res.stdout.strip() if res.returncode == 0 else None
    return None


def choose_output_directory(default_dir: Path | None = None) -> str | None:
    if sys.platform == "darwin":
        return run_osascript('POSIX path of (choose folder with prompt "Choose the output folder")')
    elif sys.platform == "win32":
        script = (
            "Add-Type -AssemblyName System.Windows.Forms; "
            "$f = New-Object System.Windows.Forms.FolderBrowserDialog; "
            "$f.Description = 'Choose the output folder'; "
            "if ($f.ShowDialog() -eq 'OK') { Write-Output $f.SelectedPath }"
        )
        try:
            res = subprocess.run(["powershell", "-NoProfile", "-Command", script], capture_output=True, text=True)
            return res.stdout.strip() or None
        except Exception:
            return None
    else:
        if shutil.which("zenity"):
            res = subprocess.run(["zenity", "--file-selection", "--directory", "--title=Choose the output folder"], capture_output=True, text=True)
            return res.stdout.strip() if res.returncode == 0 else None
        elif shutil.which("kdialog"):
            res = subprocess.run(["kdialog", "--getexistingdirectory", "."], capture_output=True, text=True)
            return res.stdout.strip() if res.returncode == 0 else None
    return None


def choose_style_dialog() -> Style | None:
    if sys.platform == "darwin":
        native_items = ", ".join('"' + f"{s.name} - {s.description}" + '"' for s in STYLES)
        native = run_osascript(
            f"set choices to {{{native_items}}}\n"
            'set picked to choose from list choices with prompt "Choose a visualizer style"'
            "\nif picked is false then return \"\"\nreturn item 1 of picked"
        )
        if native:
            return style_by_name(native.split(" - ", 1)[0].strip())
            
    elif sys.platform == "win32":
        items_str = ",".join([f"'{s.name} - {s.description}'" for s in STYLES])
        script = f"""
        Add-Type -AssemblyName System.Windows.Forms
        Add-Type -AssemblyName System.Drawing
        $f = New-Object System.Windows.Forms.Form
        $f.Text = 'Choose a visualizer style'
        $f.Size = New-Object System.Drawing.Size(400,350)
        $f.StartPosition = 'CenterScreen'
        $lbl = New-Object System.Windows.Forms.Label
        $lbl.Text = 'Select a style:'
        $lbl.Dock = 'Top'
        $f.Controls.Add($lbl)
        $lb = New-Object System.Windows.Forms.ListBox
        $lb.Dock = 'Fill'
        $items = @({items_str})
        foreach ($i in $items) {{ $lb.Items.Add($i) | Out-Null }}
        $lb.SelectedIndex = 0
        $f.Controls.Add($lb)
        $btn = New-Object System.Windows.Forms.Button
        $btn.Text = 'OK'
        $btn.Dock = 'Bottom'
        $btn.add_Click({{ $f.DialogResult = 'OK'; $f.Close() }})
        $f.Controls.Add($btn)
        $f.TopMost = $true
        if ($f.ShowDialog() -eq 'OK') {{ Write-Output $lb.SelectedItem }}
        """
        try:
            res = subprocess.run(["powershell", "-NoProfile", "-Command", script], capture_output=True, text=True)
            out = res.stdout.strip()
            if out:
                return style_by_name(out.split(" - ")[0].strip())
        except Exception:
            pass
            
    else: 
        if shutil.which("zenity"):
            cmd = ["zenity", "--list", "--title=Choose a visualizer style", "--text=Select a style:", "--column=Style", "--column=Description"]
            for s in STYLES:
                cmd.extend([s.name, s.description])
            try:
                res = subprocess.run(cmd, capture_output=True, text=True)
                out = res.stdout.strip()
                if out:
                    return style_by_name(out.split('|')[0])
            except Exception:
                pass
        elif shutil.which("kdialog"):
            cmd = ["kdialog", "--menu", "Choose a visualizer style:"]
            for s in STYLES:
                cmd.extend([s.name, s.description])
            try:
                res = subprocess.run(cmd, capture_output=True, text=True)
                out = res.stdout.strip()
                if out:
                    return style_by_name(out)
            except Exception:
                pass

    return None


def decode_audio_pcm(input_path: Path, sample_rate: int = 44100) -> tuple[np.ndarray, int]:
    ffmpeg = shutil.which("ffmpeg")
    if not ffmpeg:
        raise RuntimeError("ffmpeg was not found on PATH.")

    sys.stderr.write("Decoding audio to PCM (this may take a moment)...\n")
    sys.stderr.flush()

    cmd = [
        ffmpeg,
        "-hide_banner",
        "-y",
        "-i",
        str(input_path),
        "-vn",
        "-ac",
        "2",
        "-ar",
        str(sample_rate),
        "-f",
        "f32le",
        "pipe:1",
    ]
    result = subprocess.run(cmd, capture_output=True)
    if result.returncode != 0:
        raise RuntimeError(
            "Failed to decode audio:\n"
            + (result.stderr.decode("utf-8", errors="ignore")[-3000:] if result.stderr else "")
        )

    sys.stderr.write("Audio decoded successfully.\n")
    audio = np.frombuffer(result.stdout, dtype=np.float32)
    if audio.size % 2:
        audio = audio[:-1]
    return audio.reshape(-1, 2), sample_rate


def load_audio_segment(
    input_path: Path,
    sample_rate: int = 44100,
    start_seconds: int | None = None,
    limit_seconds: int | None = None,
) -> tuple[np.ndarray, int]:
    audio, sample_rate = decode_audio_pcm(input_path, sample_rate=sample_rate)
    start_idx = int(start_seconds * sample_rate) if start_seconds else 0
    if limit_seconds is not None:
        end_idx = start_idx + int(limit_seconds * sample_rate)
    else:
        end_idx = len(audio)
    segment = audio[start_idx:end_idx]
    if segment.size == 0:
        raise RuntimeError("No audio samples were available for rendering.")
    return segment, sample_rate


def _normalize_series(
    values: np.ndarray,
    low_pct: float = 8.0,
    high_pct: float = 96.0,
    gamma: float = 1.0,
) -> np.ndarray:
    values = values.astype(np.float32, copy=False)
    if values.size == 0:
        return values
    lo = float(np.percentile(values, low_pct))
    hi = float(np.percentile(values, high_pct))
    if hi - lo < 1e-6:
        return np.zeros_like(values, dtype=np.float32)
    norm = np.clip((values - lo) / (hi - lo), 0.0, 1.0)
    if gamma != 1.0:
        norm = np.power(norm, gamma)
    return norm.astype(np.float32)


def _attack_release(values: np.ndarray, attack: float = 0.42, release: float = 0.90) -> np.ndarray:
    if values.size == 0:
        return values.astype(np.float32, copy=False)
    out = np.empty_like(values, dtype=np.float32)
    prev = 0.0
    for idx, raw_value in enumerate(values.astype(np.float32, copy=False)):
        coeff = attack if raw_value > prev else release
        prev = coeff * prev + (1.0 - coeff) * float(raw_value)
        out[idx] = prev
    return out


def _band_energy_profile(
    spectrum: np.ndarray, band_masks: list[np.ndarray]
) -> np.ndarray:
    profile = np.zeros(len(band_masks), dtype=np.float32)
    for idx, mask in enumerate(band_masks):
        if np.any(mask):
            profile[idx] = float(np.mean(spectrum[mask]))
    return profile


def build_audio_analysis(
    audio: np.ndarray,
    sample_rate: int,
    fps: int,
    band_count: int = 48,
    window_seconds: float = 0.04,
) -> AudioAnalysis:
    mono = audio.mean(axis=1).astype(np.float32, copy=False)
    frame_count = max(1, int(np.ceil(len(mono) / sample_rate * fps)))
    frame_step = sample_rate / fps
    window_samples = max(1024, int(sample_rate * window_seconds))
    n_fft = 1 << int(np.ceil(np.log2(max(window_samples, 2048))))
    freqs = np.fft.rfftfreq(n_fft, d=1.0 / sample_rate)
    band_edges = np.geomspace(20.0, sample_rate / 2.0, band_count + 1)
    band_masks = [
        (freqs >= band_edges[i]) & (freqs < band_edges[i + 1])
        for i in range(band_count)
    ]

    rms = np.zeros(frame_count, dtype=np.float32)
    centroid = np.zeros(frame_count, dtype=np.float32)
    band_profile = np.zeros((frame_count, band_count), dtype=np.float32)

    half = window_samples // 2

    progress = RenderProgress(frame_count, label="Analyzing Audio Structure")

    for frame_idx in range(frame_count):
        center = int(frame_idx * frame_step)
        start = max(0, center - half)
        end = min(len(mono), center + half)
        chunk = mono[start:end]
        if len(chunk) < 32:
            chunk = mono[max(0, len(mono) - 32) :]
        if len(chunk) == 0:
            chunk = np.zeros(window_samples, dtype=np.float32)
        if len(chunk) < window_samples:
            chunk = np.pad(chunk, (0, window_samples - len(chunk)), mode="edge")
            
        windowed = chunk * np.hanning(len(chunk))
        spectrum = np.abs(np.fft.rfft(windowed, n=n_fft)).astype(np.float32)
        spectrum = np.log1p(spectrum)
        rms[frame_idx] = float(np.sqrt(np.mean(chunk * chunk)))
        spec_sum = float(np.sum(spectrum)) + 1e-6
        centroid[frame_idx] = float(np.sum(freqs * spectrum) / spec_sum)
        band_profile[frame_idx] = _band_energy_profile(spectrum, band_masks)

        if frame_idx % 60 == 0:
            progress.update(frame_idx)

    progress.finish()

    band_profile = np.log1p(band_profile)
    band_profile = _normalize_series(band_profile, 6.0, 96.0, gamma=0.90)
    rms_norm = _normalize_series(rms, 5.0, 96.0, gamma=0.86)
    low = band_profile[:, : max(1, band_count // 5)].mean(axis=1)
    mid = band_profile[:, band_count // 5 : max(band_count // 5 + 1, band_count * 3 // 5)].mean(axis=1)
    high = band_profile[:, max(band_count * 3 // 5, 1) :].mean(axis=1)

    onset_raw = np.zeros(frame_count, dtype=np.float32)
    onset_raw[0] = rms_norm[0]
    if frame_count > 1:
        diffs = np.maximum(0.0, np.diff(band_profile, axis=0))
        weights = np.linspace(0.5, 1.5, band_count, dtype=np.float32)
        diffs_weighted = (diffs * weights).sum(axis=1)
        rms_diffs = np.maximum(0.0, np.diff(rms_norm))
        onset_raw[1:] = diffs_weighted + 1.5 * rms_diffs
        onset_raw[0] = float(np.mean(band_profile[0]))
        
    onset = _normalize_series(onset_raw, 2.0, 99.0, gamma=0.70)
    beat = _attack_release(onset, attack=0.30, release=0.60)
    energy = 0.50 * rms_norm + 0.20 * low + 0.10 * mid + 0.20 * onset
    activity = _attack_release(energy, attack=0.35, release=0.65)
    activity = np.clip(activity, 0.0, 1.0)
    silence = np.clip(1.0 - activity * 1.5, 0.0, 1.0)

    return AudioAnalysis(
        band_profile=band_profile.astype(np.float32, copy=False),
        rms=rms_norm.astype(np.float32, copy=False),
        onset=onset.astype(np.float32, copy=False),
        beat=beat.astype(np.float32, copy=False),
        activity=activity.astype(np.float32, copy=False),
        low=low.astype(np.float32, copy=False),
        mid=mid.astype(np.float32, copy=False),
        high=high.astype(np.float32, copy=False),
        silence=silence.astype(np.float32, copy=False),
    )


@lru_cache(maxsize=8)
def load_render_context(
    input_path_str: str,
    sample_rate: int,
    start_seconds: int | None,
    limit_seconds: int | None,
    fps: int,
) -> tuple[np.ndarray, int, AudioAnalysis]:
    audio, sample_rate = load_audio_segment(
        Path(input_path_str),
        sample_rate=sample_rate,
        start_seconds=start_seconds,
        limit_seconds=limit_seconds,
    )
    analysis = build_audio_analysis(audio, sample_rate, fps=fps)
    return audio, sample_rate, analysis


def _smooth_vector(values: np.ndarray, width: int = 9) -> np.ndarray:
    if width <= 1:
        return values
    kernel = np.ones(width, dtype=np.float32) / width
    return np.convolve(values, kernel, mode="same")


def _gaussian_blur_1d(values: np.ndarray, width: int, passes: int = 3) -> np.ndarray:
    if width <= 1: 
        return values
    res = values
    for _ in range(passes):
        res = _smooth_vector(res, width)
    return res


def _smooth_circular(arr: np.ndarray, width: int) -> np.ndarray:
    if width <= 1:
        return arr.astype(np.float32, copy=False)
    pad = width
    padded = np.concatenate([arr[-pad:], arr, arr[:pad]])
    kernel = np.ones(width, dtype=np.float32) / width
    smoothed = np.convolve(padded, kernel, mode="same")
    return smoothed[pad : pad + len(arr)].astype(np.float32)


def _frame_bytes_from_gray(gray: np.ndarray) -> bytes:
    gray = np.clip(gray, 0.0, 1.0)
    rgb = (gray[:, :, None] * 255.0).astype(np.uint8)
    return np.repeat(rgb, 3, axis=2).tobytes()


def _stream_frames_to_ffmpeg(
    cmd: list[str], frame_factory, total_frames: int | None = None, progress_label: str = "Rendering"
) -> subprocess.CompletedProcess[bytes]:
    proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    assert proc.stdin is not None
    progress = RenderProgress(total_frames, label=progress_label) if total_frames else None
    written = 0
    try:
        for frame in frame_factory():
            if isinstance(frame, np.ndarray):
                proc.stdin.write(frame.tobytes())
            else:
                proc.stdin.write(frame)
            written += 1
            if progress is not None:
                progress.update(written)
    except BrokenPipeError:
        pass
    finally:
        try:
            proc.stdin.close()
        except Exception:
            pass
    proc.wait()
    if progress is not None:
        progress.finish()
    stdout = proc.stdout.read() if proc.stdout else b""
    stderr = proc.stderr.read() if proc.stderr else b""
    return subprocess.CompletedProcess(cmd, proc.returncode, stdout, stderr)


def mux_frames_to_video(
    input_path: Path,
    output_path: Path,
    width: int,
    height: int,
    fps: int,
    frame_factory,
    prefer_audio_copy: bool,
    video_preset: str,
    video_crf: str,
    start_seconds: int | None,
    limit_seconds: int | None,
    total_frames: int | None = None,
    progress_label: str = "Encoding",
) -> None:
    ffmpeg = shutil.which("ffmpeg")
    if not ffmpeg:
        raise RuntimeError("ffmpeg was not found on PATH.")

    def build_cmd(audio_mode: str) -> list[str]:
        cmd = [
            ffmpeg,
            "-hide_banner",
            "-y",
            "-f",
            "rawvideo",
            "-pix_fmt",
            "rgb24",
            "-s",
            f"{width}x{height}",
            "-r",
            str(fps),
            "-i",
            "pipe:0",
        ]
        if start_seconds is not None:
            cmd += ["-ss", str(start_seconds)]
        if limit_seconds is not None:
            cmd += ["-t", str(limit_seconds)]
        cmd += [
            "-i",
            str(input_path),
            "-map",
            "0:v",
            "-map",
            "1:a",
            "-c:v",
            "libx264",
            "-preset",
            video_preset,
            "-crf",
            video_crf,
            "-profile:v",
            "high",
            "-pix_fmt",
            "yuv420p",
            "-movflags",
            "+faststart",
            "-shortest",
            "-c:a",
            audio_mode,
        ]
        if audio_mode == "aac":
            cmd += ["-b:a", "320k", "-ar", "48000"]
        cmd += [str(output_path)]
        return cmd

    result = _stream_frames_to_ffmpeg(
        build_cmd("copy" if prefer_audio_copy else "aac"),
        frame_factory,
        total_frames=total_frames,
        progress_label=progress_label,
    )
    if result.returncode == 0:
        return

    if prefer_audio_copy:
        print("\nAudio copy failed, falling back to AAC 320k.", file=sys.stderr)
        result = _stream_frames_to_ffmpeg(build_cmd("aac"), frame_factory, total_frames=total_frames, progress_label=progress_label)
        if result.returncode == 0:
            return

    raise RuntimeError(
        "ffmpeg failed:\n"
        + (result.stderr.decode("utf-8", errors="ignore")[-4000:] if result.stderr else "No stderr captured.")
    )


def render_eclipse_video(
    input_path: Path, output_path: Path, width: int, height: int, fps: int,
    prefer_audio_copy: bool, video_preset: str, video_crf: str, limit_seconds: int | None,
    start_seconds: int | None, visual_gain: float,
) -> None:
    audio, sample_rate, analysis = load_render_context(str(input_path), 44100, start_seconds, limit_seconds, fps)
    total_frames = len(analysis.activity)
    
    points = 1024
    cx, cy = width / 2, height / 2
    base_radius = min(width, height) * 0.22
    
    yy, xx = np.mgrid[:height, :width]
    dx, dy = xx - cx, yy - cy
    radius_grid = np.sqrt(dx*dx + dy*dy).astype(np.float32)
    base_angle_grid = np.mod(np.arctan2(dy, dx) + 2*np.pi, 2*np.pi)

    rotation_speed = 0.02 
    lobe_points = points // 3

    def frames():
        prev_profile = np.zeros(points, dtype=np.float32)
        prev_inner_radius = base_radius
        
        for frame_idx in range(total_frames):
            source = analysis.band_profile[frame_idx] ** 1.8
            
            source = _gaussian_blur_1d(source, 3, passes=2)
            
            lobe = np.concatenate([source[::-1], source])
            lobe_resampled = np.interp(np.linspace(0, 1, lobe_points), np.linspace(0, 1, len(lobe)), lobe)
            
            profile_raw = np.tile(lobe_resampled, 3)
            profile_raw = np.interp(np.linspace(0, 1, points), np.linspace(0, 1, len(profile_raw)), profile_raw)
            
            for _ in range(3):
                profile_raw = _smooth_circular(profile_raw, 15)
            
            profile = np.where(profile_raw > prev_profile,
                               0.3 * prev_profile + 0.7 * profile_raw, 
                               0.8 * prev_profile + 0.2 * profile_raw)
            prev_profile = profile.copy()

            low = float(analysis.low[frame_idx])
            activity = float(analysis.activity[frame_idx])
            
            target_inner = base_radius - (20 * low * visual_gain)
            inner_radius = 0.8 * prev_inner_radius + 0.2 * target_inner
            prev_inner_radius = inner_radius
            
            base_thickness = base_radius * 0.12 + (15 * activity)
            r_outer = inner_radius + base_thickness + (180 * profile * visual_gain)
            
            angle_offset = frame_idx * rotation_speed
            angle_grid = np.mod(base_angle_grid + angle_offset, 2*np.pi)
            angle_idx = (angle_grid * (points / (2*np.pi))).astype(np.int32) % points
            
            target_r_out = r_outer[angle_idx]
            target_r_in = float(inner_radius)
            
            mask_fill = (radius_grid >= target_r_in) & (radius_grid <= target_r_out)
            frame = np.zeros((height, width), dtype=np.float32)
            frame[mask_fill] = 1.0
            
            dist_outer = radius_grid - target_r_out
            mask_outer = dist_outer > 0
            
            glow_thickness = 4.0 + 12.0 * activity
            frame[mask_outer] += np.exp(-(dist_outer[mask_outer]**2) / (glow_thickness**2))
            
            edge_glow = 2.0
            frame[mask_outer] += 0.6 * np.exp(-(dist_outer[mask_outer]**2) / (edge_glow**2))

            yield _frame_bytes_from_gray(np.clip(frame, 0, 1))

    mux_frames_to_video(input_path, output_path, width, height, fps, frames, 
                        prefer_audio_copy, video_preset, video_crf, 
                        start_seconds, limit_seconds, total_frames)


def render_classic_wave_video(
    input_path: Path, output_path: Path, width: int, height: int, fps: int,
    prefer_audio_copy: bool, video_preset: str, video_crf: str, limit_seconds: int | None,
    start_seconds: int | None, visual_gain: float,
) -> None:
    audio, sample_rate, analysis = load_render_context(str(input_path), 44100, start_seconds, limit_seconds, fps)
    total_frames = len(analysis.activity)
    
    baseline_y = int(height * 0.65)
    
    yy, _ = np.mgrid[:height, :width]

    def frames():
        prev_front = np.zeros(width, dtype=np.float32)
        prev_back = np.zeros(width, dtype=np.float32)
        
        for frame_idx in range(total_frames):
            source = analysis.band_profile[frame_idx] ** 1.5
            
            mirrored = np.concatenate([source[::-1], source])
            
            x_old = np.linspace(0, 1, len(mirrored))
            x_new = np.linspace(0, 1, width)
            target_shape = np.interp(x_new, x_old, mirrored)
            
            target_shape = _gaussian_blur_1d(target_shape, max(3, width // 20), passes=3)
            
            front = np.where(target_shape > prev_front,
                             0.3 * prev_front + 0.7 * target_shape,
                             0.8 * prev_front + 0.2 * target_shape)
            prev_front = front.copy()
            
            back = np.where(target_shape > prev_back,
                            0.7 * prev_back + 0.3 * target_shape,
                            0.9 * prev_back + 0.1 * target_shape)
            prev_back = back.copy()
            
            amp_front = front * (height * 0.4) * visual_gain
            amp_back = back * (height * 0.45) * visual_gain
            
            y_front = baseline_y - amp_front
            y_back = baseline_y - amp_back
            
            frame = np.zeros((height, width), dtype=np.float32)
            
            mask_back = (yy > y_back) & (yy <= baseline_y)
            frame[mask_back] = 0.35
            
            mask_front = (yy > y_front) & (yy <= baseline_y)
            frame[mask_front] = 1.0
            
            dist = np.abs(yy - y_front)
            glow = 0.4 * np.exp(-(dist**2) / (12.0**2))
            
            frame += np.where(yy <= baseline_y, glow, 0.0)
            
            yield _frame_bytes_from_gray(np.clip(frame, 0, 1))

    mux_frames_to_video(input_path, output_path, width, height, fps, frames, 
                        prefer_audio_copy, video_preset, video_crf, 
                        start_seconds, limit_seconds, total_frames)


def render_cinematic_bars_video(
    input_path: Path, output_path: Path, width: int, height: int, fps: int,
    prefer_audio_copy: bool, video_preset: str, video_crf: str, limit_seconds: int | None,
    start_seconds: int | None, visual_gain: float,
) -> None:
    audio, sample_rate, analysis = load_render_context(str(input_path), 44100, start_seconds, limit_seconds, fps)
    total_frames = len(analysis.activity)
    
    num_bars = 64
    bar_spacing = width / num_bars
    bar_width = max(1, int(bar_spacing * 0.75))
    baseline_y = int(height * 0.85)

    def frames():
        prev_heights = np.zeros(num_bars, dtype=np.float32)
        
        for frame_idx in range(total_frames):
            source = analysis.band_profile[frame_idx] ** 1.3
            
            source = _smooth_vector(source, 3)
            
            x_old = np.linspace(0, 1, len(source))
            x_new = np.linspace(0, 1, num_bars)
            target_heights = np.interp(x_new, x_old, source)
            
            heights = np.where(target_heights > prev_heights,
                               0.3 * prev_heights + 0.7 * target_heights,
                               0.8 * prev_heights + 0.2 * target_heights)
            prev_heights = heights.copy()
            
            frame = np.zeros((height, width), dtype=np.float32)
            
            for i in range(num_bars):
                h = heights[i] * (height * 0.55) * visual_gain
                h = max(4.0, h) 
                
                center_x = int((i + 0.5) * bar_spacing)
                x0 = max(0, center_x - bar_width // 2)
                x1 = min(width, x0 + bar_width)
                
                y1 = baseline_y
                y0 = int(y1 - h)
                
                if x1 > x0 and y1 > y0:
                    y0 = max(0, y0)
                    frame[y0:y1, x0:x1] = 1.0
                    
                    glow_h = int(height * 0.05)
                    gy0 = max(0, y0 - glow_h)
                    
                    if gy0 < y0:
                        grad = np.linspace(0.0, 0.5, y0 - gy0)[:, None]
                        frame[gy0:y0, x0:x1] += grad

            yield _frame_bytes_from_gray(np.clip(frame, 0, 1))

    mux_frames_to_video(input_path, output_path, width, height, fps, frames, 
                        prefer_audio_copy, video_preset, video_crf, 
                        start_seconds, limit_seconds, total_frames)


def render_video(
    input_path: Path,
    output_path: Path,
    style: Style,
    width: int,
    height: int,
    fps: int,
    prefer_audio_copy: bool,
    visual_gain: float = 1.0,
    video_preset: str = "faster",
    video_crf: str = "17",
    limit_seconds: int | None = None,
    start_seconds: int | None = None,
) -> None:
    if not input_path.exists():
        raise FileNotFoundError(f"Input file not found: {input_path}")

    if style.name == "eclipse":
        render_eclipse_video(
            input_path, output_path, width, height, fps, prefer_audio_copy,
            video_preset, video_crf, limit_seconds, start_seconds, visual_gain
        )
    elif style.name == "classic_wave":
        render_classic_wave_video(
            input_path, output_path, width, height, fps, prefer_audio_copy,
            video_preset, video_crf, limit_seconds, start_seconds, visual_gain
        )
    elif style.name == "cinematic_bars":
        render_cinematic_bars_video(
            input_path, output_path, width, height, fps, prefer_audio_copy,
            video_preset, video_crf, limit_seconds, start_seconds, visual_gain
        )
    else:
        raise ValueError(f"Unknown style {style.name}")


def render_all_previews(
    input_file: Path,
    output_dir: Path,
    width: int,
    height: int,
    fps: int,
    prefer_audio_copy: bool,
) -> list[Path]:
    output_dir.mkdir(parents=True, exist_ok=True)
    outputs: list[Path] = []
    preview_start = pick_preview_start(input_file)
    for style in STYLES:
        output_file = output_dir / f"{input_file.stem}_{style.name}.mov"
        print(f"Rendering {style.name} -> {output_file.name}")
        render_video(
            input_path=input_file,
            output_path=output_file,
            style=style,
            width=width,
            height=height,
            fps=fps,
            visual_gain=5.0,
            prefer_audio_copy=prefer_audio_copy,
            video_preset="veryfast",
            video_crf="18",
            limit_seconds=10,
            start_seconds=preview_start,
        )
        outputs.append(output_file)
    return outputs


def pick_preview_start(
    input_file: Path,
    clip_seconds: int = 10,
    search_seconds: int = 60,
    step_seconds: int = 5,
) -> int:
    _, _, analysis = load_render_context(str(input_file), 44100, None, None, 30)
    activity = analysis.activity
    beat = analysis.beat
    clip_frames = max(1, int(clip_seconds * 30))
    search_frames = min(len(activity), int(search_seconds * 30))
    if clip_frames <= 0 or search_frames <= clip_frames:
        return 0

    step_frames = max(1, int(step_seconds * 30))
    best_start = 0
    best_score = -1.0
    max_start = search_frames - clip_frames
    drive = np.clip(activity + 0.6 * beat, 0.0, 1.5)
    kernel = np.ones(clip_frames, dtype=np.float32) / clip_frames
    scores = np.convolve(drive, kernel, mode="valid")
    for start in range(0, max_start + 1, step_frames):
        if start >= len(scores):
            break
        score = float(scores[start])
        if score > best_score:
            best_score = score
            best_start = start
    return int(best_start / 30)


def write_preview_index(output_dir: Path, input_file: Path, outputs: list[Path]) -> Path:
    index_path = output_dir / "index.html"
    items = "\n".join(
        f'<li><a href="{html.escape(output.name)}">{html.escape(output.stem)}</a></li>'
        for output in outputs
    )
    html_doc = f"""<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>Visualizer previews for {html.escape(input_file.name)}</title>
  <style>
    body {{
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      background: #111;
      color: #f2f2f2;
      padding: 32px;
    }}
    a {{ color: #8fd3ff; text-decoration: none; }}
    a:hover {{ text-decoration: underline; }}
    li {{ margin: 0.5rem 0; }}
  </style>
</head>
<body>
  <h1>Visualizer previews for {html.escape(input_file.name)}</h1>
  <p>Open a style to preview it.</p>
  <ul>
    {items}
  </ul>
</body>
</html>
"""
    index_path.write_text(html_doc, encoding="utf-8")
    return index_path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Turn any audio file into a black-background visualizer video."
    )
    parser.add_argument("--input", "-i", help="Path to the audio file.")
    parser.add_argument("--output", "-o", help="Path to the output video or folder.")
    parser.add_argument(
        "--style",
        "-s",
        help="Visualizer style name. Use --list-styles to see options.",
    )
    parser.add_argument("--width", type=int, default=1920, help="Output video width.")
    parser.add_argument("--height", type=int, default=1080, help="Output video height.")
    parser.add_argument("--fps", type=int, default=60, help="Output video frame rate.")
    parser.add_argument(
        "--no-audio-copy",
        action="store_true",
        help="Always re-encode audio to AAC instead of trying to copy the source audio stream.",
    )
    parser.add_argument(
        "--list-styles",
        action="store_true",
        help="Print the available visualizer styles and exit.",
    )
    parser.add_argument(
        "--preview-all",
        action="store_true",
        help="Render all options into a preview folder and create an index.html file.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    if args.list_styles:
        list_styles()
        return 0

    input_path = args.input
    if not input_path:
        input_path = choose_input_file()
    if not input_path:
        input_path = input("Enter the path to an audio file: ").strip()

    if not input_path:
        print("No input file provided.")
        return 1

    input_file = Path(input_path).expanduser().resolve()
    if not input_file.exists():
        print(f"Input file not found: {input_file}")
        return 1

    if args.preview_all:
        output_dir = Path(args.output).expanduser().resolve() if args.output else None
        if output_dir is None:
            chosen_dir = choose_output_directory(input_file.parent)
            output_dir = (
                Path(chosen_dir).expanduser().resolve()
                if chosen_dir
                else input_file.parent / f"{input_file.stem}_previews"
            )
        preview_dir = output_dir if output_dir.suffix == "" else output_dir.parent
        if preview_dir.exists() and preview_dir.is_file():
            print(f"Output path is a file, not a folder: {preview_dir}")
            return 1
        if output_dir.suffix:
            preview_dir = output_dir.parent / f"{input_file.stem}_previews"

        outputs = render_all_previews(
            input_file=input_file,
            output_dir=preview_dir,
            width=args.width,
            height=args.height,
            fps=args.fps,
            prefer_audio_copy=not args.no_audio_copy,
        )
        index_path = write_preview_index(preview_dir, input_file, outputs)
        print(f"Preview folder: {preview_dir}")
        print(f"Preview index:  {index_path}")
        return 0

    if args.style:
        style = style_by_name(args.style)
    else:
        style = choose_style_dialog()
        if style is None:
            if sys.stdin.isatty():
                style = choose_style_interactively()
            else:
                style = STYLES[0]

    output_path = args.output
    if not output_path:
        chosen_dir = choose_output_directory(input_file.parent)
        if chosen_dir:
            output_dir = Path(chosen_dir).expanduser().resolve()
            output_path = str(output_dir / f"{input_file.stem}_{style.name}.mov")
        else:
            output_path = str(input_file.with_name(f"{input_file.stem}_{style.name}.mov"))

    output_file = Path(output_path).expanduser().resolve()
    output_file.parent.mkdir(parents=True, exist_ok=True)

    print(f"\nConfiguration:\n  Input:  {input_file}\n  Style:  {style.name}\n  Output: {output_file}\n")

    render_video(
        input_path=input_file,
        output_path=output_file,
        style=style,
        width=args.width,
        height=args.height,
        fps=args.fps,
        visual_gain=1.0,
        prefer_audio_copy=not args.no_audio_copy,
        video_preset="faster",
        video_crf="17",
        limit_seconds=None,
        start_seconds=None,
    )

    print("\nRender Complete.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())